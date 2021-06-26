#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), centralWidget(), mainLayout(), editPanel(), listPanel(), passPanel(true)
{

    setCentralWidget(&centralWidget);
    centralWidget.setLayout(&mainLayout);


    mainLayout.addWidget(&passPanel);
    mainLayout.addWidget(&editPanel);
    mainLayout.addWidget(&listPanel);


    QObject::connect(editPanel.getListPanelButton(), &QPushButton::pressed,
                     this, &MainWindow::switchToListPanel);

}


void MainWindow::switchToListPanel(){
    mainLayout.setCurrentWidget(&listPanel);
}
