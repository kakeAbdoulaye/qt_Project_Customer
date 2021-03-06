#include "interfacedb.h"


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
bool InterfaceDB::closeConnection()
{
    this->dataBase.close();
    return true;
}
bool InterfaceDB::checkLoginPasswordDB(QString login, QString password)
{
    bool check ;
    int count = 0;
    check = createConnection();
    this->query = QSqlQuery(dataBase);
    QString request = "SELECT * FROM TCompte WHERE Login=:log and MdP=:pas";
    this->query.prepare(request);
    this->query.bindValue(":log",login);
    this->query.bindValue(":pas",password);
    check = check && this->query.exec();
    if(!check)
    {
        qDebug() << query.lastError().text();
        qDebug() << "Request Error  !\n";
        closeConnection();
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
        closeConnection();
        return check;
    }
}
qint32 InterfaceDB::lastIdTable(QString TableName)
{

    createConnection();
    QSqlQuery query;
    query = QSqlQuery(getDataBase());
    QString request =QString("SELECT id as LastID FROM %1 ORDER BY id DESC LIMIT 1").arg(TableName);
    qint32 lastid;

    if(query.exec(request))
    {
        query.next();
        lastid= query.value("LastID").toString().toInt();
    }
    closeConnection();
   return lastid;
}
QSqlTableModel * InterfaceDB::getAllType()
{
    createConnection();
    QSqlTableModel * model = new QSqlTableModel;
    model->setTable("TType");
    model->select();
    closeConnection();
    return model;
}
QStringList InterfaceDB::getTypeByid(qint32 id)
{
    QString request = "SELECT * FROM TType WHERE  Id=:idtype";
    QStringList data ;
    createConnection();
    QSqlQuery query;
    query = QSqlQuery(getDataBase());
    query.prepare(request);
    query.bindValue(":idtype",id);
    if(query.exec())
    {
        while(query.next())
        {
            data << query.value("Id").toString();
            data << query.value("Label").toString();
        }
    }
    closeConnection();
    return data;
}
qint32 InterfaceDB::getSizeTable(QString TableName)
{
    createConnection();
    QSqlQuery query;
    query = QSqlQuery(getDataBase());
    QString request =QString("SELECT count(*) as SIZE FROM %1").arg(TableName);
    qint32 size;

    if(query.exec(request))
    {
        query.next();
        size= query.value("SIZE").toString().toInt();
    }
    closeConnection();
   return size;
}
void InterfaceDB::deleteToTable(QString TableName, qint32 id)
{
    createConnection();
    QString request =QString("DELETE FROM %1 WHERE Id = %2 ").arg(TableName).arg(id) ;
    QSqlQuery query;
    query = QSqlQuery(getDataBase());
    query.exec(request);
    closeConnection();
}
