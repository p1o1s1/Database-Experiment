#ifndef ADD_COMMODITY_H
#define ADD_COMMODITY_H

#include <QWidget>

namespace Ui {
class add_commodity;
}

class add_commodity : public QWidget
{
    Q_OBJECT

public:
    explicit add_commodity(QWidget *parent = nullptr);
    ~add_commodity();

private:
    Ui::add_commodity *ui;
};

#endif // ADD_COMMODITY_H
