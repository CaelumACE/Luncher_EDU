#include "educationluncherserver.h"
#include <QApplication>
#include<QQuickView>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EducationLuncherServer w;


    w.show();
    return a.exec();



}
