#include "editpanel.h"


TopBar::TopBar() : QWidget(), layout(), listPanelButton() {

    setLayout(&layout);
    listPanelButton.setText("See Previous Entries");
    layout.addWidget(&listPanelButton);
}

EditPanel::EditPanel(QWidget *parent)
    : QWidget(parent), mainLayout(), topBar(), textEdit()
{
    setLayout(&mainLayout);
    mainLayout.addWidget(&topBar);
    mainLayout.addWidget(&textEdit);

}
