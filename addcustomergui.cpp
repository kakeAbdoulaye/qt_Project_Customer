#include "addcustomergui.h"
#include "ui_addcustomergui.h"

AddCustomerGUI::AddCustomerGUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddCustomerGUI)
{
    ui->setupUi(this);
}

AddCustomerGUI::~AddCustomerGUI()
{
    delete ui;
}
