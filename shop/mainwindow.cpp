#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginform.cpp"
#include <QStandardItem>
#include <qstring.h>
#include <QString>

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




        QString S =QString("select Cname,Price,Rest from shop.commodity;");
        query=new QSqlQuery;
        query->exec(S);
        qDebug() << "进入搜索" ;
        QSqlQueryModel* model = new QSqlQueryModel;
        model->setQuery(*query);
        ui->commodity_list->setModel(model);
        ui->commodity_list->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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
    float sum=0;
    int k;
    int oldnum=0;
    int newnum=0;
    int flag=0;
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
    ui->buy_list->setModel(itemmodel);
    ui->buy_list->show();
}

void mainwindow::on_commodity_list_clicked(const QModelIndex &index)
{
    QSqlTableModel *model = new QSqlTableModel;
    ui->commodity_list->setSelectionBehavior(QAbstractItemView::SelectRows);
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
