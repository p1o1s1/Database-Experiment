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

private:
    Ui::vipr *ui;
};

#endif // VIPR_H
