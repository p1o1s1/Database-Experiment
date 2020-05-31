#ifndef COMMODITY_H
#define COMMODITY_H

#include <QWidget>

namespace Ui {
class commodity;
}

class commodity : public QWidget
{
    Q_OBJECT

public:
    explicit commodity(QWidget *parent = nullptr);
    ~commodity();

private:
    Ui::commodity *ui;
};

#endif // COMMODITY_H
