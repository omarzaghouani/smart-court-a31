#ifndef CALENDRIER_H
#define CALENDRIER_H
#include<QSqlQueryModel>
#include<QTableView>
#include<QMessageBox>

class calendrier
{
    private:
   QString  mois;
   QString jour;
   QString annee;

public:
    calendrier();
      calendrier( QString  mois,QString jour,QString annee);
      QString getmois;
      QString getjour;
      QString getannee;
       //void setmois(QString mois);
          bool ajouter();
             QSqlQueryModel* afficher();
};

#endif // CALENDRIER_H
