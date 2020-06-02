#ifndef MODIFY_COMMODITY_H
#define MODIFY_COMMODITY_H

#include <QWidget>

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

private:
    Ui::modify_commodity *ui;
};

#endif // MODIFY_COMMODITY_H
