#include "connexionuser.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //ApplicationCentrale w;
   // w.show();
   ConnexionUser user;
    user.exec();

    return a.exec();
}
