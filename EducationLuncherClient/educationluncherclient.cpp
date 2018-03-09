#include "educationluncherclient.h"
#include "ui_educationluncherclient.h"
#include <QtNetwork>
#include <QLabel>

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





void EducationLuncherClient::processPendingDatagrams() // 接收到服务端udp广播，触发此函数，发出tcp连接服务端
{


       tcpClient->connectToHost(QHostAddress("192.168.3.2"),6666);
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


    connect(tcpClient,SIGNAL(readyRead()),this,SLOT(slotreadServer()));
   // udpScoket->close();


}

void EducationLuncherClient::slotreadServer() //当服务端有新信息时触发更新UI界面
{
      QString serverMsg=tcpClient->readAll();
      ui->label->setText(serverMsg);


}
