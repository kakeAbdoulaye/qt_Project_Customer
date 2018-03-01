#include "connexionuser.h"
#include "ui_connexionuser.h"

ConnexionUser::ConnexionUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnexionUser)
{
    ui->setupUi(this);
    connect(ui->buttonAnnule,SIGNAL(clicked()),this,SLOT(exitConnexion()));
    connect(ui->buttonConnexion,SIGNAL(clicked(bool)),this,SLOT(wantToConnect()));
}

ConnexionUser::~ConnexionUser()
{
    delete ui;
}
void ConnexionUser::exitConnexion()
{
    this->close();
}
bool ConnexionUser::checkLoginPassword()
{
    QString login = ui->lineEditLogin->text().trimmed();
    QString password = ui->lineEditPassword->text();

    if(!login.isEmpty() && !password.isEmpty())
    {
        InterfaceDB interface;
        return interface.createConnection() && interface.checkLoginPasswordDB(login,password);
    }
    else
    {
        return false ;
    }
}
void ConnexionUser::wantToConnect()
{
    bool check = this->checkLoginPassword();
    if(check == true)
    {
       ApplicationCentrale * application = new ApplicationCentrale();
       exitConnexion();
       application->show();
    }
    else
    {
        QMessageBox::warning(this,"Error Connection ","Login or Password is incorrect !",QMessageBox::Ok);
        ui->lineEditPassword->setText("");
    }
}
