#include "juge.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

juge::juge()
{
     id_juge=0;
     mdp=0;
     nom_juge="";
     prenom="";
     gmail="";
     date="";
}
juge::juge(int a, int b,QString c,QString d,QString e ,QString f )
{
     this->id_juge=a;
    this->mdp=b;
    this->nom_juge=c;
    this->prenom=d;
    this->gmail=e;
    this->date=f;
 }


/*int CONTRAT_CLIENT::     getnum_contrat(){return num;}
void CONTRAT_CLIENT::setnum_contrat(int  num_contrat){num= num_contrat;};

QString CONTRAT_CLIENT::     getdurée_contrat=(){return durée_contrat;}
QString CONTRAT_CLIENT::     getdate_sign=(){return date_sign;}
QString CONTRAT_CLIENT::     getdate_expir(){return date_expir ;}
QString CONTRAT_CLIENT::     getnom_societe(){return nom_societe;}

*/
bool juge::ajouter()
{    QSqlQuery query;
     QString num = QString::number(id_juge);
      QString num1 = QString::number(mdp);


     query.prepare("INSERT INTO  jegge(id,mdp,nom,prenom,gmail,datea)" "VALUES(:id,:mdp,:nom,:prenom,:gmail,:datea)");
     query.bindValue(":id",num);
     query.bindValue(":mdp",num1);
     query.bindValue(":nom",nom_juge);
     query.bindValue(":prenom",prenom);
     query.bindValue(":gmail",gmail);
      query.bindValue(":datea",date);
     return query.exec();
}

bool juge::supprimer(int id_juge)
{
    QSqlQuery query;
    QString id=QString::number(id_juge);

    QSqlQueryModel *model= new QSqlQueryModel();



    query.prepare("SELECT * FROM jegge WHERE (id  LIKE "+id+  ")");

    if(query.exec()){
    model->setQuery(query);
    }


    if(query.numRowsAffected()==0){

       QMessageBox::warning(nullptr, QObject::tr("database is open"),
                   QObject::tr("juge introvale .\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
    }else{
    query.prepare("Delete from jegge where id=:id");
    query.bindValue(":id",id );
    return  query.exec();
 }
return false;
}

bool juge::modifier()
{ QSqlQuery query;

    QString id_string=QString::number(id_juge);


      QSqlQuery queryr;


      QSqlQueryModel *modelr= new QSqlQueryModel();


      queryr.prepare("SELECT * FROM jegee WHERE (id  LIKE "+id_string+  ")");







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
QString id_string=QString::number(id_juge);

query.prepare("UPDATE jugeee SET mdp=:mdp,prenom=:prenom,nom=:nom,gmail=:gmail,datee=:date WHERE id=:id;");

query.bindValue(":id",id_string);
    query.bindValue(":nom",nom_juge);
    query.bindValue(":prenom",prenom);
    query.bindValue(":mail",gmail);
       query.bindValue(":mdp",mdp);
       query.bindValue(":date",date);






return    query.exec();}
return false;
    }


QSqlQueryModel *juge::chercher(QString id )
{

    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from jegge where id like '" +id+"'");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("num_contrat"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("date_sign"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("date_expir"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("nom_societe"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("duree_contrat"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("domaine"));

    return model;
  }
QSqlQueryModel* juge::afficher()
{
   QSqlQueryModel* model=new QSqlQueryModel() ;
   model->setQuery("SELECT* FROM jegge");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("id juge"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("mot de passe"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("prenom"));
   model->setHeaderData(4, Qt::Horizontal, QObject::tr("dmail"));
   model->setHeaderData(5,Qt::Horizontal,  QObject::tr("date"));
       return model;

}
QSqlQueryModel * juge::trier()
{

    {

               QSqlQuery * q = new  QSqlQuery ();
                      QSqlQueryModel * model = new  QSqlQueryModel ();
                      q->prepare("SELECT * from jegge order by id DESC");
                      q->exec();
                      model->setQuery(*q);
                      return model;
    }
}
QSqlQueryModel * juge::trierASC()
{

    {

               QSqlQuery * q = new  QSqlQuery ();
                      QSqlQueryModel * model = new  QSqlQueryModel ();
                      q->prepare("SELECT * from jegge order by id ASC");
                      q->exec();
                      model->setQuery(*q);
                      return model;
    }
}
QStringList juge::listeadresses(QString var){
    QSqlQuery query;
    query.prepare("select id("+var+") from jegge");
    query.exec();
    QStringList list;
    while(query.next())
    {
        list.append(query.value(0).toString());
    }

    return list;
}
int juge::calcul_adresses(QString adresse,QString val)
{
    QSqlQuery query;
     query.prepare("select  * from jegge  WHERE "+val+"=:id");
     query.bindValue(":id", adresse );
     query.exec();
     int total=0;
     while(query.next())
     {
       total++;
     }
     return total;
}
int juge::nbtout(){
    QSqlQuery qry;
    int  row_count=0;


    qry.exec("SELECT * FROM jegge ");

    //qDebug() << "Number of Rows: " << qry.size();
    while(qry.next())
        row_count++;


            //qDebug()<<q.numRowsAffected();
    qDebug()<<row_count;
            return row_count;
}
