#ifndef TCPCLIENTSOCKET_H
#define TCPCLIENTSOCKET_H

#include<QTcpSocket>
#include<QObject>

class TcpClientSocket:public QTcpSocket
{
    Q_OBJECT

public:
    TcpClientSocket(QObject* parent=0);

signals:
    void signalUpdateClients(QString);
    void signalDisconnected(qintptr);

protected slots:
    void dataReceived();
    void slotDisconnected();

};
#endif // TCPCLIENTSOCKET_H
