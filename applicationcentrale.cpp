#include "applicationcentrale.h"
#include "ui_applicationcentrale.h"
#include <QMessageBox>
#include <Qt>
#include <QStandardItem>

ApplicationCentrale::ApplicationCentrale(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ApplicationCentrale)
{
    ui->setupUi(this);
    this->dataBase_Customer = new interfacedb_Customer ;
    this->dataBase_Resource = new interfacedb_Resource;
    initGroupAction();
    initTreeViewPerson();
    initTableViewCustomer();
    ui->statusBar->showMessage("You have just connected",15000);
    connect(ui->ButtonSearch,SIGNAL(clicked(bool)),this,SLOT(filtered()));
}

ApplicationCentrale::~ApplicationCentrale()
{
    delete ui;
}
void ApplicationCentrale::initGroupAction()
{
    this->actionGroup = new QActionGroup(this);
    connect(actionGroup,SIGNAL(triggered(QAction*)),this,SLOT(manageAction(QAction*)));
    this->actionGroup->addAction(ui->actionCustomer);
    this->actionGroup->addAction(ui->actionStaff);
    this->actionGroup->addAction(ui->actionExit);
    this->actionGroup->addAction(ui->actionAbout);
}
void ApplicationCentrale::manageAction(QAction *sender)
{
    if(sender == ui->actionExit)
    {
        exitApplication();
    }
    else if(sender == ui->actionCustomer)
    {
        AddCustomerGUI * windowsAddCustomer = new AddCustomerGUI(this);
        qint32 value = windowsAddCustomer->exec();
        if( value == QDialog::Accepted)
        {
            ui->statusBar->showMessage("Added Customer ... ",15000);
        }
        else if(value == QDialog::Rejected)
        {
             ui->statusBar->showMessage("Cancelled customer addition ... ",15000);
        }
    }
    else if(sender == ui->actionStaff)
    {
        AddStaffGUI * windowsAddStaff = new AddStaffGUI(this);
        qint32 value = windowsAddStaff->exec();
        if( value == QDialog::Accepted)
        {
            ui->statusBar->showMessage("Added Personn ... ",15000);
        }
        else if(value == QDialog::Rejected)
        {
             ui->statusBar->showMessage("Cancelled person addition ... ",15000);
        }
    }
    else if(sender == ui->actionAbout)
    {
        WindowsAbout * windowInfo = new WindowsAbout(this);
        qint32 value = windowInfo->exec();
        if( value == QDialog::Accepted)
        {
            ui->statusBar->showMessage("You have just read ... ",15000);
        }
        else if(value == QDialog::Rejected)
        {
             ui->statusBar->showMessage("You have just read ... ",15000);
        }
    }
    else
    {

    }

}
void ApplicationCentrale::exitApplication()
{
    this->close();
}

void ApplicationCentrale::initTreeViewPerson()
{
   modelSTANITEM = this->dataBase_Resource->getAllRessource_TreeView() ;
   ui->treeViewPerson->setModel(modelSTANITEM);
}
void ApplicationCentrale::initTableViewCustomer()
{
     modelSQl = this->dataBase_Customer->getAllCustomer() ;
     ui->tableViewCustomer->setModel(modelSQl);
     ui->lineEditIdenSearch->setValidator(new QIntValidator(0,999999999,this));
}
void ApplicationCentrale::filtered()
{
    //liberer lancien model avant
    qint32 TClient_Id = ui->lineEditIdenSearch->text().toInt();
    QString TClient_Nom=ui->lineEditNameSearch->text();
    QString TClient_Prenom=ui->lineEditFisrtNameSearch->text();
    QString TClient_DateRdv1= ui->dateEditSearch1->text();
    QString TClient_DateRdv2=ui->dateEditSearch2->text();
    modelSQl = this->dataBase_Customer->getAllCustomerFiltered(TClient_Nom,TClient_Prenom,TClient_DateRdv1,TClient_DateRdv2,TClient_Id);
    ui->tableViewCustomer->setModel(modelSQl);
    ui->lineEditIdenSearch->setValidator(new QIntValidator(0,999999999,this));
}

void ApplicationCentrale::on_ButtonLoadTableCustomer_clicked(bool checked)
{
    //this->modelSQl;
    //initTableViewCustomer();
    //liberer le model d'avant
}
