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

void interfacedb_Resource::addStaffToResourceTable(Ressource ressoure, QString type)
{
    createConnection();
    QString requestTRessource = "INSERT INTO TRessource (Id,Nom,Prenom,IdType)VALUES(:idres,:nom,:prenom,:idtype);";
    QString requestTType= QString("SELECT Id FROM TType WHERE Label='%1'").arg(type);
    QString requestTCompte= "INSERT INTO TCompte(Id,IdRessource,Login,MdP) VALUES(:idcompte,:idress,:log,:mdp)";

    QSqlQuery query;
    query = QSqlQuery(getDataBase());
    //On recupere l'id du type de la ressource
    qint32  idType ;
    if(query.exec(requestTType))
    {
         query.next();
         idType= query.value("Id").toString().toInt();
    }
    //On insere la ressource dans la base de données
    query.prepare(requestTRessource);
    query.bindValue(":idres",ressoure.getPERID());
    query.bindValue(":nom",ressoure.getPERNom());
    query.bindValue(":prenom",ressoure.getPERPrenom());
    query.bindValue(":idtype",idType);
    if(query.exec())
    {
        qDebug("Insert new Ressource !!");
    }
    closeConnection();
    // si C'est un informaticien la ressource , je lui cree un compte
    if(!ressoure.getLogin().isEmpty() && !ressoure.getMotPasse().isEmpty())
    {
        qint32 lastIdTCompte= lastIdTable("TCompte") ;
        createConnection();
        QSqlQuery query2;
        query2 = QSqlQuery(getDataBase());
        query2.prepare(requestTCompte);
        query2.bindValue(":idcompte",lastIdTCompte+1);
        query2.bindValue(":idress",ressoure.getPERID());
        query2.bindValue(":log",ressoure.getLogin());
        query2.bindValue(":mdp",ressoure.getMotPasse());
        query2.exec();
         closeConnection();
    }

}
