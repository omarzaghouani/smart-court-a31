#include "calendrier.h"
#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QMessageBox>
calendrier::calendrier( QString  mois,QString jour,QString annee)
{
this->mois= mois;
    this->jour= jour;
    this->annee= annee;

}

/*void calendrier::setmois(QString mois){mois= mois;};
//QString calendrier ::getmois(){return mois;}
QString calendrier :: getjour(){return jour;}
QString calendrier :: getannee(){return annee;}*/
bool calendrier ::ajouter(){
    QSqlQuery query;
     query.prepare("INSERT INTO CALENDRIER(mois,jour,annee) "
                   "VALUES (:moiss,:jourr,:anneee)");
        query.bindValue(":moiss", mois);
           query.bindValue(":jourr", jour);
              query.bindValue(":anneee", annee);
               return query.exec();
}
QSqlQueryModel* calendrier::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("SELECT* FROM CALENDRIER");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("mois"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("jour"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("annee"));

    return model;



}
