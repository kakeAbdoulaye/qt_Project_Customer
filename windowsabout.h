#ifndef WINDOWSABOUT_H
#define WINDOWSABOUT_H

#include <QDialog>

namespace Ui {
class WindowsAbout;
}

class WindowsAbout : public QDialog
{
    Q_OBJECT

public:
    explicit WindowsAbout(QWidget *parent = 0);
    ~WindowsAbout();

private:
    Ui::WindowsAbout *ui;
};

#endif // WINDOWSABOUT_H
