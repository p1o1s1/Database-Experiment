#include "vipr.h"
#include "ui_vipr.h"
#include <QMessageBox>

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

void vipr::on_btnCancel_2_clicked()
{
    this->close();
}

void vipr::on_btnOk_2_clicked()
{
    QMessageBox::about(NULL, "VIP注册", "注册成功");
    emit vipsend(ui->cname_2->text().toUtf8().data());
    this->close();
}
