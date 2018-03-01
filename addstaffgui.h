#ifndef ADDSTAFFGUI_H
#define ADDSTAFFGUI_H

#include <QDialog>
#include "interfacedb.h"

namespace Ui {
class AddStaffGUI;
}

class AddStaffGUI : public QDialog
{
    Q_OBJECT

public:
    explicit AddStaffGUI(QWidget *parent = 0);
    ~AddStaffGUI();

private:
    Ui::AddStaffGUI *ui;
    void addModelToCombox();
private slots:
    void activeGroupBox(QString select);

};

#endif // ADDSTAFFGUI_H
