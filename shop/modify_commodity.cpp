#include "modify_commodity.h"
#include "ui_modify_commodity.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commodity.h"
#include "ui_commodity.h"
#include <QtSql>
#include <QMessageBox>

modify_commodity::modify_commodity(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::modify_commodity)
{
    ui->setupUi(this);
}

modify_commodity::~modify_commodity()
{
    delete ui;
}

void modify_commodity::on_btnCancel_clicked()
{
    this->close();
}

void modify_commodity::on_btnOk_clicked()
{
    bool ok=0;
    QSqlQuery *query;
    QSqlQuery *query3;
    QString S;
    S=QString("update commodity set cname = '%1', price = %2, rest= %3 where CID = '%4'").arg(ui->cname->text()).arg(ui->cprice->text()).arg(ui->rest->text()).arg(ui->CID->text());
    query=new QSqlQuery;
    ok=query->exec(S);
    if(ok)
        QMessageBox::about(NULL, "修改商品", "修改成功");
    QString S3 =QString("select CID,Cname,Price,Rest from shop.commodity;");
    query3=new QSqlQuery;
    query3->exec(S3);
    qDebug() << "进入搜索" ;
    model4->setQuery(*query3);
    mainwindowss.ui->commodity_list->setModel(model4);
    mainwindowss.ui->commodity_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainwindowss.ui->commodity_list->setSelectionBehavior(QAbstractItemView::SelectRows);
    mainwindowss.ui->commodity_list->show();
    modelf->setQuery(*query3);
    commodity *com = new commodity();
    com->ui->tableView->setModel(modelf);
    com->ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    com->ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    com->ui->tableView->show();
    this->close();
}
