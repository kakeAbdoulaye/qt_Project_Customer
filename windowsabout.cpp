#include "windowsabout.h"
#include "ui_windowsabout.h"

WindowsAbout::WindowsAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WindowsAbout)
{
    ui->setupUi(this);
}

WindowsAbout::~WindowsAbout()
{
    delete ui;
}
