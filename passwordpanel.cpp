#include "passwordpanel.h"
#include <QErrorMessage>
#include <QDebug>

InitPassword::InitPassword() : layout(), firstLabel("Enter a password:"),
	 firstLine(), secondLabel("Enter your password again:"), secondLine(),
	  enterButton() {


	setLayout(&layout);
    layout.addWidget(&firstLabel);
    firstLine.setEchoMode(QLineEdit::Password);
    layout.addWidget(&firstLine);

    layout.addWidget(&secondLabel);
    secondLine.setEchoMode(QLineEdit::Password);
    layout.addWidget(&secondLine);

    layout.addSpacing(70);

    enterButton.setText("Enter");
    layout.addWidget(&enterButton);

    QObject::connect(&enterButton, &QPushButton::pressed,
                     this, &InitPassword::enterButtonPressed);

}

void InitPassword::enterButtonPressed(){
    if(firstLine.text().compare(secondLine.text() != 0)){
        QErrorMessage *em = new QErrorMessage(this);
        em->testAttribute(Qt::WA_DeleteOnClose);
        em->showMessage("Passwords aren't matching!");
    }else{

        //generate salt
        //store the salt in the database
        //use PBKDF2 to create a hash from the password
        //store the hash in the database

    }

}

EnterPassword::EnterPassword() : layout(), label(),
	 passLineEdit(), enterButton() {

	setLayout(&layout);

}

PasswordPanel::PasswordPanel(bool b) : layout(){

	setLayout(&layout);

	if(b){
		enterPass = new EnterPassword();
		layout.addWidget(enterPass);
	}else{
		initPass = new InitPassword();
		layout.addWidget(initPass);
	}

}
