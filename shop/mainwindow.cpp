#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginform.cpp"
#include <QStandardItem>
#include <qstring.h>
#include <QString>
#include "commodity.h"
#include "add_commodity.h"
#include <QMainWindow>
#include "ui_add_commodity.h"
#include "vip.h"
#include "vipr.h"
#include <QDateTime>


int clicked_seq=-1;
QSqlQueryModel* model4 = new QSqlQueryModel;
int vipx=0;

mainwindow::mainwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainwindow)
{
    ui->setupUi(this);
    QSqlQuery *query;
    if (!createConnection())
    {
           QMessageBox::warning(this, tr("警告！"),
                       tr("数据库连接失败！"),
                       QMessageBox::Yes);
        }
    else{
       /* QSqlQueryModel* model = new QSqlQueryModel;
        model->setQuery("select * from shop.commodity",db);
        //设置表的列名

        model->setHeaderData(3,Qt::Horizontal,QObject::tr("商品库存"));
        QTableView *viewgoods = new QTableView(ui->commodity_list);
        viewgoods->setModel(model);
        viewgoods->setFixedSize(800,490);
        viewgoods->setColumnWidth(0,130);
        viewgoods->setColumnWidth(1,130);
        viewgoods->setColumnWidth(2,130);
        viewgoods->setColumnWidth(3,130);
        viewgoods->setColumnWidth(4,130);
        viewgoods->setColumnWidth(5,130);
        viewgoods->setSortingEnabled(true);
        viewgoods->show();*/




        QString S =QString("select CID,Cname,Price,Rest from shop.commodity;");
        query=new QSqlQuery;
        query->exec(S);
        qDebug() << "进入搜索" ;
        model4->setQuery(*query);
        ui->addup->setText(QString("%1").arg(0));
        ui->vippay->setText(QString("%1").arg(0));
        ui->discount->setText(QString("%1").arg(0));
        ui->pay->setText(QString("%1").arg(0));
        ui->commodity_list->setModel(model4);
        ui->commodity_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->push_addgoods_2->setDisabled(true);
        ui->commodity_list->show();
    }
}

mainwindow::~mainwindow()
{

    delete ui;
}

int row=0;

QStandardItemModel* itemmodel = new QStandardItemModel();

void mainwindow::on_push_addgoods_2_clicked()
{
    float sum=0.0;
    int k;
    int oldnum=0;
    int newnum=0;
    int flag=0;
    float addup=0.0;
    itemmodel->setHorizontalHeaderLabels({"CID", "Cname", "Num", "Price", "Sum"});
    ui->buy_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    if(ui->CID!=NULL){
        for(k=0;k<row;k++){
            if(ui->CID->document()->toPlainText()==itemmodel->item(k,0)->text()){
                oldnum=itemmodel->item(k,2)->text().toInt();
                newnum=ui->num->text().toInt()+oldnum;
                itemmodel->setItem(k,0,new QStandardItem(ui->CID->document()->toPlainText()));
                itemmodel->setItem(k,1,new QStandardItem(ui->Cname->document()->toPlainText()));
                itemmodel->setItem(k,2,new QStandardItem(QString("%1").arg(newnum)));
                itemmodel->setItem(k,3,new QStandardItem(ui->Price->document()->toPlainText()));
                sum=newnum*ui->Price->document()->toPlainText().toFloat();
                itemmodel->setItem(k,4,new QStandardItem(QString("%1").arg(sum)));
                row--;
                flag=1;
                break;
            }
        }
        if(flag==0){
            itemmodel->setItem(row,0,new QStandardItem(ui->CID->document()->toPlainText()));
            itemmodel->setItem(row,1,new QStandardItem(ui->Cname->document()->toPlainText()));
            itemmodel->setItem(row,2,new QStandardItem(ui->num->text()));
            itemmodel->setItem(row,3,new QStandardItem(ui->Price->document()->toPlainText()));
            sum=ui->num->text().toFloat()*ui->Price->document()->toPlainText().toFloat();
            itemmodel->setItem(row,4,new QStandardItem(QString("%1").arg(sum)));
        }
        row++;
    }
    ui->pbnpay->setDisabled(false);
    ui->buy_list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->buy_list->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->buy_list->setModel(itemmodel);
    ui->buy_list->show();
    for(k=0;k<row;k++){
        addup+=itemmodel->item(k,4)->text().toFloat();
    }
    ui->addup->setText(QString("%1").arg(addup));
    if(vipx){
        ui->discount->setText(QString("%1").arg(ui->addup->document()->toPlainText().toFloat()*0.1));
        ui->pay->setText(QString("%1").arg(ui->addup->document()->toPlainText().toFloat()*0.9+ui->vippay->document()->toPlainText().toFloat()));
    }
    else{
        ui->discount->setText(QString("%1").arg(0));
        ui->pay->setText(QString("%1").arg(ui->addup->document()->toPlainText().toFloat()+ui->vippay->document()->toPlainText().toFloat()));
    }
}

