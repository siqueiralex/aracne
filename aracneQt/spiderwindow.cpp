#include "spiderwindow.h"
#include "ui_spiderwindow.h"

SpiderWindow::SpiderWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpiderWindow)
{
    ui->setupUi(this);
}

SpiderWindow::~SpiderWindow()
{
    delete ui;
}
