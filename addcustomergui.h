#ifndef ADDCUSTOMERGUI_H
#define ADDCUSTOMERGUI_H

#include "client.h"
#include <QDialog>
#include <QStandardItemModel>
#include<QString>
#include <QMessageBox>
#include "interfacedb_resource.h"
#include "interfacedb_customer.h"

namespace Ui {
class AddCustomerGUI;
}

class AddCustomerGUI : public QDialog
{
    Q_OBJECT

public:
    explicit AddCustomerGUI(QWidget *parent = 0,qint32 userIden=-1);
    ~AddCustomerGUI();

private:
    Ui::AddCustomerGUI *ui;
    qint32 userId;
    QStandardItemModel * model ;
    interfacedb_Customer dataBase_Customer ;
    interfacedb_Resource dataBase_Resource;

     void initCustomerData();
     void reset();
 private slots:
    void addCustomer();
    bool check();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
};

#endif // ADDCUSTOMERGUI_H
