#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "spiderwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSpider_triggered()
{
    spiderWindow = new SpiderWindow(this);
    spiderWindow->show();
}

void MainWindow::on_actionDump_triggered()
{
    dumpWindow = new DumpWindow(this);
    dumpWindow->show();
}
