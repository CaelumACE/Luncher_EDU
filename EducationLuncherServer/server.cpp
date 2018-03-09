#include "server.h"
#include "educationluncherserver.h"

Server::Server(QObject*parent,int port)
       :QTcpServer(parent)
{
       this->listen(QHostAddress::AnyIPv4,port);   //监听客户端


}



void Server::incomingConnection(qintptr socketDescriptor)//当有新客户端连接时调用，绑定slotUpdateClients，slotDisconnected函数，并加入客户端列表
{

   TcpClientSocket* tcpClientsSocket=new TcpClientSocket(this);
   connect(tcpClientsSocket,SIGNAL(signalUpdateClients(QString)),this,SLOT(slotUpdateClients(QString)));
   connect(tcpClientsSocket,SIGNAL(signalDisconnected(qintptr)),this,SLOT(slotDisconnected(qintptr)));
   tcpClientsSocket->setSocketDescriptor(socketDescriptor);
   clientList.append(tcpClientsSocket); 
   slotSendToMsg(tcpClientsSocket);

//   connect(tcpClientsSocket,SIGNAL(signalDisconnected(qintptr)),temp,SLOT(slotDisconnected(int)));

}

void Server::slotUpdateClients(QString msg) //信号触发，客户端有新信息传入
{
   emit signalUpdateServer(msg);   //发送服务器信息更新


}

void Server::slotDisconnected(qintptr descriptor)//信号触发客户端与服务器断开连接
{

    for(int i=0;i<clientList.count();i++)
    {
        QTcpSocket* item =clientList.at(i);
        if (item->socketDescriptor()==descriptor)
        {
            clientList.removeAt(i);
             emit signalDisconnected(i);

            return;


        }
    }
    return;
     //将断开的客户端，从客户端列表移除

}


void Server::slotSendToMsg(TcpClientSocket* tcpSocketClient)//当有客户端接入时，同时给客户端发送字符串，并通过客户端列表排序的index，传送Hello Client+index
{


        QByteArray serverMsg;
        int i=clientList.indexOf(tcpSocketClient);
        serverMsg.append(tr("Hello Client %1").arg(i));
        QTcpSocket* item=clientList.at(i);
        item->write(serverMsg);

}


