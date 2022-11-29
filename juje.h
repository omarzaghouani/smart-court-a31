#ifndef JUJE_H
#define JUJE_H

#include<QSqlQueryModel>
#include<QTableView>
#include<QMessageBox>
class juje
{
private:
    int idd;

    QString mdp;
  QString prenom;
    QString nom;
    QString type;
     QString mail;
    QString date;

public:
    juje();
    juje(int idd,QString mdp,QString prenom,QString nom,QString type, QString mail,QString date);
    int     getid();
    QString      gettype();
    QString      getnom_juge();
    QString      getdate();
    QString      getmdp();
    void setid();
    bool modifier();


    void setid(int idd);
    bool ajouter();

    QSqlQueryModel* afficher();
bool supprimer(int id);

void chercher(QTableView *table,int idd);
QStringList listeadresses(QString var);
int calcul_adresses(QString adresse,QString val);

};

#endif // AFFAIRE_H
