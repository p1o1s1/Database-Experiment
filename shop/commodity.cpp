#include "commodity.h"
#include "ui_commodity.h"

commodity::commodity(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::commodity)
{
    ui->setupUi(this);
}

commodity::~commodity()
{
    delete ui;
}
