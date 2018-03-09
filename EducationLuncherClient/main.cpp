#include "educationluncherclient.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EducationLuncherClient w;
    w.show();

    return a.exec();
}
