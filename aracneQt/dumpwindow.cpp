#include "dumpwindow.h"
#include "ui_dumpwindow.h"

DumpWindow::DumpWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DumpWindow)
{
    ui->setupUi(this);
}

DumpWindow::~DumpWindow()
{
    delete ui;
}
