#include "addstaffgui.h"
#include "ui_addstaffgui.h"
#include <iostream>


AddStaffGUI::AddStaffGUI(QWidget *parent,qint32 id) :
    QDialog(parent),
    ui(new Ui::AddStaffGUI)
{
    ui->setupUi(this);
    this->idRess = id;
    addModelToCombox();
    connect(ui->comboBoxType,SIGNAL(currentTextChanged(QString)),this,SLOT(activeGroupBox(QString)));
    connect(ui->comboBoxType,SIGNAL(activated(QString)),this,SLOT(activeGroupBox(QString)));

}

AddStaffGUI::~AddStaffGUI()
{
    delete ui;
}

void AddStaffGUI::addModelToCombox()
{
    InterfaceDB dataBase ;
    QSqlTableModel * modelCombox = dataBase.getAllType(this->idRess);
    ui->comboBoxType->setModel(modelCombox);
    ui->comboBoxType->setModelColumn(modelCombox->fieldIndex("label"));
    activeGroupBox(ui->comboBoxType->currentText());
}
void AddStaffGUI::activeGroupBox(QString select)
{
    if(select.trimmed() == "Informaticien")
    {
        ui->groupBoxAuthentication->setEnabled(true);
    }
    else
    {
        ui->groupBoxAuthentication->setEnabled(false);
    }
}

void AddStaffGUI::addStaff()
{
    interfacedb_Resource dataBase;
    QString name = ui->lineEditName->text();
    QString fname = ui->lineEditFirstName->text();
    QString login = ui->lineEditLogin->text();
    QString password = ui->lineEditPassword->text();
    QString type = ui->comboBoxType->currentText();
    if(idRess == -1)// si on cree la ressource pour la premiere fois
    {
        // je lui donne un id de ressource
        idRess = dataBase.lastIdTable("TRessource") +1 ;
    }

    Ressource newRessource(idRess,name,fname,login,password);
    dataBase.addStaffToResourceTable(newRessource,type);


}
void AddStaffGUI::on_buttonBox_accepted()
{
    addStaff();
}
/* QModelIndex  myIndex= myItem->index();
        //qDebug()<<myItem->text();
        qDebug()<<myItem->text().left(myItem->text().indexOf(" ")).trimmed().toInt();
        //qDebug()<<myIndex.data(Qt::DisplayRole).toString().length();

                //if(model->item(1,0)->checkState()==Qt::Checked)
                   // qDebug()<<myItem->accessibleText();*/
