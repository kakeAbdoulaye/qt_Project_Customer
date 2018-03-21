#ifndef APPLICATIONCENTRALE_H
#define APPLICATIONCENTRALE_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

#include "addcustomergui.h"
#include "addstaffgui.h"
#include "windowsabout.h"
#include "interfacedb_resource.h"
#include "interfacedb_customer.h"

namespace Ui {
class ApplicationCentrale;
}

class ApplicationCentrale : public QMainWindow
{
    Q_OBJECT

public:
    explicit ApplicationCentrale(QWidget *parent = 0);
    ~ApplicationCentrale();

private:
    Ui::ApplicationCentrale *ui;
    QActionGroup * actionGroup ;
    QSqlTableModel * modelSQl;
    QStandardItemModel * modelSTANITEM;
    interfacedb_Customer  dataBase_Customer ;
    interfacedb_Resource  dataBase_Resource;
    qint32 idUser = - 1;
    qint32 idRessource = - 1;


    void initGroupAction();
    void initTreeViewPerson();
    void initTableViewCustomer();

private slots:
    void exitApplication();
    void manageAction(QAction * sender);
    void filtered();
    void on_ButtonLoadTableCustomer_clicked();
    void on_ButtonAddCustomer_clicked();
    void on_Button_AddPerson_clicked();
    void on_ButtonEditCustomer_clicked();
    void on_ButtonDeleteCustomer_clicked();
    void on_Button_EditPerson_clicked();
    void on_Button_Delete_clicked();
    void LoadTreeViewPerson_clicked();
};

#endif // APPLICATIONCENTRALE_H
