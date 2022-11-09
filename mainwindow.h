#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDialog>
#include <QMainWindow>
#include"juje.h"
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

private:
    Ui::MainWindow *ui;
    juje j;
signals:

    void setCenter(QVariant, QVariant);
    void addMarker(QVariant, QVariant);
};





#endif // MAINWINDOW_H
