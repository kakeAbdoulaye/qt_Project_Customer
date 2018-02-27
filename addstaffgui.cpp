#include "addstaffgui.h"
#include "ui_addstaffgui.h"

AddStaffGUI::AddStaffGUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddStaffGUI)
{
    ui->setupUi(this);
}

AddStaffGUI::~AddStaffGUI()
{
    delete ui;
}
