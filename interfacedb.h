#ifndef INTERFACEDB_H
#define INTERFACEDB_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlRecord>
#include <QFile>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>
#include <QStandardItem>
#include <QDebug>
#include <QMap>
#include <iostream>
using namespace std;

enum TClient
{
    TClient_Id =0 ,
    TClient_Nom=1,
    TClient_Prenom=2,
    TClient_Adresse =3,
    TClient_Ville=4,
    TClient_CP = 5 ,
    TClient_Commentaire = 6,
    TClient_Tel=7,
    TClient_DateRdv=8,
    TClient_DureeRdv=9,
    TClient_Priorite=10
};
enum
{
    TRessource_id = 0,
    TRessource_Nom = 1 ,
    TRessource_Prenom = 2,
    TRessource_idType = 3
};
enum TCompte
{

};
enum TType
{

};
enum TRdv
{

};
class InterfaceDB
{
public:
    InterfaceDB();
    bool createConnection();
    bool closeConnection();
    bool checkLoginPasswordDB(QString login , QString password);
    QStandardItemModel  * getAllRessource(qint32 id=-1);
    QStandardItemModel * getAllRessource_TreeView();
    QSqlTableModel * getAllType(qint32 id=-1);
    QSqlTableModel * getAllCustomer();
    QSqlTableModel * getAllCustomerFiltered(QString name,QString fname,QString date1 , QString date2 ,qint32 id);

private :
    QSqlDatabase dataBase ;
    QSqlQuery query;
    //QWidget *parent ;

};

#endif // INTERFACEDB_H
