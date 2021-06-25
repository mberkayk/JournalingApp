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

    keyFile = new QFile(dirStr + "/key");
    dataFile = new QFile(dirStr + "/db.json");

    dbData = new QJsonDocument();

}

void Database::loadData(){
    //decrpyt the data first
    bool b;
    if(dataFile->exists()){
        b = dataFile->open(QIODevice::ExistingOnly |
                     QIODevice::ReadOnly);
    }else{
        b = dataFile->open(QIODevice::NewOnly |
                     QIODevice::ReadOnly);
    }
    Q_ASSERT(b);

    QByteArray arr = dataFile->readAll();
    *dbData = QJsonDocument(QJsonDocument::fromJson(arr));
    if(arr.isEmpty() || dbData->isObject() == false) {
        dbData->setObject(QJsonObject());
    }

    dataFile->close();

}

void Database::saveData(){
    //encrypt the data
    //save the data
}


Database::~Database(){
    delete dataFile;
    delete keyFile;
}
