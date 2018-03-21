#ifndef INTERFACEDB_RESOURCE_H
#define INTERFACEDB_RESOURCE_H
#include "interfacedb.h"
#include "ressource.h"
enum
{
    TRessource_id = 0,
    TRessource_Nom = 1 ,
    TRessource_Prenom = 2,
    TRessource_idType = 3
};
class interfacedb_Resource:public InterfaceDB
{
public:
    interfacedb_Resource();
    QStandardItemModel  * getAllRessource(qint32 id=-1);
    QStandardItemModel * getAllRessource_TreeView();
    void addStaffToResourceTable(Ressource ressoure, QString type);
    QStringList getRessourceByid(qint32 id);
    void deleteCompteofResource(qint32 idresource);
    QStringList getCompteByResourceid(qint32 id);

};

#endif // INTERFACEDB_RESOURCE_H
