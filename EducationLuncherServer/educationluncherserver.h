#ifndef EDUCATIONLUNCHERSERVER_H
#define EDUCATIONLUNCHERSERVER_H
#include"server.h"
#include <QMainWindow>
#include<QtNetwork>
#include<QTimer>
#include<QPushButton>



namespace Ui {
class EducationLuncherServer;
}

class EducationLuncherServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit EducationLuncherServer(QWidget *parent = 0);
    ~EducationLuncherServer();



public:
    int port;
    Server* teacherServer;

public slots:
    void slotCreatServer();
    void slotUpdateServer(QString msg);
    void slotDisconnected(int i);


private slots:

    void startBroadcasting();
    void broadcastDatagram();



private:

    QUdpSocket* udpSocket;

private:
    QPushButton* startButton;
    QPushButton* closeButton;
    QTimer* timer;
    int messageNo;


private:
    Ui::EducationLuncherServer *ui;
};

#endif // EDUCATIONLUNCHERSERVER_H
