#ifndef APPLICATIONCENTRALE_H
#define APPLICATIONCENTRALE_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>

#include "addcustomergui.h"
#include "addstaffgui.h"
#include "windowsabout.h"
namespace Ui {
class ApplicationCentrale;
}

class ApplicationCentrale : public QMainWindow
{
    Q_OBJECT

public:
    explicit ApplicationCentrale(QWidget *parent = 0);
    ~ApplicationCentrale();

private:
    Ui::ApplicationCentrale *ui;
    QActionGroup * actionGroup ;


    void initGroupAction();
    void initTreeViewPerson();
    void initTableViewCustomer();

private slots:
    void exitApplication();
    void manageAction(QAction * sender);
};

#endif // APPLICATIONCENTRALE_H
