#include "interfacedb_customer.h"

interfacedb_Customer::interfacedb_Customer()
{

}
QSqlTableModel * interfacedb_Customer::getAllCustomer()
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
QSqlTableModel * interfacedb_Customer::getAllCustomerFiltered(QString name, QString fname, QString date1, QString date2, qint32 id)
{
    QString nameSearch ="";
    QString fnameSearch ="";
    QString dateSearch ="";
    QString idSearch ="";

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
    if(!name.isEmpty() && !name.isNull())
    {
        nameSearch = QString("Nom like '%%1%' ").arg(name);
    }
    if(!fname.isNull() && !fname.isEmpty())
    {
        if(!nameSearch.isEmpty())
        {
            fnameSearch = QString("or Prenom like '%%1%'").arg(fname);
        }
        else
        {
            fnameSearch = QString("Prenom like '%%1%'").arg(fname);
        }
    }
    if(!date1.isNull() && !date1.isEmpty() && !date2.isNull() && !date2.isEmpty())
    {
        if(!nameSearch.isEmpty() ||!fnameSearch.isEmpty())
        {
            dateSearch = QString("or DateRdv BETWEEN '%1' and '%2'").arg(date1).arg(date2);
        }
        else
        {
            dateSearch = QString("DateRdv BETWEEN '%1' and '%2'").arg(date1).arg(date2);
        }
    }
    if(id != 0)
    {
        if(!nameSearch.isEmpty() ||!fnameSearch.isEmpty() ||!dateSearch.isEmpty())
        {
            idSearch = QString("or Id='%1'").arg(id);
        }
        else
        {
            idSearch = QString("Id='%1'").arg(id);
        }
    }
    if(!nameSearch.isEmpty() ||!fnameSearch.isEmpty() ||!dateSearch.isEmpty() || !idSearch.isEmpty())
    {
         model->setFilter(nameSearch+fnameSearch+dateSearch+idSearch);
    }
    model->select();
    closeConnection();
    return model;
}
qint32 interfacedb_Customer::lastIdofCustomerTable()
{
    createConnection();
    QSqlQuery query;
    QString request ="SELECT id as LastID FROM TClient ORDER BY id DESC LIMIT 1";
    qint32 lastid;
    if(query.exec(request))
    {
        query.next();
        lastid= query.value("LastID").toString().toInt();
    }
    closeConnection();
   return lastid;
}
void interfacedb_Customer::addCustomerToCustomerTable(Client *client, QString dateRDV)
{
    createConnection();
    QString requestTClient = "INSERT INTO TClient (Id,Nom,Prenom,Adresse,Ville,CP,Commentaire,Tel,DateRdv,DureeRdv,Priorite)VALUES(:iduser,:nom,:prenom,:adr,:ville,:cp,:com,:tel,:daterdv,:duree,:prio);";
    QString requestTRdv= "INSERT INTO TRdv (Id,IdClient,IdRessource) VALUES(:id,:iduser,:idress)";
    QSqlQuery query;
    query = QSqlQuery(getDataBase());
    query.prepare(requestTClient);
    query.bindValue(":iduser",client->getPATPersonne().getPERID());
    query.bindValue(":nom",client->getPATPersonne().getPERNom());
    query.bindValue(":prenom",client->getPATPersonne().getPERPrenom());
    query.bindValue(":adr",client->getPATAdresse().getADRAdresse());
    query.bindValue(":ville",client->getPATAdresse().getADRVille());
    query.bindValue(":cp",client->getPATAdresse().getADRCodePostale());
    query.bindValue(":com",client->getPATCommentaire());
    query.bindValue(":tel",client->getPATPersonne().getPERTelephone());
    query.bindValue(":daterdv",dateRDV);
    query.bindValue(":duree",client->getPATDureeConsultation());
    query.bindValue(":prio",client->getPATPriorite());
    if(query.exec())
    {
        qDebug("Insert new customer !!");
    }
    closeConnection();
    qint32 lastIdTRdv =lastIDofTableRdv() ;
    createConnection();
    QSqlQuery query2;
    query2 = QSqlQuery(getDataBase());
    for(qint32 myIterator = 0 ;myIterator < client->getNombreRessource(); ++myIterator)
    {
        query2.prepare(requestTRdv);
        query2.bindValue(":id",lastIdTRdv+myIterator+1);
        query2.bindValue(":iduser",client->getPATPersonne().getPERID());
        query2.bindValue(":idress",client->getPATVecRessource().at(myIterator));
        query2.exec();
    }
     closeConnection();
}
