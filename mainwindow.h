#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedLayout>

#include "listpanel.h"
#include "editpanel.h"
#include "passwordpanel.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QWidget *centralWidget;
    QStackedLayout *mainLayout;

    EditPanel *editPanel;
    ListPanel *listPanel;
    PasswordPanel *passPanel;

    void switchToListPanel();

public:
    MainWindow(QWidget *parent = nullptr);

public slots:
	void switchToEditPanel();

signals:
	void newPasswordSignal(QByteArray);
	void passEnteredSignal(QByteArray);

};
#endif // MAINWINDOW_H
