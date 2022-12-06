#ifndef LOGIN_H
#define LOGIN_H
#include <QDialog>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QMainWindow>
#include<QMessageBox>
#include "juge.h"
#include<mainwindow1.h>
#include<mainwindow.h>

#include "ui_mainwindow1.h"
#include "ui_mainwindow.h"
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    int ret();
    int retmdp();

private slots:
    void on_pb_connecter_clicked();

private:

    Ui::login *ui;
   QMainWindow* M;
};

#endif // LOGIN_H
