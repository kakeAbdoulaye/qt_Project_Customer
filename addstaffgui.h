#ifndef ADDSTAFFGUI_H
#define ADDSTAFFGUI_H

#include <QDialog>
#include "interfacedb_resource.h"
#include "interfacedb_customer.h"
#include "ressource.h"

namespace Ui {
class AddStaffGUI;
}

class AddStaffGUI : public QDialog
{
    Q_OBJECT

public:
    explicit AddStaffGUI(QWidget *parent = 0, qint32 id=-1);
    ~AddStaffGUI();
    void addStaff();

private:
    Ui::AddStaffGUI *ui;
    qint32 idRess  ;
    void init();
    interfacedb_Customer dataBase_Customer ;
    interfacedb_Resource dataBase_Resource;
signals:
    void emitActiveGroupBox(QString select);
private slots:
    void activeGroupBox(QString select);

    void on_buttonBox_accepted();

};

#endif // ADDSTAFFGUI_H
