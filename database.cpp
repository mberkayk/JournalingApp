#include "database.h"
#include <QStandardPaths>
#include <QDir>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>

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
    QString dbPath = dirStr + "/database.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");//not dbConnection
    db.setDatabaseName(dbPath);
    if(!db.open()) qDebug() << db.lastError();

}




Database::~Database(){
    delete dataFile;
    delete keyFile;
}
