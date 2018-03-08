#include "addcustomergui.h"
#include "ui_addcustomergui.h"
#include<QString>
//#include <QSqlTableModel>
#include "interfacedb.h"
AddCustomerGUI::AddCustomerGUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCustomerGUI)
{
    ui->setupUi(this);
    //uniquement de chiffres
    ui->lineEditPostCode->setValidator(new QIntValidator(0,99999,this));
    ui->lineEditTelephone->setValidator(new QIntValidator(0,999999999,this));
    QDate today = QDate::currentDate();
    ui->dateEditDateRendezVous->setDateRange(today,ui->dateEditDateRendezVous->maximumDate());
    InterfaceDB bd ;
    QSqlTableModel * tt = bd.getAllRessource();
    ui->comboBoxlistResource->setModel(tt);
    ui->comboBoxlistResource->setModelColumn(tt->fieldIndex("nom"));


}

AddCustomerGUI::~AddCustomerGUI()
{
    delete ui;
}

void AddCustomerGUI::upCaseforLetter(QString line)
{
    QString newLine="";
    if(line != ui->lineEditName->text())
    {
       newLine.append(line[0].toUpper());
       ui->lineEditName->setText(newLine);
       emit ui->lineEditName->textChanged(ui->lineEditName->text());
    }
}
