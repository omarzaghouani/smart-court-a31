#ifndef AFFAIRE_H
#define AFFAIRE_H


#include<QSqlQueryModel>
#include<QTableView>
#include<QMessageBox>


#include <QtPrintSupport/QPrinter>



#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>
#include <iostream>
#include <QDebug>
#include <QRadioButton>
#include <QtPrintSupport/QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QTextDocument>
#include <QTextEdit>
#include <QtSql/QSqlQueryModel>
#include <QtPrintSupport/QPrinter>
#include <QVector2D>
#include <QVector>
#include <QSqlQuery>
#include<QDesktopServices>
#include<QUrl>
#include<QtPrintSupport/QPrintDialog>
#include <QPixmap>
#include <QTabWidget>
#include <QValidator>
#include<QDesktopServices>
#include<QtSql/QSqlQuery>
#include<QVariant>
#include <QDateTime>
#include<QPrinter>
#include<QPainter>
#include<QDir>
class Affaire
{
private:
    int reference;
    QString ordre;
    int idjuge;
    QString type;
    int idavocat;
    int cinpersonne;
    int num_salle;
    QString date  ;
public:
    QStringList listeadresses(QString var);
    int calcul_adresses(QString adresse,QString val);

    Affaire();
    Affaire(int reference,QString ordre,int idjuge,QString type,int idavocat,int cinpersonne,   int num_salle,QString date);
  void  setref(int idd );
  int  getref();

    bool ajouter();
    int nba();
    int nbtout();

    int nbj();
    int nb1();
    int nb2();
    int nbs();
QSqlQueryModel* afficher();
bool supprimer(int reference);
void chercher(QTableView *table,int cas );
bool supprimert( );
int pdf();
bool modifier();
void  setordre(QString s );
QSqlQueryModel* afficherh();

void  settype(QString s );
void  setdate(QString s );


};

#endif // AFFAIRE_H
