#ifndef CONNEXIONUSER_H
#define CONNEXIONUSER_H

#include <QDialog>
#include "applicationcentrale.h"
#include <QMessageBox>
namespace Ui {
class ConnexionUser;
}

class ConnexionUser : public QDialog
{
    Q_OBJECT

public:
    explicit ConnexionUser(QWidget *parent = 0);
    ~ConnexionUser();

private:
    Ui::ConnexionUser *ui;
    bool checkLoginPassword();
private slots:
    void exitConnexion();
    void wantToConnect();
};

#endif // CONNEXIONUSER_H
