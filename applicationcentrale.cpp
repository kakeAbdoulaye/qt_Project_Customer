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
    this->modelSQl = new QSqlTableModel(this);
    this->modelSTANITEM= new QStandardItemModel(this);

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
        AddCustomerGUI  windowsAddCustomer(this,idUser);
        qint32 value = windowsAddCustomer.exec();

        if( value == QDialog::Accepted)
        {
            on_ButtonLoadTableCustomer_clicked();
            ui->statusBar->showMessage("Added Customer ... ",15000);
             idUser =-1;
        }
        else if(value == QDialog::Rejected)
        {
             idUser =-1;
             ui->statusBar->showMessage("Cancelled customer addition ... ",15000);
        }
    }
    else if(sender == ui->actionStaff)
    {
        AddStaffGUI  windowsAddStaff(this,idRessource) ;
        qint32 value = windowsAddStaff.exec();
        if( value == QDialog::Accepted)
        {
            LoadTreeViewPerson_clicked();
            ui->statusBar->showMessage("Added Personn ... ",15000);
            idRessource = -1 ;
        }
        else if(value == QDialog::Rejected)
        {
             ui->statusBar->showMessage("Cancelled person addition ... ",15000);
             idRessource = -1 ;
        }
    }
    else if(sender == ui->actionAbout)
    {
        WindowsAbout windowInfo ;
        qint32 value = windowInfo.exec();
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
   modelSTANITEM = this->dataBase_Resource.getAllRessource_TreeView() ;
   ui->treeViewPerson->setModel(modelSTANITEM);
}
void ApplicationCentrale::initTableViewCustomer()
{
     modelSQl = this->dataBase_Customer.getAllCustomer() ;
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
    modelSQl = this->dataBase_Customer.getAllCustomerFiltered(TClient_Nom,TClient_Prenom,TClient_DateRdv1,TClient_DateRdv2,TClient_Id);
    delete(ui->tableViewCustomer->model());
    ui->tableViewCustomer->setModel(modelSQl);
    ui->lineEditIdenSearch->setValidator(new QIntValidator(0,999999999,this));
}

void ApplicationCentrale::on_ButtonLoadTableCustomer_clicked()
{
    delete(ui->tableViewCustomer->model());
    initTableViewCustomer();
}
void ApplicationCentrale::LoadTreeViewPerson_clicked()
{
    delete(ui->treeViewPerson->model());
    initTreeViewPerson();
}
void ApplicationCentrale::on_ButtonAddCustomer_clicked()
{
    emit ui->actionCustomer->triggered();
}

void ApplicationCentrale::on_Button_AddPerson_clicked()
{
    emit ui->actionStaff->triggered();
}

void ApplicationCentrale::on_ButtonEditCustomer_clicked()
{
    QItemSelectionModel * select =  ui->tableViewCustomer->selectionModel();
    if(select->hasSelection())
    {
        QModelIndex index = select->selectedRows().at(0);
        idUser = ui->tableViewCustomer->model()->data(index).toInt();
        ui->tableViewCustomer->clearSelection();
        emit ui->actionCustomer->triggered();
    }
}

void ApplicationCentrale::on_ButtonDeleteCustomer_clicked()
{
    QItemSelectionModel * select =  ui->tableViewCustomer->selectionModel();
    if(select->hasSelection())
    {
        QModelIndex index = select->selectedRows().at(0);
        idUser = ui->tableViewCustomer->model()->data(index).toInt();
        ui->tableViewCustomer->clearSelection();
        dataBase_Customer.deleteToTable("TClient",idUser);
        dataBase_Customer.deleteRdvofCustomer(idUser);
        on_ButtonLoadTableCustomer_clicked();
        idUser =-1;
    }
}

void ApplicationCentrale::on_Button_EditPerson_clicked()
{
     QItemSelectionModel * select = ui->treeViewPerson->selectionModel();
     if(select->hasSelection())
     {
         QModelIndex index = select->selectedRows().at(0);
         QString selected = ui->treeViewPerson->model()->data(index).toString();
         qint32 id = selected.left(selected.indexOf(" ")).trimmed().toInt();
         if(id != 0)
         {
             idRessource = id ;
             ui->treeViewPerson->clearSelection();
             emit ui->actionStaff->triggered();
         }

     }

}

void ApplicationCentrale::on_Button_Delete_clicked()
{
    QItemSelectionModel * select = ui->treeViewPerson->selectionModel();
    if(select->hasSelection())
    {
        QModelIndex index = select->selectedRows().at(0);
        QString selected = ui->treeViewPerson->model()->data(index).toString();
        qint32 id = selected.left(selected.indexOf(" ")).trimmed().toInt();
        if(id != 0)
        {
            idRessource = id ;
            ui->treeViewPerson->clearSelection();
            dataBase_Resource.deleteToTable("TRessource",idRessource);
            dataBase_Resource.deleteCompteofResource(idRessource);
            qDebug("c'est fait");
            idRessource = -1;
            LoadTreeViewPerson_clicked();
        }

    }
}
