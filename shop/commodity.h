#ifndef COMMODITY_H
#define COMMODITY_H

#include <QWidget>
#include "mainwindow.h"
#include "modify_commodity.h"

extern QSqlQueryModel* modelf;

namespace Ui {
class commodity;
}

class commodity : public QWidget
{
    Q_OBJECT

public:
    explicit commodity(QWidget *parent = nullptr);
    ~commodity();

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_newBtn_2_clicked();

    void on_modifyBtn_2_clicked();

    void on_deleteBtn_2_clicked();

public:
    Ui::commodity *ui;
    mainwindow mainwindow;
    //modify_commodity modify_commodity;
};

#endif // COMMODITY_H
