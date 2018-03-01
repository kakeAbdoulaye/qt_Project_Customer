#include "addstaffgui.h"
#include "ui_addstaffgui.h"

#include <iostream>
AddStaffGUI::AddStaffGUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStaffGUI)
{
    ui->setupUi(this);
    addModelToCombox();
    connect(ui->comboBoxType,SIGNAL(currentTextChanged(QString)),this,SLOT(activeGroupBox(QString)));
}

AddStaffGUI::~AddStaffGUI()
{
    delete ui;
}

void AddStaffGUI::addModelToCombox()
{
    InterfaceDB dataBase ;
    dataBase.createConnection();
    QSqlTableModel * modelCombox = dataBase.getAllType();
    ui->comboBoxType->setModel(modelCombox);
    ui->comboBoxType->setModelColumn(modelCombox->fieldIndex("label"));

}
void AddStaffGUI::activeGroupBox(QString select)
{
    if(select == "Informaticien")
    {
        ui->groupBoxAuthentication->setEnabled(true);
    }
    else
    {
        ui->groupBoxAuthentication->setEnabled(false);
    }
}
