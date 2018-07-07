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
    SpiderWindow sWindow;
    sWindow.setModal(true);
    sWindow.exec();
}
