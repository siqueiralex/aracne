#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "spiderwindow.h"
#include "dumpwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionSpider_triggered();

    void on_actionDump_triggered();

    void on_lineEdit_2_returnPressed();

private:
    Ui::MainWindow *ui;
    SpiderWindow *spiderWindow;
    DumpWindow *dumpWindow;
};

#endif // MAINWINDOW_H
