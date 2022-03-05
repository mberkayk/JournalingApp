#include "mainwindow.h"

#include <QStandardPaths>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {


	centralWidget = new QWidget;
	setCentralWidget(centralWidget);

	mainLayout = new QStackedLayout;
	centralWidget->setLayout(mainLayout);

	editPanel = new EditPanel;
	listPanel = new ListPanel;

	QString dirStr = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
	QFile keyFile(dirStr + "/key");

	passPanel = new PasswordPanel(keyFile.exists());


    mainLayout->addWidget(passPanel);
    mainLayout->addWidget(editPanel);
    mainLayout->addWidget(listPanel);

    QObject::connect(editPanel->getListPanelButton(), &QPushButton::pressed,
                     this, &MainWindow::switchToListPanel);

	QObject::connect(passPanel, &PasswordPanel::newPasswordSignal,
					 this, [this](QByteArray a){emit newPasswordSignal(a);});
	QObject::connect(passPanel, &PasswordPanel::passEnteredSignal,
					 this, [this](QByteArray a){emit passEnteredSignal(a);});

}


void MainWindow::switchToListPanel(){
    mainLayout->setCurrentWidget(listPanel);
}

void MainWindow::switchToEditPanel(){
	mainLayout->setCurrentWidget(editPanel);
}
