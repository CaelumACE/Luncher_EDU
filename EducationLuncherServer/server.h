#ifndef SERVER_H
#define SERVER_H
#include<QTcpServer>
#include<QObject>
#include"tcpclientsocket.h"


class Server:public QTcpServer
{
  Q_OBJECT

public:
    Server(QObject*parent,int port);
    QList<TcpClientSocket*> clientList;

signals:
    void signalUpdateServer(QString msg);
    void signalDisconnected(int);

public slots:
    void slotUpdateClients(QString);
    void slotDisconnected(qintptr descriptor);
    void slotSendToMsg(TcpClientSocket *tcpSocketClient);

protected:
    void incomingConnection(qintptr socketDescriptor);//注意从QT5开始socketDescript类型改为qintptr,如果用int无法触发此函数



};



#endif // SERVER_H
