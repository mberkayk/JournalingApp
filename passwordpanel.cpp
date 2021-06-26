#include "passwordpanel.h"

InitPassword::InitPassword() : layout(), firstLabel(),
	 firstLine(), secondLabel(), secondLine(),
	  enterButton() {


	setLayout(&layout);

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
