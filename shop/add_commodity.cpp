#include "add_commodity.h"
#include "ui_add_commodity.h"

add_commodity::add_commodity(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_commodity)
{
    ui->setupUi(this);
}

add_commodity::~add_commodity()
{
    delete ui;
}

void add_commodity::on_btnOk_clicked()
{

}

void add_commodity::on_btnCancel_clicked()
{
     this->close();
}
