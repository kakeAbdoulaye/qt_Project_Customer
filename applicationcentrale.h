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
    interfacedb_Customer * dataBase_Customer ;
    interfacedb_Resource  * dataBase_Resource;


    void initGroupAction();
    void initTreeViewPerson();
    void initTableViewCustomer();

private slots:
    void exitApplication();
    void manageAction(QAction * sender);
    void filtered();
    void on_ButtonLoadTableCustomer_clicked(bool checked);
};

#endif // APPLICATIONCENTRALE_H
