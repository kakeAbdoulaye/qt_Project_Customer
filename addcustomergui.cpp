#include "addcustomergui.h"
#include "ui_addcustomergui.h"

AddCustomerGUI::AddCustomerGUI(QWidget *parent,qint32 userIden) :
    QDialog(parent),
    ui(new Ui::AddCustomerGUI)
{
    ui->setupUi(this);
    userId = userIden;
    this->dataBase_Resource = new interfacedb_Resource;
    this->dataBase_Customer = new interfacedb_Customer;
    initCustomerData();
}

AddCustomerGUI::~AddCustomerGUI()
{
    delete ui;
}
void AddCustomerGUI::addCustomer()
{
    qint32 idPerson = this->dataBase_Customer->lastIdofCustomerTable() ;//le dernier id de la table Client
    QString namePerson = ui->lineEditName->text();
    QString fnamePerson = ui->lineEditFirstName->text();
    qint32 telPerson = ui->lineEditTelephone->text().toInt();
    Personne * person = new Personne(idPerson+1,namePerson,fnamePerson,telPerson);

    QString addressAd = ui->lineEditAddress->text();
    qint32 postalCodeAd = ui->lineEditPostCode->text().toInt();
    QString townAd = ui->lineEditTown->text();
    Adresse * address = new Adresse(addressAd,townAd,postalCodeAd);

    QString comC = ui->textEditCommentary->toPlainText();
    QTime lenghCon = ui->timeEditDuration->time();
    qint32 priorityC = ui->spinBoxPriority->text().toInt();
    Client * customer = new Client(*person,*address,lenghCon,priorityC,comC) ;

    qint32 sizeResourceTable = this->dataBase_Resource->getSizeTableRessource();
    QStandardItemModel * model = dynamic_cast<QStandardItemModel *>(ui->listViewRessource->model());
    for(qint32 index = 0 ;index < sizeResourceTable ;++index)
    {
        QStandardItem * myItem = model->item(index,0);
        if(myItem->checkState() == Qt::Checked )
        {
            qint32 idResource = myItem->text().left(myItem->text().indexOf(" ")).trimmed().toInt();
            customer->ajouterIdenRessource(idResource);
        }
    }

    QString dateRDV = ui->dateEditDateRendezVous->text();
    this->dataBase_Customer->addCustomerToCustomerTable(customer,dateRDV);

}
void AddCustomerGUI::initCustomerData()
{
    ui->lineEditPostCode->setValidator(new QIntValidator(0,99999,this));
    ui->lineEditTelephone->setValidator(new QIntValidator(0,999999999,this));

    if(userId == -1)
    {

        QDate today = QDate::currentDate();
        ui->dateEditDateRendezVous->setDateRange(today,ui->dateEditDateRendezVous->maximumDate());
        model = this->dataBase_Resource->getAllRessource();
        ui->listViewRessource->setModel(model);
    }
    else
    {
        QDate today = QDate::currentDate();
        ui->dateEditDateRendezVous->setDateRange(today,ui->dateEditDateRendezVous->maximumDate());
        model = this->dataBase_Resource->getAllRessource(userId);
        ui->listViewRessource->setModel(model);
    }

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

void AddCustomerGUI::on_buttonBox_accepted()
{
    QMessageBox::warning(0,"Error","Forget some information , fill all champ please !!!");

    //addCustomer();
}
/* QModelIndex  myIndex= myItem->index();
        //qDebug()<<myItem->text();
        qDebug()<<myItem->text().left(myItem->text().indexOf(" ")).trimmed().toInt();
        //qDebug()<<myIndex.data(Qt::DisplayRole).toString().length();

                //if(model->item(1,0)->checkState()==Qt::Checked)
                   // qDebug()<<myItem->accessibleText();*/
