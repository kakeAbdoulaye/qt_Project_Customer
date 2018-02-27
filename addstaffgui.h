#ifndef ADDSTAFFGUI_H
#define ADDSTAFFGUI_H

#include <QDialog>

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
};

#endif // ADDSTAFFGUI_H
