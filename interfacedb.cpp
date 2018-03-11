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
 QStandardItemModel  * InterfaceDB::getAllRessource(qint32 id)
{
    QStandardItemModel * monModel =new QStandardItemModel  ;
    QMap<qint32,qint32> monMap ;
    QMap<qint32,qint32>::iterator iteratorMap;
    QString space =" ";
    bool find=false;
    QString request = "SELECT * FROM TRdv WHERE  TRdv.IdClient=:iduser";
    createConnection();
    this->query = QSqlQuery(dataBase);
    this->query.prepare(request);
    this->query.bindValue(":iduser",id);

    if(query.exec())
    {
        while(query.next())
        {
            qint32 key = query.value("IdRessource").toInt();
            qint32 value= query.value("IdClient").toInt();
            qDebug()<<key<<space<<value;
            monMap.insert(key,value);
        }
    }
    request = "SELECT * FROM TRessource";
    if(id == -1)
    {
        if(query.exec(request))
        {
            while(query.next())
            {
                QString itemString = query.value("Nom").toString()+space+query.value("Prenom").toString();
                QStandardItem * item = new QStandardItem(itemString);
                item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
                item->setData(Qt::Unchecked, Qt::CheckStateRole);
                monModel->appendRow(item);
            }
        }
    }
    else
    {
        if(query.exec(request))
         {
             while(query.next())
             {
                QString itemString = query.value("Nom").toString()+space+query.value("Prenom").toString();
                QStandardItem * item = new QStandardItem(itemString);
                item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
                for (iteratorMap = monMap.begin(); iteratorMap != monMap.end() && find == false; ++iteratorMap)
                {
                   if(iteratorMap.key() == query.value("Id").toInt())
                   {
                       item->setData(Qt::Checked, Qt::CheckStateRole);
                       find = true;
                   }
                   else
                   {
                       item->setData(Qt::Unchecked, Qt::CheckStateRole);
                       find=false;
                   }
                }
                find = false;
                monModel->appendRow(item);

              }
          }
    }

    closeConnection();
    return monModel;
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
QSqlTableModel * InterfaceDB::getAllType(qint32 id)
{
    createConnection();
    QSqlTableModel * model = new QSqlTableModel;
    model->setTable("TType");
    qDebug()<<id;
    if(id != -1)
    {
        model->setFilter(QString("Id='%1'").arg(id));
    }
    model->select();
    closeConnection();
    return model;
}
QSqlTableModel * InterfaceDB::getAllCustomer()
{
    createConnection();
    QSqlTableModel * model = new QSqlTableModel;
    model->setTable("TClient");
    model->setHeaderData(TClient_Id,Qt::Horizontal,"Identification");
    model->setHeaderData(TClient_Nom,Qt::Horizontal,"Name");
    model->setHeaderData(TClient_Prenom,Qt::Horizontal,"First Name");
    model->setHeaderData(TClient_Adresse,Qt::Horizontal,"Address");
    model->setHeaderData(TClient_Ville,Qt::Horizontal,"Town");
    model->setHeaderData(TClient_CP,Qt::Horizontal,"Postal Code");
    model->setHeaderData(TClient_Tel,Qt::Horizontal,"Telephone");
    model->setHeaderData(TClient_Commentaire,Qt::Horizontal,"Information");
    model->setHeaderData(TClient_DateRdv,Qt::Horizontal,"Date");
    model->setHeaderData(TClient_Priorite,Qt::Horizontal,"Priority");
    model->select();
    closeConnection();
    return model;
}
QSqlTableModel * InterfaceDB::getAllCustomerFiltered(QString name, QString fname, QString date1, QString date2, qint32 id)
{
    QString filter="";
    createConnection();
    QSqlTableModel * model = new QSqlTableModel;
    model->setTable("TClient");
    model->setHeaderData(TClient_Id,Qt::Horizontal,"Identification");
    model->setHeaderData(TClient_Nom,Qt::Horizontal,"Name");
    model->setHeaderData(TClient_Prenom,Qt::Horizontal,"First Name");
    model->setHeaderData(TClient_Adresse,Qt::Horizontal,"Address");
    model->setHeaderData(TClient_Ville,Qt::Horizontal,"Town");
    model->setHeaderData(TClient_CP,Qt::Horizontal,"Postal Code");
    model->setHeaderData(TClient_Tel,Qt::Horizontal,"Telephone");
    model->setHeaderData(TClient_Commentaire,Qt::Horizontal,"Information");
    model->setHeaderData(TClient_DateRdv,Qt::Horizontal,"Date");
    model->setHeaderData(TClient_Priorite,Qt::Horizontal,"Priority");
    model->setFilter(QString("Nom like '%%1%' or Prenom like '%%2%' or DateRdv BETWEEN '%3' AND '%4' or Id='%5'").arg(name).arg(fname).arg(date1).arg(date2).arg(id));
    qDebug()<<QString("Nom like '%%1%' and Prenom like '%%2%' or DateRdv BETWEEN '%3' AND '%4' or Id='%5'").arg(name).arg(fname).arg(date1).arg(date2).arg(id);
    model->select();
    closeConnection();
    return model;
}
