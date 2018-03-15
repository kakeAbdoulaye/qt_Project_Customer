#include "connexionuser.h"
#include "c_init_bd.h"
#include <QApplication>
#include <QtSql>
#include <QStandardItemModel>
#include <QTableView>
#include <QVBoxLayout>
#include <iostream>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   // ApplicationCentrale w;
   // w.show();
    //C_INIT_BD::Creation_BD();
   ConnexionUser user;
    user.exec();

   // AddCustomerGUI gui ;
    //gui.exec();
    //AddStaffGUI staff ;
    //staff.exec();
    return a.exec();


    //return 0 ;

}
