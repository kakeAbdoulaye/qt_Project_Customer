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
    QSqlTableModel * getAllType(qint32 id=-1);
    qint32 lastIdTable(QString TableName);
    qint32 getSizeTable(QString TableName);
    QSqlDatabase getDataBase(){return dataBase;}

private :

    QSqlDatabase dataBase ;
    QSqlQuery query;
    //QWidget *parent ;

};

#endif // INTERFACEDB_H
