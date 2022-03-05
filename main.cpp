#include "mainwindow.h"
#include "database.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("mberkayk");
    QCoreApplication::setApplicationName("Journalling-App");

	Database db;
    MainWindow w;

	QObject::connect(&w, &MainWindow::newPasswordSignal,
					 &db, &Database::newPasswordEntered);

	QObject::connect(&w, &MainWindow::passEnteredSignal,
					 &db, &Database::oldPassEntered);

	QObject::connect(&db, &Database::passInitComplete,
					 &w, &MainWindow::switchToEditPanel);

    w.show();
    return a.exec();
}
