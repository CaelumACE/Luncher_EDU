#include "educationluncherserver.h"
#include "ui_educationluncherserver.h"
#include "server.h"
#include <QtNetwork>
#include <QLabel>
#include<QListView>
#include<QStringListModel>
#include<QProcess>




EducationLuncherServer::EducationLuncherServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EducationLuncherServer)
{
    ui->setupUi(this);


    port=6666;
    ui->statusLabel->setText(tr("Ready to Broadcast datagrams on port 6666"));
    ui->statusLabel->setWordWrap(true);
    startButton=new QPushButton(tr("&Start"));
    closeButton=new QPushButton(tr("&Quit"));
    ui->buttonBox->addButton(startButton,QDialogButtonBox::ActionRole);
    ui->buttonBox->addButton(closeButton,QDialogButtonBox::RejectRole);
    connect(startButton,SIGNAL(clicked()),this,SLOT(slotCreatServer()));
    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));



    timer=new QTimer(this);
    udpSocket=new QUdpSocket(this);
    messageNo=1;

    connect(startButton,SIGNAL(clicked()),this,SLOT(startBroadcasting()));
    connect(timer,SIGNAL(timeout()),this,SLOT(broadcastDatagram()));

    setWindowTitle("Broadcast Sender");




}

EducationLuncherServer::~EducationLuncherServer()
{
    delete ui;
}





void EducationLuncherServer::startBroadcasting()//触发点击Start按钮后调用此槽函数开始计时
{
  startButton->setEnabled(false);
  timer->start(1000);

}


void EducationLuncherServer::broadcastDatagram()//计时开始时触发此槽函数
{
  ui->statusLabel->setText(tr("Now broadcasting datagram:   %1").arg(messageNo));
  QByteArray datagram=""+QByteArray::number(messageNo);
  udpSocket->writeDatagram(datagram.data(),datagram.size(),QHostAddress::LocalHost,port);//udp广播
  ++messageNo;

}




void EducationLuncherServer::slotCreatServer()//创建服务器
{
   teacherServer=new Server(this,port);
   connect(teacherServer,SIGNAL(signalUpdateServer(QString)),this,SLOT(slotUpdateServer(QString)));
   startButton->setEnabled(false);
   connect(teacherServer,SIGNAL(signalDisconnected(int)),this,SLOT(slotDisconnected(int)));

//   QString programAddress ="D:/MySoft/Tencent/QQ/Bin/QQScLauncher.exe";  //打开程序的路径
//   QStringList arguments;  //命令参数

//   QProcess *chromeProcess = new QProcess(this);
//   chromeProcess->start(programAddress,arguments);// 此处第二个参数为空，如果用一个参数，要保证programAddress中没有空格
}

void EducationLuncherServer::slotUpdateServer(QString msg)//客户端新信息触发UI界面信息更新
{
        ui->listWidget->addItem(msg);


}


void EducationLuncherServer::slotDisconnected(int i)//客户端断开连接后，触发此函数，将Listwidget对应数据移除
{
   ui->listWidget->takeItem(i);
   // ui ->listWidget->clear();


}

