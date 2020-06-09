#ifndef VIP_H
#define VIP_H

#include <QDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "commodity.h"

namespace Ui {
class vip;
class mainwindow;
}

class vip : public QDialog
{
    Q_OBJECT

public:
    explicit vip(QWidget *parent = nullptr);
    ~vip();

private slots:
    void on_btnCancel_2_clicked();

    void on_btnOk_2_clicked();

public:
    Ui::vip *ui;
    mainwindow mainwindowf;
    commodity commodity;

signals:
    void dialog_send_a_signal(QString vipno,QString vippay,QString discount,QString pay);//定义子窗口向主窗口发送数据的信号
};

#endif // VIP_H
