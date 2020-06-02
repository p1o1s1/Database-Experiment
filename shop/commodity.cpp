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


QSqlQueryModel* model = new QSqlQueryModel;

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
    model->setQuery(*query);
    ui->deleteBtn_2->setDisabled(true);
    ui->tableView->setModel(model);
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
}

void commodity::on_newBtn_2_clicked()
{
    add_commodity *add = new add_commodity();
    add->setWindowModality(Qt::ApplicationModal);
    add->show();
}

void commodity::on_modifyBtn_2_clicked()
{
    modify_commodity *modify = new modify_commodity();
    modify->setWindowModality(Qt::ApplicationModal);
    modify->show();
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
    }
    QString S2 =QString("select CID,Cname,Price,Rest from shop.commodity;");
    query2->exec(S2);
    qDebug() << "进入搜索" ;
    model->setQuery(*query2);
    ui->deleteBtn_2->setDisabled(true);
    ui->tableView->setModel(model);
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
