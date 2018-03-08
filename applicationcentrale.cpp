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
    initGroupAction();
    initTreeViewPerson();
    initTableViewCustomer();
    ui->statusBar->showMessage("You have just connected",15000);
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
    InterfaceDB dataBase ;
    QStandardItemModel * monModel = dataBase.getAllRessource_TreeView() ;
    ui->treeViewPerson->setModel(monModel);
}
void ApplicationCentrale::initTableViewCustomer()
{
     InterfaceDB dataBase ;
     QSqlTableModel * model = dataBase.getAllCustomer() ;
     ui->listViewCustomer->setModel(model);
}




