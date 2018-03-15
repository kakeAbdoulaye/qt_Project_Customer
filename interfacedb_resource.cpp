#include "interfacedb_resource.h"

interfacedb_Resource::interfacedb_Resource()
{

}
QStandardItemModel  * interfacedb_Resource::getAllRessource(qint32 id)
{
   QStandardItemModel * monModel =new QStandardItemModel  ;
   QMap<qint32,qint32> monMap ;
   QMap<qint32,qint32>::iterator iteratorMap;
   QString space =" ";
   QSqlQuery query;
   bool find=false;
   QString request = "SELECT * FROM TRdv WHERE  TRdv.IdClient=:iduser";
   createConnection();
   query = QSqlQuery(getDataBase());
   query.prepare(request);
   query.bindValue(":iduser",id);

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
               QString itemString = query.value("Id").toString()+space+query.value("Nom").toString()+space+query.value("Prenom").toString();
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
               QString itemString = query.value("Id").toString()+space+query.value("Nom").toString()+space+query.value("Prenom").toString();
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
QStandardItemModel * interfacedb_Resource::getAllRessource_TreeView()
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
qint32 interfacedb_Resource::getSizeTableRessource()
{

    createConnection();
    QSqlQuery query;
    QString request = "SELECT count(*) as SIZE FROM TRessource";
    qint32 size;
    if(query.exec(request))
    {
        query.next();
        size= query.value("SIZE").toString().toInt();
    }
    closeConnection();
   return size;
}
