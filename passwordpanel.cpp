#include "passwordpanel.h"
#include <QErrorMessage>
#include <QPasswordDigestor>
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
    if(firstLine.text().compare(secondLine.text()) != 0){
        QErrorMessage *em = new QErrorMessage(this);
        em->testAttribute(Qt::WA_DeleteOnClose);
        em->showMessage("Passwords aren't matching!");
    }else{
        char rawSalt[] = "not a very random salt";
        QByteArray salt = QByteArray::fromRawData(rawSalt, sizeof(rawSalt)/sizeof(char));
        QByteArray data = firstLine.text().toUtf8();

        QByteArray passKey = QPasswordDigestor::deriveKeyPbkdf2(QCryptographicHash::Sha256, data, salt, 10000, 32);
		qDebug() << "this is the passKey:" << passKey.size() << passKey;

		emit newPasswordSignal(passKey);
    }

}

EnterPassword::EnterPassword() {

	layout = new QVBoxLayout;
	setLayout(layout);

	layout->addWidget(new QLabel("Enter Password"));

	passLineEdit = new QLineEdit;
	passLineEdit->setEchoMode(QLineEdit::Password);
	layout->addWidget(passLineEdit);

	enterButton = new QPushButton("Enter");
	layout->addWidget(enterButton);

	QObject::connect(enterButton, &QPushButton::pressed,
					 this, [this]{
		char rawSalt[] = "not a very random salt";
		QByteArray salt = QByteArray::fromRawData(rawSalt, sizeof(rawSalt)/sizeof(char));
		emit passEnteredSignal(QPasswordDigestor::deriveKeyPbkdf2(QCryptographicHash::Sha256, passLineEdit->text().toUtf8(), salt, 10000, 32));
	});

}

PasswordPanel::PasswordPanel(bool b) : layout(){

	setLayout(&layout);

	if(b){
		enterPass = new EnterPassword();
		layout.addWidget(enterPass);
		QObject::connect(enterPass, &EnterPassword::passEnteredSignal,
						 this, [this](QByteArray a){emit passEnteredSignal(a);});
	}else{
		initPass = new InitPassword();
		layout.addWidget(initPass);
		QObject::connect(initPass, &InitPassword::newPasswordSignal, this,
						 [this](QByteArray a) {emit newPasswordSignal(a);});
	}

}
