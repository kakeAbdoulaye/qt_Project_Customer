#include "addstaffgui.h"
#include "ui_addstaffgui.h"
#include <iostream>


AddStaffGUI::AddStaffGUI(QWidget *parent,qint32 id) :
    QDialog(parent),
    ui(new Ui::AddStaffGUI)
{
    ui->setupUi(this);
    this->idRess = id;
    init();
    connect(ui->comboBoxType,SIGNAL(currentTextChanged(QString)),this,SLOT(activeGroupBox(QString)));
    connect(ui->comboBoxType,SIGNAL(activated(QString)),this,SLOT(activeGroupBox(QString)));
    activeGroupBox(ui->comboBoxType->currentText());
}

AddStaffGUI::~AddStaffGUI()
{
    delete ui;
}

void AddStaffGUI::init()
{
    QSqlTableModel * modelCombox ;
    if(idRess == -1)
    {
        modelCombox = dataBase_Resource.getAllType();
        ui->comboBoxType->setModel(modelCombox);
        ui->comboBoxType->setModelColumn(modelCombox->fieldIndex("label"));

    }
    else
    {
        QStringList data = this->dataBase_Resource.getRessourceByid(idRess);

        QString type = data.at(TRessource_idType);
        ui->lineEditName->setText(data.at(TRessource_Nom));
        ui->lineEditFirstName->setText(data.at(TRessource_Prenom));

        modelCombox = dataBase_Resource.getAllType();
        ui->comboBoxType->setModel(modelCombox);
        ui->comboBoxType->setModelColumn(modelCombox->fieldIndex("label"));
        data = dataBase_Resource.getTypeByid(type.toInt());
        ui->comboBoxType->setCurrentText(data.at(TType_Label));

        if(ui->comboBoxType->currentText() == "Informaticien")
        {
            data = this->dataBase_Resource.getCompteByResourceid(idRess);
            ui->lineEditLogin->setText(data.at(TCompte_Login));
            ui->lineEditPassword->setText(data.at(TCompte_MdP));
        }
    }
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
    QString name = ui->lineEditName->text();
    QString fname = ui->lineEditFirstName->text();
    QString login = ui->lineEditLogin->text();
    QString password = ui->lineEditPassword->text();
    QString type = ui->comboBoxType->currentText();
    if(idRess == -1)//si on cree la ressource pour la premiere fois
    {
        // je lui donne un id de ressource
        idRess = dataBase_Resource.lastIdTable("TRessource") +1 ;
        Ressource newRessource(idRess,name,fname,login,password);
        dataBase_Resource.addStaffToResourceTable(newRessource,type);
    }
    else
    {
        dataBase_Resource.deleteToTable("TRessource",idRess);
        dataBase_Resource.deleteCompteofResource(idRess);
        Ressource newRessource(idRess,name,fname,login,password);
        dataBase_Resource.addStaffToResourceTable(newRessource,type);
    }

}
void AddStaffGUI::on_buttonBox_accepted()
{
    addStaff();
}
