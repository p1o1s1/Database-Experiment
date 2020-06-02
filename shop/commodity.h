#ifndef COMMODITY_H
#define COMMODITY_H

#include <QWidget>
#include "mainwindow.h"

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

private:
    Ui::commodity *ui;
    mainwindow mainwindow;
};

#endif // COMMODITY_H
