#ifndef INTERFACEDB_CUSTOMER_H
#define INTERFACEDB_CUSTOMER_H
#include "interfacedb.h"
#include "client.h"
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
class interfacedb_Customer : public InterfaceDB
{
public:
    interfacedb_Customer();
    QSqlTableModel * getAllCustomer();
    QSqlTableModel * getAllCustomerFiltered(QString name,QString fname,QString date1 , QString date2 ,qint32 id);
    void addCustomerToCustomerTable(Client * client, QString dateRDV);
    void deleteRdvofCustomer(qint32 idcustomer);
    QStringList getCustomerByid(qint32 id);


};

#endif // INTERFACEDB_CUSTOMER_H
