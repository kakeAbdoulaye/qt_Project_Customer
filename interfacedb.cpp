#include "interfacedb.h"
#include <iostream>
InterfaceDB::InterfaceDB()
{

}
bool InterfaceDB::createConnection()
{
     bool openDB;
     dataBase = QSqlDatabase::addDatabase("QSQLITE");
     dataBase.setHostName("localhost");
     dataBase.setUserName("root");
     dataBase.setPassword("password");

     if(QFile::exists("base_tmp.sqli") == true)
     {
         dataBase.setDatabaseName("base_tmp.sqli");
         openDB = dataBase.open();
         if(openDB == false)
         {
             qDebug() << dataBase.lastError().text();
             qDebug() << "Error to open DataBase !\n";
             return false;
         }
     }
     else
     {
        qDebug() << "PATH of the dataBase is not Correct" ;
        return false;
     }
     return true;
}
bool InterfaceDB::checkLoginPasswordDB(QString login, QString password)
{
    bool check ;
    int count = 0;
    this->query = QSqlQuery(dataBase);
    QString request = "SELECT * FROM TCompte WHERE Login=:log and MdP=:pas";
    this->query.prepare(request);
    this->query.bindValue(":log",login);
    this->query.bindValue(":pas",password);
    check = this->query.exec();
    if(!check)
    {
        qDebug() << query.lastError().text();
        qDebug() << "Request Error  !\n";
        return check;
    }
    else
    {
        while (this->query.next()) {
            ++count;
        }
        if(count == 1)
        {
            check = true;
        }
        else
        {
            check = false;
        }
        return check;
    }
}
QSqlTableModel * InterfaceDB::getAllRessource()
{
    QSqlTableModel * model = new QSqlTableModel;
    model->setTable("TRessource");
    model->select();
    return model;
}
QSqlTableModel * InterfaceDB::getAllType()
{
    QSqlTableModel * model = new QSqlTableModel;
    model->setTable("TType");
    model->select();
    return model;
}
