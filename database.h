#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QFile>
#include <QJsonDocument>

class Database
{

private:
    QFile* file;
    QJsonDocument* dbData;

public:
    Database();
    ~Database();
};

#endif // DATABASE_H
