#ifndef MAINWINDOW1_H
#define MAINWINDOW1_H
#include "juge.h"
#include"login.h"
#include"arduino.h"
#include <QMainWindow>
#include <QMessageBox>
#include<QString>
#include<QtWidgets>
#include<QTableView>
#include <QDialog>
#include<QAbstractItemModel>
#include<QString>
#include<QMessageBox>
#include<QTableView>
#include<QSqlQueryModel>
#include <QAbstractItemModel>
#include<QSqlQuery>
#include <QMediaRecorder>
#include <QMediaCaptureSession>
#include <QUrl>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>

#include <QtTextToSpeech>
#include <QMessageBox>
#include<QtCharts>#include <QtCore>
#include <QtSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow1; }
QT_END_NAMESPACE

class MainWindow1 : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow1(QWidget *parent = nullptr);
    ~MainWindow1();


private slots:
    void on_pb_ajouter_clicked();
    void on_pb_supprimer_clicked();
    void on_pb_modifier_clicked();
    void on_pb_trier_clicked();
    //void update_label();
    void on_pb_chercher_clicked();

    void on_pb_mail_clicked();
    //void stat();
    void on_pb_pdf_clicked();

    //void on_pb_stat_clicked();

    //void on_pb_envoyer_clicked();

    void on_pb_sent_clicked();

    void on_pb_tri_asc_clicked();

    void on_pushButton_clicked();
    void on_calendarWidget_clicked(const QDate &date);


private:
    Ui::MainWindow1 *uii;
    juge C;
    arduino A;
    QByteArray data;

};
#endif // MAINWINDOW1_H
