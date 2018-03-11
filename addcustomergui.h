#ifndef ADDCUSTOMERGUI_H
#define ADDCUSTOMERGUI_H

#include "client.h"
#include <QDialog>
#include <QStandardItemModel>
#include<QString>
#include "interfacedb.h"

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
    InterfaceDB dataBase ;

     void initCustomerData();
 private slots:
    void upCaseforLetter(QString line);
    void addCustomer();
};

#endif // ADDCUSTOMERGUI_H
