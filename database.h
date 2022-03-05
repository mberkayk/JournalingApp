#ifndef DATABASE_H
#define DATABASE_H

#include <QFile>

class Encryption{

public:
    Encryption();

    void encrypt();
    void generateKey();

};

class Database : public QObject
{

	Q_OBJECT

private:
    QFile* keyFile;

    void loadData();
    void saveData();

	void handleErrors();

	int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext);
	int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char *plaintext);

public:
    Database();
    ~Database();

public slots:
	void newPasswordEntered(QByteArray);
	void oldPassEntered(QByteArray);

signals:
	void passInitComplete();
};

#endif // DATABASE_H
