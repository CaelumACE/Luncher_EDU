#include"tcpclientsocket.h"



TcpClientSocket::TcpClientSocket(QObject *parent)

{

    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));  //客户端有新信息，调用readready信号，触发槽函数datareceived
    connect(this,SIGNAL(disconnected()),this,SLOT(slotDisconnected())); //客户端断开时，调用disconnected信号，触发槽函数slotDisconnected

}


void TcpClientSocket::dataReceived() //客户端信息更新
{
  QString clientmessage=this->readAll();  //读取客户端的信息
  emit signalUpdateClients(clientmessage);  //发送客户端的信息信号
}


void TcpClientSocket::slotDisconnected()//客户端断开连接
{
   emit signalDisconnected(this->socketDescriptor()); //发送客户端断开信息

}
