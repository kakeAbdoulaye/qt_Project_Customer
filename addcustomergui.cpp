#include "addcustomergui.h"
#include "ui_addcustomergui.h"

AddCustomerGUI::AddCustomerGUI(QWidget *parent,qint32 userIden) :
    QDialog(parent),
    ui(new Ui::AddCustomerGUI)
{
    ui->setupUi(this);
    userId = userIden;
    initCustomerData();
}

AddCustomerGUI::~AddCustomerGUI()
{
    delete ui;
}
void AddCustomerGUI::addCustomer()
{
    if(check())
    {
        qint32 idPerson = this->dataBase_Customer.lastIdTable("TClient");//le dernier id de la table Client
        QString namePerson = ui->lineEditName->text();
        QString fnamePerson = ui->lineEditFirstName->text();
        QString tel = ui->lineEditTelephone->text();

        QString addressAd = ui->lineEditAddress->text();
        QString pCode = ui->lineEditPostCode->text();
        QString townAd = ui->lineEditTown->text();


        QString comC = ui->textEditCommentary->toPlainText();
        QTime lenghCon = ui->timeEditDuration->time();
        qint32 priorityC = ui->spinBoxPriority->text().toInt();

        qint32 telPerson = tel.toInt();
        qint32 postalCodeAd = pCode.toInt();

        Adresse * address = new Adresse(addressAd,townAd,postalCodeAd);

        Client * customer  ;
        if(userId == -1 )
        {
            customer = new Client(idPerson+1,namePerson,fnamePerson,telPerson,*address,lenghCon,priorityC,comC) ;
        }
        else
        {
            dataBase_Customer.deleteToTable("TClient",userId);
            dataBase_Customer.deleteRdvofCustomer(userId);
            customer = new Client(userId,namePerson,fnamePerson,telPerson,*address,lenghCon,priorityC,comC) ;
        }
        qint32 sizeResourceTable = this->dataBase_Resource.getSizeTable("TRessource");
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
        this->dataBase_Customer.addCustomerToCustomerTable(customer,dateRDV);
    }
}
void AddCustomerGUI::initCustomerData()
{
    ui->lineEditPostCode->setValidator(new QIntValidator(0,99999,this));
    ui->lineEditTelephone->setValidator(new QIntValidator(0,999999999,this));

    if(userId == -1)
    {
        this->reset();
    }
    else
    {

        QStringList data = this->dataBase_Customer.getCustomerByid(userId);
        ui->dateEditDateRendezVous->setDateRange(QDate::fromString(data.at(TClient_DateRdv),"yyyy-MM-dd"),ui->dateEditDateRendezVous->maximumDate());
        model = this->dataBase_Resource.getAllRessource(userId);
        ui->listViewRessource->setModel(model);

        ui->lineEditName->setText(data.at(TClient_Nom));
        ui->lineEditFirstName->setText(data.at(TClient_Prenom));
        ui->lineEditTelephone->setText(data.at(TClient_Tel));

         ui->lineEditAddress->setText(data.at(TClient_Adresse));
         ui->lineEditPostCode->setText(data.at(TClient_CP));
         ui->lineEditTown->setText(data.at(TClient_Ville));

         ui->textEditCommentary->setPlainText(data.at(TClient_Commentaire));
         //ui->timeEditDuration->setTime(QTime t());
         QString prio =data.at(TClient_Priorite) ;
         ui->spinBoxPriority->setValue(prio.toInt());

    }

}
bool AddCustomerGUI::check()
{
    QString namePerson = ui->lineEditName->text();
    QString fnamePerson = ui->lineEditFirstName->text();
    qint32 count = 0 ;

    QString addressAd = ui->lineEditAddress->text();
    QString pCode = ui->lineEditPostCode->text();
    QString townAd = ui->lineEditTown->text();

    qint32 sizeResourceTable = this->dataBase_Resource.getSizeTable("TRessource");
    QStandardItemModel * model = dynamic_cast<QStandardItemModel *>(ui->listViewRessource->model());
    for(qint32 index = 0 ;index < sizeResourceTable ;++index)
    {
        QStandardItem * myItem = model->item(index,0);
        if(myItem->checkState() == Qt::Checked )
        {
            ++count;
        }
    }

    if(!namePerson.isEmpty() && !fnamePerson.isEmpty() && !addressAd.isEmpty()
            && !pCode.isEmpty()&& !townAd.isEmpty() && count>0)
    {

        return true;
    }
    else
    {
        return false;
    }
}
void AddCustomerGUI::reset()
{

    QDate today = QDate::currentDate();
    ui->dateEditDateRendezVous->setDateRange(today,ui->dateEditDateRendezVous->maximumDate());
    model = this->dataBase_Resource.getAllRessource();
    ui->listViewRessource->setModel(model);
    ui->lineEditName->setText("");
    ui->lineEditFirstName->setText("");
    ui->lineEditTelephone->setText("");
     ui->lineEditAddress->setText("");
     ui->lineEditPostCode->setText("");
     ui->lineEditTown->setText("");
     ui->textEditCommentary->setPlainText("");
     //ui->timeEditDuration->setTime(QTime t());
     ui->spinBoxPriority->setValue(1);

}
void AddCustomerGUI::on_buttonBox_accepted()
{
    addCustomer();
}

void AddCustomerGUI::on_buttonBox_rejected()
{
     userId =-1;
     reset();
}
