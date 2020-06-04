#ifndef ADD_COMMODITY_H
#define ADD_COMMODITY_H

#include <QWidget>
#include "mainwindow.h"
#include "commodity.h"

namespace Ui {
class add_commodity;
}

class add_commodity : public QWidget
{
    Q_OBJECT

public:
    explicit add_commodity(QWidget *parent = nullptr);
    ~add_commodity();

private slots:
    void on_btnOk_clicked();

    void on_btnCancel_clicked();

public:
    Ui::add_commodity *ui;
    mainwindow mainwindow;
    commodity commodity;
};

#endif // ADD_COMMODITY_H
