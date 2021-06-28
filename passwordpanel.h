#ifndef PASSWORDPANEL_H
#define PASSWORDPANEL_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>

class InitPassword : public QWidget {

private:
	QVBoxLayout layout;

	QLabel firstLabel;
	QLineEdit firstLine;
	QLabel secondLabel;
	QLineEdit secondLine;

	QPushButton enterButton;

public:
	InitPassword();

    void enterButtonPressed();

};

class EnterPassword : public QWidget {

private:
	QVBoxLayout layout;

	QLabel label;
	QLineEdit passLineEdit;

	QPushButton enterButton;

public:
	EnterPassword();

};

class PasswordPanel : public QWidget {

private:
	QVBoxLayout layout;

	InitPassword *initPass;
	EnterPassword *enterPass;

public:
    PasswordPanel(bool b);

};

#endif // PASSWORDPANEL_H
