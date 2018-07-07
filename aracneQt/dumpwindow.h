#ifndef DUMPWINDOW_H
#define DUMPWINDOW_H

#include <QDialog>

namespace Ui {
class DumpWindow;
}

class DumpWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DumpWindow(QWidget *parent = 0);
    ~DumpWindow();

private:
    Ui::DumpWindow *ui;
};

#endif // DUMPWINDOW_H
