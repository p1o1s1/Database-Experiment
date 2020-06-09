#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QStandardItem>
#include <qstring.h>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QtSql>


extern QSqlQueryModel* model4;

namespace Ui {
class mainwindow;
}

class mainwindow : public QWidget
{
    Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = nullptr);
    ~mainwindow();

private slots:
    void on_push_addgoods_2_clicked();

    void on_commodity_list_clicked(const QModelIndex &index);

    void on_pbnAddSuupe_3_clicked();

    void on_buy_list_clicked(const QModelIndex &index);

    void on_pbnAddSuupe_4_clicked();

    void on_pbnModifySup_3_clicked();

public:
    Ui::mainwindow *ui;

private slots:
    void receiveMsg(QString vipno,QString vippay,QString discount,QString pay);
    void on_pbnregister_clicked();
};

#endif // MAINWINDOW_H
