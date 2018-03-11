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
    Client * customer ;
    qint32 idPerson;//le dernier id de la base de donnée
    QString namePerson = ui->lineEditName->text();
    QString fnamePerson = ui->lineEditFirstName->text();
    qint32 telPerson = ui->lineEditTelephone->text().toInt();
    QString addressAd = ui->lineEditAddress->text();
    qint32 postalCodeAd = ui->lineEditPostCode->text().toInt();
    QString townAd = ui->lineEditTown->text();
    QString comC = ui->textEditCommentary->toPlainText();
    QTime lenghCon = ui->timeEditDuration->time();
    qint32 priorityC = ui->spinBoxPriority->text().toInt();

}
void AddCustomerGUI::initCustomerData()
{
    ui->lineEditPostCode->setValidator(new QIntValidator(0,99999,this));
    ui->lineEditTelephone->setValidator(new QIntValidator(0,999999999,this));

    if(userId == -1)
    {

        QDate today = QDate::currentDate();
        ui->dateEditDateRendezVous->setDateRange(today,ui->dateEditDateRendezVous->maximumDate());
        model = this->dataBase.getAllRessource();
        ui->listViewRessource->setModel(model);
        //ui->listViewRessource->
    }
    else
    {
        QDate today = QDate::currentDate();
        ui->dateEditDateRendezVous->setDateRange(today,ui->dateEditDateRendezVous->maximumDate());
        model = dataBase.getAllRessource(userId);
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
