#ifndef INTERFACEDB_RESOURCE_H
#define INTERFACEDB_RESOURCE_H
#include "interfacedb.h"
#include "ressource.h"

class interfacedb_Resource:public InterfaceDB
{
public:
    interfacedb_Resource();
    QStandardItemModel  * getAllRessource(qint32 id=-1);
    QStandardItemModel * getAllRessource_TreeView();
    void addStaffToResourceTable(Ressource ressoure, QString type);

};

#endif // INTERFACEDB_RESOURCE_H