void mainwindow::on_commodity_list_clicked(const QModelIndex &index)
{
    QSqlTableModel *model = new QSqlTableModel;
    ui->commodity_list->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->push_addgoods_2->setDisabled(false);
    model->setTable("commodity"); //指定要做模型的表
    model->setHeaderData(0, Qt::Horizontal, "CID");
    model->setHeaderData(1, Qt::Horizontal, "Cname");
    model->setHeaderData(2, Qt::Horizontal, "Price");
    model->setHeaderData(3, Qt::Horizontal, "Rest");
    model->select();
    ui->commodity_list->setModel (model); //关键步骤
    QSqlRecord record=model->record(index.row()); //关键步骤
    //01.记录被点击行的"name"列(与数据库这张表的列头名相同)，到局部变量namestr中
    QString CIDstr = record.value("CID").toString();
    QString namestr = record.value("Cname").toString();
    //02.下同
    QString price = record.value("Price").toString();
    QString rest = record.value("Rest").toString();
    ui->CID->setText(CIDstr);
    ui->Cname->setText(namestr);
    ui->Rest->setText(rest);
    ui->Price->setText(price);
}


int delets=0;
QModelIndex d_indexs;

void mainwindow::on_buy_list_clicked(const QModelIndex &index)
{
    d_indexs=index;
    delets=1;
    ui->pbnAddSuupe_3->setDisabled(false);
}

void mainwindow::on_pbnAddSuupe_3_clicked()
{
    int k;
    float addup=0.0;
    if(delets){
        itemmodel->removeRow(d_indexs.row());
        row--;
        delets=0;
        ui->pbnAddSuupe_3->setDisabled(true);
    }
    for(k=0;k<row;k++){
        addup+=itemmodel->item(k,4)->text().toFloat();
    }
    ui->addup->setText(QString("%1").arg(addup));
    if(vipx){
        ui->discount->setText(QString("%1").arg(ui->addup->document()->toPlainText().toFloat()*0.1));
        ui->pay->setText(QString("%1").arg(ui->addup->document()->toPlainText().toFloat()*0.9+ui->vippay->document()->toPlainText().toFloat()));
    }
    if(row==0)
        ui->pbnpay->setDisabled(true);
    ui->buy_list->setModel(itemmodel);
    ui->buy_list->show();
}


void mainwindow::on_pbnAddSuupe_4_clicked()
{
    commodity *com = new commodity();
    com->setWindowModality(Qt::ApplicationModal);
    com->show();
}

void mainwindow::on_pbnModifySup_3_clicked()
{
    vip *v= new vip(this);
    connect(v,SIGNAL(dialog_send_a_signal(QString,QString,QString,QString)),this,SLOT(receiveMsg(QString,QString,QString,QString)));//绑定子窗口向主窗口发送消息的信号与槽
    v->setWindowModality(Qt::ApplicationModal);
    v->exec();
}

void mainwindow::receiveMsg(QString vipno,QString vippay,QString discount,QString pay)
{
    vipx=1;
    ui->vipno->setText(vipno);
    ui->vippay->setText(QString("%1").arg(0));
    ui->discount->setText(QString("%1").arg(ui->addup->document()->toPlainText().toFloat()*0.1));
    ui->pay->setText(QString("%1").arg(ui->addup->document()->toPlainText().toFloat()*0.9));
    ui->pbnModifySup_3->setDisabled(true);
    ui->pbnregister->setDisabled(true);
}

void mainwindow::on_pbnregister_clicked()
{
    vipr *f=new vipr(this);
    connect(f,SIGNAL(vipsend(QString)),this,SLOT(vipregister(QString)));
    f->setWindowModality(Qt::ApplicationModal);
    f->exec();
}

void mainwindow::vipregister(QString vipname)
{
    vipx=1;
    int vipno=1;
    QSqlQuery *query;
    QString S;
    query=new QSqlQuery;
    for(vipno=1;1;vipno++){
        S=QString("select * from vip where vipid=%1").arg(vipno);
        query->exec(S);
        if(!query->next()){
            S=QString("insert into vip values(%1,'%2',\"%3\")").arg(vipno).arg(vipname).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
            query->exec(S);
            qDebug() << vipname ;
            break;
        }
    }
    ui->vippay->setText(QString("%1").arg(50));
    ui->pbnregister->setDisabled(true);
    ui->pbnModifySup_3->setDisabled(true);
    ui->vipno->setText(QString("%1").arg(vipno));
    ui->discount->setText(QString("%1").arg(ui->addup->document()->toPlainText().toFloat()*0.1));
    ui->pay->setText(QString("%1").arg(ui->addup->document()->toPlainText().toFloat()*0.9+50.0));
}

void mainwindow::on_pbnpay_clicked()
{
    QSqlQuery *query;
    QString S;
    query=new QSqlQuery;
    int oid=1;
    int k=0;
    for(oid=1;1;oid++){
        S=QString("select * from list where oid=%1").arg(oid);
        query->exec(S);
        if(!query->next()){
            if(ui->vipno->document()->toPlainText().toInt()==0){
                S=QString("insert into list values(%1,\"%2\",%3,NULL,\"%4\");").arg(oid).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(ui->pay->document()->toPlainText()).arg(cashierid);
            }
            else
                S=QString("insert into list values(%1,\"%2\",%3,%4,\"%5\");").arg(oid).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(ui->pay->document()->toPlainText()).arg(ui->vipno->document()->toPlainText().toInt()).arg(cashierid);
            qDebug() << S ;
            qDebug() << cashierid ;
            query->exec(S);
            break;
        }
    }
    qDebug() << row ;
    for(k=0;k<row;k++){
        S=QString("insert into listdetail values(%1,%2,%3,%4);").arg(oid).arg(itemmodel->item(k,0)->text()).arg(itemmodel->item(k,2)->text()).arg(itemmodel->item(k,3)->text());
        qDebug() << S ;
        query->exec(S);
    }
    vipx=0;
    row=0;
}
