#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDialog>
#include <QMainWindow>
#include <QAbstractSocket>
#include <QQuickItem>
#include <QWidget>

#include <QMediaPlayer>
#include <QSettings>
#include <QDataStream>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QFile>
#include <QDesktopWidget>
#include <QDialog>
#include <QTextStream>
#include <QAxWidget>
#define NOM_RX "^([a-z]+[,.]?[ ]?|[A-Z]+['-]?)+$"
#include "statistique.h"
#include"juje.h"
#include "mailsmtp.h"
#include "mail.h"
#include "calendrier.h"
#include "arduino.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_ajouter_clicked();

    void on_pushButton_Sui_m_clicked();

    void on_pushButton_trier_3_clicked();

    void on_pushButton_ajouter_4_clicked();

   // void on_Psearch_4_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_trier_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_Actualise_h_clicked();

    void on_pushButton_Sui_m_2_clicked();

    void on_pushButton_ajouter_5_clicked();
    void sendMail();
    void mailSent(QString);
    void browse();

    void on_sendBtn_clicked();

    void on_sendBtn_2_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_pushButton_ajouter_6_clicked();

    void on_pushButton_Sui_m_3_clicked();

    void on_calendarWidget_activated(const QDate &date);

    void on_sendBtn_3_clicked();

    void on_sendBtn_4_clicked();

    void on_ent_date_Aj_userDateChanged(const QDate &date);
    void update();


private:
    Ui::MainWindow *ui;
    juje j;
    QByteArray data; // variable contenant les données reçues

    Arduino A; // objet temporaire

//calendrier c;
    QStringList files;
signals:

    void setCenter(QVariant, QVariant);
    void addMarker(QVariant, QVariant);
};





#endif // MAINWINDOW_H
