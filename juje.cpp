#include "juje.h"
#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QMessageBox>
juje::juje()
{

}
juje::    juje(int idd,QString mdp,QString prenom,QString nom,QString type, QString mail,QString date)
{
this->idd= idd;
this->mdp= mdp;
this->prenom= prenom;
this->nom =nom;
this->type= type;
 this->mail= mail;
this->date =date;


}
int juje::     getid(){return idd;}
void juje::setid(int id){idd=id;};

QString juje::     gettype(){return type;}
QString juje::     getnom_juge(){return nom;}
QString juje::     getdate(){return date ;}
QString juje::     getmdp(){return mdp;}
bool juje ::ajouter(){
    QSqlQuery query;
    QString id_string=QString::number(idd);

          query.prepare("INSERT INTO jugeee (identifiant,mdp,prenom,nom,type,mail,datee) "
                        "VALUES (:identifiantt,:mdpp,:nomm,:prenomm,:maill,:date_naissancee,:typee)");
          query.bindValue(":identifiantt", id_string);
          query.bindValue(":mdpp", mdp);
          query.bindValue(":nomm", nom);
          query.bindValue(":prenomm", prenom);
          query.bindValue(":maill", mail);
          query.bindValue(":date_naissancee", date);
          query.bindValue(":typee", type);


          return query.exec();

}
QSqlQueryModel* juje::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();

    model->setQuery("SELECT* FROM jugeee");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("identifaint"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("mdp"));


    return model;



}
bool juje::supprimer(int id ){

    QSqlQuery query;

    query.prepare("Delete from  jugeee where identifiant=:id");
    query.bindValue(":id", id);
    return query.exec();


}
void juje::chercher(QTableView *table,int idd ){
    QSqlQueryModel *model= new QSqlQueryModel();

             QSqlQuery *query=new QSqlQuery;
QString iidd=QString::number(idd);
             query->prepare("SELECT * FROM jugeee WHERE (identifiant  LIKE "+iidd+  ")");

            // model->setQuery("SELECT* FROM jugeee");

             //model->setQuery(*query);

             query->exec();

             if(query->exec()){
             model->setQuery(*query);
             table->setModel(model);


             table->show();
             }

                  if(query->numRowsAffected()==0){

                QMessageBox::warning(nullptr, QObject::tr("database is open"),
                         QObject::tr("juge introvale .\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);


           }}





bool juje::modifier()
    {
    QSqlQuery query;

        QString id_string=QString::number(idd);


          QSqlQuery queryr;


          QSqlQueryModel *modelr= new QSqlQueryModel();


          queryr.prepare("SELECT * FROM jugeee WHERE (identifiant  LIKE "+id_string+  ")");







          if(queryr.exec()){
          modelr->setQuery(queryr);
          }


      if(queryr.exec()){
      modelr->setQuery(queryr);
      }



          if(queryr.numRowsAffected()==0){
             QMessageBox::warning(nullptr, QObject::tr("database is open"),
                         QObject::tr("juge introvale .\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);


        }



          else{

    QSqlQuery query;
    QString id_string=QString::number(idd);

    query.prepare("UPDATE jugeee SET mdp=:mdp,prenom=:prenom,type=:type,nom=:nom,mail=:mail,datee=:date WHERE identifiant=:id;");

    query.bindValue(":id",id_string);
        query.bindValue(":type",type);
        query.bindValue(":nom",nom);
        query.bindValue(":prenom",prenom);
        query.bindValue(":mail",mail);
           query.bindValue(":mdp",mdp);
           query.bindValue(":date",date);






    return    query.exec();}
    return false;
    }
