#ifndef INTERFACEDB_H
#define INTERFACEDB_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlRecord>
#include <QFile>
#include <QSqlTableModel>

class InterfaceDB
{
public:
    InterfaceDB();
    bool createConnection();
    bool checkLoginPasswordDB(QString login , QString password);
    QSqlTableModel * getAllRessource();
    QSqlTableModel * getAllType();

private :
    QSqlDatabase dataBase ;
    QSqlQuery query;

};

#endif // INTERFACEDB_H
