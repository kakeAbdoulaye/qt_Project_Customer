#ifndef ADDCUSTOMERGUI_H
#define ADDCUSTOMERGUI_H

#include <QDialog>

namespace Ui {
class AddCustomerGUI;
}

class AddCustomerGUI : public QDialog
{
    Q_OBJECT

public:
    explicit AddCustomerGUI(QWidget *parent = 0);
    ~AddCustomerGUI();

private:
    Ui::AddCustomerGUI *ui;
 private slots:
    void upCaseforLetter(QString line);

};

#endif // ADDCUSTOMERGUI_H
