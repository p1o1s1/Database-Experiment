#include "vipr.h"
#include "ui_vipr.h"

vipr::vipr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vipr)
{
    ui->setupUi(this);
}

vipr::~vipr()
{
    delete ui;
}
