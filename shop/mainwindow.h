#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

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

private:
    Ui::mainwindow *ui;
};

#endif // MAINWINDOW_H
