#ifndef SPIDERWINDOW_H
#define SPIDERWINDOW_H

#include <QDialog>

namespace Ui {
class SpiderWindow;
}

class SpiderWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SpiderWindow(QWidget *parent = 0);
    ~SpiderWindow();

private:
    Ui::SpiderWindow *ui;
};

#endif // SPIDERWINDOW_H
