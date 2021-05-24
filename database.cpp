#include "database.h"
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QJsonObject>

Database::Database() {

    QString dirStr = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(dirStr);
    if(!dir.exists()){
        qDebug() << "data directory does not exist";
        if(dir.mkpath(dirStr)) qDebug() << "data directory was created";
        else qDebug() << "data directory couldn't be created";
    }else{
        qDebug() << "data directory alredy exists" << dirStr;
    }

    file = new QFile(dirStr + "/db.json");

    dbData = new QJsonDocument();

    //load the data from file to dbData object
    bool b;
    if(file->exists()){
        b = file->open(QIODevice::ExistingOnly |
                     QIODevice::ReadOnly);
    }else{
        b = file->open(QIODevice::NewOnly |
                     QIODevice::ReadOnly);
    }
    Q_ASSERT(b);

    QByteArray arr = file->readAll();
    *dbData = QJsonDocument(QJsonDocument::fromJson(arr));
    if(arr.isEmpty() || dbData->isObject() == false) {
        dbData->setObject(QJsonObject());
    }

    file->close();

}

Database::~Database(){
    delete file;
}
