#include "mainwindow.h"

#include <QApplication>
//#include <QSqlDatabase>
#include <QTextStream>
#include<QTime>
#include<QFile>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
//#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Connection c;
    QFile file("d.txt");
       MainWindow w;
       //bool test=false;
       QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
       db.setDatabaseName("haroun");
       db.setUserName("haroun");//inserer nom de l'utilisateur
       db.setPassword("456123");//inserer mot de passe de cet utilisateur
        //bool test=c.createconnect();

        if(db.open())
        {



                   w.show();

            QMessageBox::information(nullptr, QObject::tr("database is open"),
                        QObject::tr("connection successful.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);


    }
        else{
            QMessageBox::information(nullptr, QObject::tr("database is not open"),
                        QObject::tr("connection failed.\n"

                          "Click Cancel to exit."), QMessageBox::Cancel);}
    return a.exec();
}
