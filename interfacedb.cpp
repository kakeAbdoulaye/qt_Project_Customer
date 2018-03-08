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
 QSqlRelationalTableModel * InterfaceDB::getAllRessource()
{
    createConnection();
    QSqlRelationalTableModel * model = new  QSqlRelationalTableModel;
    model->setTable("TRessource");
    model->setRelation(TRessource_idType,QSqlRelation("TType","Id","Label"));
    model->setHeaderData(TRessource_Nom,Qt::Horizontal,"Name");
    model->setHeaderData(TRessource_Prenom,Qt::Horizontal,"First Name");
    model->setHeaderData(TRessource_idType,Qt::Horizontal,"Type");
    model->select();
    closeConnection();
    return model;
}
 QStandardItemModel * InterfaceDB::getAllRessource_TreeView()
 {

     QMap<QString ,QStandardItem * > monMap ;
     QMap<QString ,QStandardItem * >::iterator iteratorMap;
     QString space =" ";

     createConnection();

     QSqlQuery query;
     if(query.exec("SELECT * FROM TType"))
     {
         while(query.next())
         {
           QString itemParent = query.value("Label").toString();
           monMap.insert(itemParent,new QStandardItem(itemParent));
         }
     }
     if(query.exec("SELECT * FROM TRessource INNER JOIN TType ON TRessource.IdType = TType.ID"))
     {
         while(query.next())
         {
             QString parent = query.value("Label").toString();
             QString child = query.value("Nom").toString()+space+query.value("Prenom").toString();
             for (iteratorMap = monMap.begin(); iteratorMap != monMap.end(); ++iteratorMap)
             {
                if(iteratorMap.key() == parent)
                {
                     QStandardItem * itemChild =new QStandardItem(child);
                     iteratorMap.value()->appendRow(itemChild);
                }
             }

         }
     }

     QStandardItemModel * monModel =new QStandardItemModel  ;

     for (iteratorMap = monMap.begin(); iteratorMap != monMap.end(); ++iteratorMap)
     {
         monModel->appendRow(iteratorMap.value()); ;
     }

     closeConnection();

     return monModel;
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
QSqlTableModel * InterfaceDB::getAllCustomer()
{
    createConnection();
    QSqlTableModel * model = new QSqlTableModel;
    model->setTable("TClient");
    model->select();
    closeConnection();
    return model;
}
