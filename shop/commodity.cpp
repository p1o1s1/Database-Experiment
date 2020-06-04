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

QSqlQueryModel* modelf = new QSqlQueryModel;

commodity::commodity(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::commodity)
{
    ui->setupUi(this);
    QSqlQuery *query;
    QString S =QString("select CID,Cname,Price,Rest from shop.commodity;");
    query=new QSqlQuery;
    query->exec(S);
    qDebug() << "进入搜索" ;
    modelf->setQuery(*query);
    ui->deleteBtn_2->setDisabled(true);
    ui->modifyBtn_2->setDisabled(true);
    ui->tableView->setModel(modelf);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->show();
}

commodity::~commodity()
{
    delete ui;
}

int delet=0;
QModelIndex d_index;

void commodity::on_tableView_clicked(const QModelIndex &index)
{
    d_index=index;
    delet=1;
    ui->deleteBtn_2->setDisabled(false);
    ui->modifyBtn_2->setDisabled(false);
}

void commodity::on_newBtn_2_clicked()
{
    add_commodity *add = new add_commodity();
    add->setWindowModality(Qt::ApplicationModal);
    add->show();
}

void commodity::on_modifyBtn_2_clicked()
{
   if(delet)
    {
        modify_commodity *modify = new modify_commodity();
        modify->setWindowModality(Qt::ApplicationModal);
        modify->show();
        int curRow=ui->tableView->currentIndex().row();
        QAbstractItemModel *modessl = ui->tableView->model();
        QModelIndex indextemp1 = modessl->index(curRow,0);//遍历第一行的所有列
        QModelIndex indextemp2 = modessl->index(curRow,1);
        QModelIndex indextemp3 = modessl->index(curRow,2);
        QModelIndex indextemp4 = modessl->index(curRow,3);
        QVariant datatemp1 = modessl->data(indextemp1);
        QVariant datatemp2 = modessl->data(indextemp2);
        QVariant datatemp3 = modessl->data(indextemp3);
        QVariant datatemp4 = modessl->data(indextemp4);
        modify->ui->CID->setText(datatemp1.toString());
        modify->ui->cname->setText(datatemp2.toString());
        modify->ui->cprice->setText(datatemp3.toString());
        modify->ui->rest->setText(datatemp4.toString());
        delet=0;
        ui->modifyBtn_2->setDisabled(true);
        ui->deleteBtn_2->setDisabled(true);
    }
}

void commodity::on_deleteBtn_2_clicked()
{
    QSqlQuery *query2,*query3;
    int curRow=ui->tableView->currentIndex().row();
    QAbstractItemModel *modessl = ui->tableView->model();
    QModelIndex indextemp = modessl->index(curRow,0);//遍历第一行的所有列
    //这个是一个单元格的值。tostring()----ok
    QVariant datatemp = modessl->data(indextemp);
    query2=new QSqlQuery;
    if(delet){
        QString S =QString("delete from commodity where CID=%1").arg(datatemp.toString());
        qDebug() << S;
        query2->exec(S);
        delet=0;
        ui->deleteBtn_2->setDisabled(true);
        ui->modifyBtn_2->setDisabled(true);
        QMessageBox::about(NULL, "删除商品", "删除成功");
    }
    QString S2 =QString("select CID,Cname,Price,Rest from shop.commodity;");
    query2->exec(S2);
    qDebug() << "进入搜索" ;
    modelf->setQuery(*query2);
    ui->deleteBtn_2->setDisabled(true);
    ui->tableView->setModel(modelf);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->show();

    QString S3 =QString("select CID,Cname,Price,Rest from shop.commodity;");
    query3=new QSqlQuery;
    query3->exec(S3);
    qDebug() << "进入搜索" ;
    model4->setQuery(*query3);
    mainwindow.ui->commodity_list->setModel(model4);
    mainwindow.ui->commodity_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainwindow.ui->commodity_list->setSelectionBehavior(QAbstractItemView::SelectRows);
    mainwindow.ui->commodity_list->show();


}
