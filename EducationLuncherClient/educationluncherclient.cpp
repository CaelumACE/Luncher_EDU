#include "educationluncherclient.h"
#include "ui_educationluncherclient.h"
#include <QtNetwork>
#include <QLabel>
#include<QProcess>

EducationLuncherClient::EducationLuncherClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EducationLuncherClient)
{
    ui->setupUi(this);

    ui->statusLabel->setText(tr("Listening for broadcasted message"));
    ui->statusLabel->setWordWrap(true);

    udpScoket=new QUdpSocket(this);
    tcpClient=new QTcpSocket(this);

    udpScoket->bind(6666,QUdpSocket::ShareAddress);
    connect(udpScoket,SIGNAL(readyRead()),this,SLOT(processPendingDatagrams()));

    setWindowTitle(tr("Broadcast Receiver"));


}

EducationLuncherClient::~EducationLuncherClient()
{
    delete ui;
}

/*
void EducationLuncherClient::getLocalHostIpv4Adress()
{

   QString localHostName=QHostInfo::localHostName();
   QHostInfo info=QHostInfo::fromName(localHostName);
   foreach (QHostAddress address, info.addresses())
  {
       if(address.protocol()==QAbstractSocket::IPv4Protocol)
       {
           QString localAddressIPV4=address.toString();
       }

  }
}

*/



void EducationLuncherClient::processPendingDatagrams() // 接收到服务端udp广播，触发此函数，发出tcp连接服务端
{


       tcpClient->connectToHost(QHostAddress("192.168.0.135"),6666);

       connect(tcpClient,SIGNAL(connected()),this,SLOT(slotConnected()));


   while (udpScoket->hasPendingDatagrams())
   {
       QByteArray datagram;
       datagram.resize(udpScoket->pendingDatagramSize());
       udpScoket->readDatagram(datagram.data(),datagram.size());
       ui->statusLabel->setText(tr("Received datagram:  %1").arg(datagram.data()));
   }

}



void EducationLuncherClient::slotConnected() //连接成功后，将本机IP地址和主机名字传送给服务端
{
    QString localAdress=tcpClient->localAddress().toString();
    QString localName=QHostInfo::localHostName();
    QString localInformation=localName+"   "+localAdress;
    QByteArray clientData;
    clientData.append(localInformation);
    tcpClient->write(clientData);
       QString programAddress ="D:/MySoft/Tencent/QQ/Bin/QQScLauncher.exe";  //打开程序的路径
       QStringList arguments;  //命令参数


       //此段为QProcessd 打开外部程序，打开UE4程序
      QProcess *chromeProcess = new QProcess(this);
       chromeProcess->start(programAddress,arguments);// 此处第二个参数为空，如果用一个参数，要保证programAddress中没有空格
    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(slotreadServer()));
   // udpScoket->close();


}

void EducationLuncherClient::slotreadServer() //当服务端有新信息时触发更新UI界面
{
      QString serverMsg=tcpClient->readAll();
      ui->label->setText(serverMsg);


}
