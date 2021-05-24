#ifndef EDITPANEL_H
#define EDITPANEL_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QBoxLayout>

class TopBar : public QWidget {
    Q_OBJECT

private:
    QVBoxLayout layout;
    QPushButton listPanelButton;

public:
    TopBar();
    const QPushButton * getButton() {return &listPanelButton;}
};

class EditPanel : public QWidget {
    Q_OBJECT

private:
    QVBoxLayout mainLayout;
    TopBar topBar;
    QTextEdit textEdit;

public:
    EditPanel(QWidget *parent = nullptr);
    const QPushButton * getListPanelButton() {return topBar.getButton();}
};

#endif // EDITPANEL_H
