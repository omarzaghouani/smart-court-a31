#include "mainwindow1.h"
#include <juge.h>
#include <QApplication>
#include <connexion.h>
#include <QMessageBox>
#include<login.h>
#include<QDebug>>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connexion c;
    login l;
    bool test=c.createconnect();
    MainWindow w;
    MainWindow1 ww;

    int mdp=l.retmdp();

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
