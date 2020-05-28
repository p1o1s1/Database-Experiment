#include <QApplication>
#include "mainform.h"
#include "mainwindow.h"
#include "loginform.h"
#include <QMessageBox>
#include "loginform.h"
#include <QMessageBox>
#include <QApplication>
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSlider>
#include <QSpinBox>
#include <QSqlError>
#include <QDebug>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QTextStream>
#include <stdio.h>
#include <QLineEdit>
#include <QMessageBox>
#include <QtSql>


int main(int argc,char** argv)
{
    QApplication app(argc,argv);
    mainwindow *main = new mainwindow();
   // main->setWindowTitle("欢迎界面");

    LoginForm login;
    if (login.exec() == QDialog::Accepted)//调用login.exec()，阻塞主控制流，直到完成返回
    {
       main->show();
       return app.exec();
    }
    else return 0;
}
