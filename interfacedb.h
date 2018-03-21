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



enum TCompte
{
    TCompte_id = 0 ,
    TCompte_IdRessource = 1 ,
    TCompte_Login =2,
    TCompte_MdP=3
};
enum TType
{
    TType_Id = 0 ,
    TType_Label = 1

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
    QSqlTableModel * getAllType();
    qint32 lastIdTable(QString TableName);
    qint32 getSizeTable(QString TableName);
    void deleteToTable(QString TableName , qint32 id);
    QSqlDatabase getDataBase(){return dataBase;}
    QStringList getTypeByid(qint32 id);
private :

    QSqlDatabase dataBase ;
    QSqlQuery query;
    //QWidget *parent ;

};

#endif // INTERFACEDB_H
