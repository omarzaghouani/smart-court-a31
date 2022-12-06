#ifndef JUGE_H
#define JUGE_H
#include<QString>
#include<QSqlQueryModel>
#include<QTableView>
#include<QMessageBox>
#include "arduino.h"


class juge
{
private:
 int id_juge;
  int mdp;

  QString nom_juge;
  QString prenom;
  QString gmail;
  QString date;



public:
   juge();
   juge(int,int,QString,QString,QString,QString);

   /*int ge_id(){return id_juge;}
   QString getdate_datr(){return date_sign;}
   QString getdate_expir(){return date_expir;}
   QString getnom_societe(){return nom_societe;}
   QString getduree_contrat(){return duree_contrat;}
   QString getdomaine(){return domaine;}
   QString getID_EMPLOYE(){return ID_EMPLOYE;}*/

   void setnum(int num){ this->mdp=  num;}
   int getnum(){return mdp;}
   /*{ this->date_sign=date_sign;}
   QString setdate_expir(QString  date_expir){ this->date_expir=date_expir;}
   QString setnom_societe(QString nom_societe){this->nom_societe=nom_societe;}
   QString setduree_contrat(QString duree_contrat){this->duree_contrat=duree_contrat;}
    QString setdomaine(QString domaine){this->domaine=domaine;}
    QString setID_EMPLOYE(QString ID_EMPLOYE){this->ID_EMPLOYE=ID_EMPLOYE;}


*/
  bool ajouter();
  QSqlQueryModel* afficher();
  bool supprimer(int);
  bool modifier();
 QSqlQueryModel * chercher(QString nom_societe);
 QSqlQueryModel *trier();
 QSqlQueryModel *trierASC();
 QStringList listeadresses(QString var);
 int calcul_adresses(QString adresse,QString val);
 int nbtout();


};

#endif // JUGE_H
