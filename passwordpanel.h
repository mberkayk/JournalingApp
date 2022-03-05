#ifndef PASSWORDPANEL_H
#define PASSWORDPANEL_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QBoxLayout>

class InitPassword : public QWidget {

	Q_OBJECT

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

signals:
	void newPasswordSignal(QByteArray);

};

class EnterPassword : public QWidget {

	Q_OBJECT

private:
	QVBoxLayout *layout;

	QLineEdit *passLineEdit;

	QPushButton *enterButton;

public:
	EnterPassword();

signals:
	void passEnteredSignal(QByteArray);

};

class PasswordPanel : public QWidget {

	Q_OBJECT

private:
	QVBoxLayout layout;

	InitPassword *initPass;
	EnterPassword *enterPass;

public:
    PasswordPanel(bool b);

signals:
	void newPasswordSignal(QByteArray);
	void passEnteredSignal(QByteArray);

};

#endif // PASSWORDPANEL_H
