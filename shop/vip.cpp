#include "vip.h"
#include "ui_vip.h"
#include "commodity.h"
#include "ui_commodity.h"
#include <QStandardItem>
#include <qstring.h>
#include <QString>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QApplication>
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include <QSqlError>
#include <QDebug>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QTextStream>
#include <stdio.h>
#include <QLineEdit>
#include <QMessageBox>
#include <QtSql>
#include "add_commodity.h"
#include "modify_commodity.h"
#include "ui_modify_commodity.h"


vip::vip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::vip)
{
    ui->setupUi(this);
}

vip::~vip()
{
    delete ui;
}

void vip::on_btnCancel_2_clicked()
{
    this->close();
}

void vip::on_btnOk_2_clicked()
{
    bool ok=0;
    float discounts;
    float pays;
    QSqlQuery *query;
    QString S;
    S=QString("select * from vip where VIPid=%1").arg(ui->cname_2->text());
    query=new QSqlQuery;
    ok=query->exec(S);
    if(ok){
        if(query->next()){
            QMessageBox::about(NULL, "VIP验证", "验证成功");
            discounts=mainwindowf.ui->addup->document()->toPlainText().toFloat()*0.1;
            pays=9.0*discounts;
            qDebug() <<discounts;
            qDebug() << "啊啊啊啊啊";
            emit dialog_send_a_signal(ui->cname_2->text(),QString("%1").arg(0),QString("%1").arg(discounts),QString("%1").arg(pays));
            this->close();
        }
        else{
            QMessageBox::about(NULL, "VIP验证", "验证有误，请重新输入");
        }
    }

}
