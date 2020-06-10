#ifndef VIPR_H
#define VIPR_H

#include <QDialog>

namespace Ui {
class vipr;
}

class vipr : public QDialog
{
    Q_OBJECT

public:
    explicit vipr(QWidget *parent = nullptr);
    ~vipr();

private slots:
    void on_btnCancel_2_clicked();

    void on_btnOk_2_clicked();

private:
    Ui::vipr *ui;

signals:
    void vipsend(QString vipname);//定义子窗口向主窗口发送数据的信号

};

#endif // VIPR_H
