#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QFile>
#include <QJsonDocument>

#include <openssl/evp.h>

class Encryption{

public:
    Encryption();

    void encrypt();
    void generateKey();

};

class Database
{

private:
    QFile* dataFile;
    QFile* keyFile;
    QJsonDocument* dbData;

    void loadData();
    void saveData();

public:
    Database();
    ~Database();
};

#endif // DATABASE_H
