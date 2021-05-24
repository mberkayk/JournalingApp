#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("mberkayk");
    QCoreApplication::setApplicationName("Journalling-App");

    MainWindow w;
    w.show();
    return a.exec();
}
