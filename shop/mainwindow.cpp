#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginform.cpp"

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

void mainwindow::on_push_addgoods_2_clicked()
{

}

void mainwindow::on_commodity_list_clicked(const QModelIndex &index)
{
    QSqlTableModel *model = new QSqlTableModel;
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
