#include "mainwindow.h"
#include <QtWidgets>
#include <QApplication>
#include"connection.h"
#include"mainwindow.h"
#include<QMessageBox>
#include "login.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;
    login l;
        bool test=c.createconnect();
      MainWindow w;


        if(test)
        {


l.show();
//w.show();
            QMessageBox::information(nullptr, QObject::tr("database is open"),
                        QObject::tr("connection successful.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);


    }
        else
            QMessageBox::information(nullptr, QObject::tr("database is not open"),
                        QObject::tr("connection failed.\n"

                          "Click Cancel to exit."), QMessageBox::Cancel);
    return a.exec();
}
