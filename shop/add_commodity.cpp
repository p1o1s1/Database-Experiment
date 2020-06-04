#include "add_commodity.h"
#include "ui_add_commodity.h"
#include <QtSql>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commodity.h"
#include "ui_commodity.h"

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
    bool ok=0;
    int k=1;
    QSqlQuery *query;
    QSqlQuery *query3;
    QString S;
    while(1){
        S=QString("select CID,Cname,Price,Rest from shop.commodity where CID=%1").arg(k);
        query=new QSqlQuery;
        query->exec(S);
        if(!query->next()){
            break;
        }
        else k++;
    }
    qDebug() << k ;
    S=QString("insert into shop.commodity values(%1,'%2','%3','%4')").arg(k).arg(ui->cname->text()).arg(ui->cprice->text()).arg(ui->rest->text());
    query=new QSqlQuery;
    ok=query->exec(S);
    if(ok)
        QMessageBox::about(NULL, "加入商品", "插入成功");
    QString S3 =QString("select CID,Cname,Price,Rest from shop.commodity;");
    query3=new QSqlQuery;
    query3->exec(S3);
    qDebug() << "进入搜索" ;
    model4->setQuery(*query3);
    mainwindow.ui->commodity_list->setModel(model4);
    mainwindow.ui->commodity_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainwindow.ui->commodity_list->setSelectionBehavior(QAbstractItemView::SelectRows);
    mainwindow.ui->commodity_list->show();
    modelf->setQuery(*query3);
    commodity.ui->tableView->setModel(modelf);
    commodity.ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    commodity.ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    commodity.ui->tableView->show();
    this->close();
}

void add_commodity::on_btnCancel_clicked()
{
     this->close();
}
