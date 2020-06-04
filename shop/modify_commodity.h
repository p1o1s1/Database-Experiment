#ifndef MODIFY_COMMODITY_H
#define MODIFY_COMMODITY_H

#include <QWidget>
#include "mainwindow.h"
#include "commodity.h"

namespace Ui {
class modify_commodity;
}

class modify_commodity : public QWidget
{
    Q_OBJECT

public:
    explicit modify_commodity(QWidget *parent = nullptr);
    ~modify_commodity();

private slots:
    void on_btnCancel_clicked();

    void on_btnOk_clicked();

public:
    Ui::modify_commodity *ui;
    mainwindow mainwindowss;
    //commodity commodityss;
};

#endif // MODIFY_COMMODITY_H
