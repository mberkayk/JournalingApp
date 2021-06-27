#include "passwordpanel.h"

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
