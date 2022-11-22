#include "affaire.h"

#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QMessageBox>
#include <QTextStream>
#include<QTime>
#include<QFile>
#include "ui_mainwindow.h"

Affaire::Affaire()
{  reference=0;
     ordre="";
     idjuge=0;
     type="";
     idavocat=0;
     cinpersonne=0;
      num_salle=0;

     date="";

}
Affaire::Affaire(int reference,QString ordre,int idjuge,QString type,int idavocat,int cinpersonne,    int num_salle,QString date)

    {
     this->reference= reference;
      this->ordre=ordre;
      this->idjuge=idjuge;
      this->type=type;
      this->idavocat=idavocat;
      this->cinpersonne=cinpersonne;
    this->num_salle= num_salle;

      this->date=date;

    }
    int Affaire:: getref(){return reference;}
   /*QString  Affaire:: gettype(){return type;}
   QString  Affaire:: getordre(){return type;}
   QString  Affaire:: getnom_juge(){return type;}
   QString  Affaire:: gettype_p(){return type;}
   QString  Affaire:: getdate(){return type;}
   QString  Affaire:: getcin(){return type;}*/

    void Affaire:: setref(int idd ){reference=idd;}
    void Affaire:: setordre(QString s ){ordre=s;}

    void Affaire:: settype(QString s ){type=s;}
    void Affaire:: setdate(QString s ){date=s;}
    int Affaire::calcul_adresses(QString adresse,QString val)
    {
        QSqlQuery query;
         query.prepare("select  * from AFF  WHERE "+val+"=:adresse");
         query.bindValue(":adresse", adresse );
         query.exec();
         int total=2;
         while(query.next())
         {
           total++;
         }
         return total;
    }

    QStringList Affaire::listeadresses(QString var){
        QSqlQuery query;
        query.prepare("select DISTINCT("+var+") from aff");
        query.exec();
        QStringList list;
        while(query.next())
        {
            list.append(query.value(0).toString());
        }

        return list;
    }

    bool Affaire::ajouter(){

      QString reference_string=QString::number(reference);
        QString idjuge_string=QString::number(idjuge);
        QString idavocat_string=QString::number(idavocat);

        QString cinp_string=QString::number(cinpersonne);

        QString numsalle_string=QString::number(num_salle);

        QSqlQuery queryr;

        QSqlQuery queryj;
        QSqlQuery querya;

        QSqlQuery queryp;

        QSqlQuery querys;


        QSqlQueryModel *modelj= new QSqlQueryModel();
        QSqlQueryModel *modela= new QSqlQueryModel();

        QSqlQueryModel *modelp= new QSqlQueryModel();

        QSqlQueryModel *models= new QSqlQueryModel();
        QSqlQueryModel *modelr= new QSqlQueryModel();


        queryr.prepare("SELECT * FROM Aff WHERE (reference  LIKE "+reference_string+  ")");

        queryj.prepare("SELECT * FROM JUGE WHERE (IDJUGE  LIKE "+idjuge_string+  ")");
        querya.prepare("SELECT * FROM AVOCAT WHERE (ID  LIKE "+idavocat_string+  ")");

        queryp.prepare("SELECT * FROM PERSONNE WHERE (CIN  LIKE "+cinp_string+  ")");

        querys.prepare("SELECT * FROM SALLE WHERE (NUM  LIKE "+numsalle_string+  ")");



        if(queryj.exec()){
        modelj->setQuery(queryj);
        //modelj->setQuery(std::move(queryj));

        }
        if(querya.exec()){
        modela->setQuery(querya);
        }
        if(queryp.exec()){
        modelp->setQuery(queryp);
        }
        if(querys.exec()){
        models->setQuery(querys);
        }

    if(queryr.exec()){
    modelr->setQuery(queryr);
    }



        if(queryj.numRowsAffected()==0){
           QMessageBox::warning(nullptr, QObject::tr("database is open"),
                       QObject::tr("juge introvale .\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

           return  false;

      }else if(querya.numRowsAffected()==0){QMessageBox::warning(nullptr, QObject::tr("database is open"),
                                                                     QObject::tr("avocat introvale .\n"
                                                                                 "Click Cancel to exit."), QMessageBox::Cancel);
            return  false;

}else if(queryp.numRowsAffected()==0){QMessageBox::warning(nullptr, QObject::tr("database is open"),
                                                           QObject::tr("personne introvale .\n"
                                                                       "Click Cancel to exit."), QMessageBox::Cancel);
            return  false;

}else if(querys.numRowsAffected()==0){QMessageBox::warning(nullptr, QObject::tr("database is open"),
                                                           QObject::tr("salle introvale .\n"
                                                                       "Click Cancel to exit."), QMessageBox::Cancel);
            return  false;

}
        else if(queryr.numRowsAffected()!=0){QMessageBox::warning(nullptr, QObject::tr("database is open"),
                                                                   QObject::tr("affaire deja  existe .\n"
                                                                               "Click Cancel to exit."), QMessageBox::Cancel);

            return  false;

        }



        else{
QSqlQuery query;
              query.prepare("INSERT INTO Aff (reference,ordre,type,idjuge,idavocat,cinpersonne,numsalle,datea) "
                            "VALUES (:referencee,:ordree,:typee,:idjugee,:idavocatt,:cinpersonnee,:numsallee,:dateaa )");
              query.bindValue(":referencee", reference_string);
              query.bindValue(":ordree", ordre);
              query.bindValue(":typee", type);

              query.bindValue(":idjugee", idjuge_string);
              query.bindValue(":idavocatt", idavocat_string);
              query.bindValue(":cinpersonnee", cinp_string);
              query.bindValue(":numsallee", numsalle_string);

              query.bindValue(":dateaa", date);


              return query.exec();
}

        return  false;
    }
    int Affaire::nba(){
        QSqlQuery qry;
        QString k="administratif";
        int  row_count=0;
        //qry.prepare("SELECT * FROM table1 WHERE E  LIKE d% ");
        //qry.bindValue(":ref", k);

        qry.exec("SELECT * FROM AFF WHERE ordre LIKE 'A%'");

        //qDebug() << "Number of Rows: " << qry.size();
        while(qry.next())
            row_count++;


                //qDebug()<<q.numRowsAffected();
        qDebug()<<row_count;
                return row_count;


    }
    int Affaire::nbj(){
        QSqlQuery qry;
        int  row_count=0;
        //qry.prepare("SELECT * FROM table1 WHERE E  LIKE d% ");
        //qry.bindValue(":ref", k);

        qry.exec("SELECT * FROM AFF WHERE ordre LIKE 'j%'");

        //qDebug() << "Number of Rows: " << qry.size();
        while(qry.next())
            row_count++;


                //qDebug()<<q.numRowsAffected();
        qDebug()<<row_count;
                return row_count;
    }
    int Affaire::nb1(){
        QSqlQuery qry;
        int  row_count=0;
        //qry.prepare("SELECT * FROM table1 WHERE E  LIKE d% ");
        //qry.bindValue(":ref", k);

        qry.exec("SELECT * FROM AFF WHERE type LIKE '1%'");

        //qDebug() << "Number of Rows: " << qry.size();
        while(qry.next())
            row_count++;


                //qDebug()<<q.numRowsAffected();
        qDebug()<<row_count;
                return row_count;
    }
    int Affaire::nb2(){
        QSqlQuery qry;
        int  row_count=0;
        //qry.prepare("SELECT * FROM table1 WHERE E  LIKE d% ");
        //qry.bindValue(":ref", k);

        qry.exec("SELECT * FROM AFF WHERE type LIKE '2%'");

        //qDebug() << "Number of Rows: " << qry.size();
        while(qry.next())
            row_count++;


                //qDebug()<<q.numRowsAffected();
        qDebug()<<row_count;
                return row_count;
    }
    int Affaire::nbs(){
        QSqlQuery qry;
        int  row_count=0;
        //qry.prepare("SELECT * FROM table1 WHERE E  LIKE d% ");
        //qry.bindValue(":ref", k);

        qry.exec("SELECT * FROM AFF WHERE type LIKE 's%'");

        //qDebug() << "Number of Rows: " << qry.size();
        while(qry.next())
            row_count++;


                //qDebug()<<q.numRowsAffected();
        qDebug()<<row_count;
                return row_count;
    }
    int Affaire::nbtout(){
        QSqlQuery qry;
        int  row_count=0;
        //qry.prepare("SELECT * FROM table1 WHERE E  LIKE d% ");
        //qry.bindValue(":ref", k);

        qry.exec("SELECT * FROM AFF ");

        //qDebug() << "Number of Rows: " << qry.size();
        while(qry.next())
            row_count++;


                //qDebug()<<q.numRowsAffected();
        qDebug()<<row_count;
                return row_count;
    }

    QSqlQueryModel* Affaire::afficher()
    {
        QSqlQueryModel *model=new QSqlQueryModel();
        model->setQuery("SELECT* FROM AFF");
      //model->setHeaderData(0, Qt::Horizontal, QObject::tr("reference"));
      //model->setHeaderData(1, Qt::Horizontal, QObject::tr("cin"));
       // ui->tableView_aff_h->setModel(model);


        return model;



    }
    QSqlQueryModel* Affaire::afficherh()
    {
        QSqlQueryModel *model=new QSqlQueryModel();

        model->setQuery("SELECT* FROM Affhs");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("reference"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("cin"));


        return model;



    }
    bool Affaire::supprimer(int reference ){
        QString aff_string=QString::number(reference);
        QSqlQuery query;
        QSqlQueryModel *model= new QSqlQueryModel();



        query.prepare("SELECT * FROM Aff WHERE (reference  LIKE "+aff_string+  ")");

        if(query.exec()){
        model->setQuery(query);
        }


        if(query.numRowsAffected()==0){

           QMessageBox::warning(nullptr, QObject::tr("database is open"),
                       QObject::tr("Affaire introvale .\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);


      }else{
           /*query.prepare(" SELECT * FROM AFF where reference=:reference");
            query.bindValue(":reference", reference);

             query.exec();*/




            query.prepare("Delete from  Aff where reference=:reference");
            query.bindValue(":reference", reference);

            return query.exec();


        }

        return false;

    }
    void Affaire ::chercher(QTableView *table,int cas )
     {
         QSqlQueryModel *model= new QSqlQueryModel();

         QSqlQuery *query=new QSqlQuery;
         QString cas_string=QString::number(cas);

         query->prepare("SELECT * FROM Aff WHERE (reference  LIKE "+cas_string+  ")");

         //model->setQuery("SELECT* FROM Aff");

        // model->setQuery(*query);
         query->exec();

         if(query->exec()){
         model->setQuery(*query);
         table->setModel(model);
         table->show();
         }


         if(query->numRowsAffected()==0){

            QMessageBox::warning(nullptr, QObject::tr("database is open"),
                        QObject::tr("Affaire introvale .\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);


       }

     }
    bool Affaire::supprimert( ){

        QSqlQuery query;
        QSqlQueryModel *model= new QSqlQueryModel();

        query.prepare("Delete from  Aff ");
        if(query.exec()){
        model->setQuery(query);
        }

        return query.exec();


    }

    bool Affaire::modifier()
    {
        QString reference_string=QString::number(reference);
          QString idjuge_string=QString::number(idjuge);
          QString idavocat_string=QString::number(idavocat);

          QString cinp_string=QString::number(cinpersonne);

          QString numsalle_string=QString::number(num_salle);

          QSqlQuery queryr;

          QSqlQuery queryj;
          QSqlQuery querya;

          QSqlQuery queryp;

          QSqlQuery querys;


          QSqlQueryModel *modelj= new QSqlQueryModel();
          QSqlQueryModel *modela= new QSqlQueryModel();

          QSqlQueryModel *modelp= new QSqlQueryModel();

          QSqlQueryModel *models= new QSqlQueryModel();
          QSqlQueryModel *modelr= new QSqlQueryModel();


          queryr.prepare("SELECT * FROM Aff WHERE (reference  LIKE "+reference_string+  ")");

          queryj.prepare("SELECT * FROM JUGE WHERE (IDJUGE  LIKE "+idjuge_string+  ")");
          querya.prepare("SELECT * FROM AVOCAT WHERE (ID  LIKE "+idavocat_string+  ")");

          queryp.prepare("SELECT * FROM PERSONNE WHERE (CIN  LIKE "+cinp_string+  ")");

          querys.prepare("SELECT * FROM SALLE WHERE (NUM  LIKE "+numsalle_string+  ")");



          if(queryj.exec()){
          modelj->setQuery(queryj);
          }
          if(querya.exec()){
          modela->setQuery(querya);
          }
          if(queryp.exec()){
          modelp->setQuery(queryp);
          }
          if(querys.exec()){
          models->setQuery(querys);
          }

      if(queryr.exec()){
      modelr->setQuery(queryr);
      }



          if(queryj.numRowsAffected()==0){
             QMessageBox::warning(nullptr, QObject::tr("database is open"),
                         QObject::tr("juge introvale .\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);


        }else if(querya.numRowsAffected()==0){QMessageBox::warning(nullptr, QObject::tr("database is open"),
                                                                       QObject::tr("avocat introvale .\n"
                                                                                   "Click Cancel to exit."), QMessageBox::Cancel);
  }else if(queryp.numRowsAffected()==0){QMessageBox::warning(nullptr, QObject::tr("database is open"),
                                                             QObject::tr("personne introvale .\n"
                                                                         "Click Cancel to exit."), QMessageBox::Cancel);
  }else if(querys.numRowsAffected()==0){QMessageBox::warning(nullptr, QObject::tr("database is open"),
                                                             QObject::tr("salle introvale .\n"
                                                                         "Click Cancel to exit."), QMessageBox::Cancel);
  }
          else if(queryr.numRowsAffected()==0){QMessageBox::warning(nullptr, QObject::tr("database is open"),
                                                                     QObject::tr("affaire introvable .\n"
                                                                                 "Click Cancel to exit."), QMessageBox::Cancel);
          }



          else{
    QSqlQuery query;

    /*QString id_string=QString::number(reference);
    query.prepare("INSERT INTO AffHM  SELECT * FROM AFF where reference=:reference ");
    query.bindValue(":reference", reference);
    query.exec();*/

    query.prepare("UPDATE Aff SET ordre=:ordreee,idjuge=:idjudee,numsalle=:numsallee,cinpersonne=:cinpersonnee,idavocat=:idavocatt,type=:typee,datea=:datee WHERE reference=:referencee;");

    query.bindValue(":referencee",reference);
        query.bindValue(":ordreee",ordre);
        query.bindValue(":typee",type);
        query.bindValue(":datee",date);
        query.bindValue(":idjudee",idjuge);
           query.bindValue(":idavocatt",idavocat);
           query.bindValue(":cinpersonnee",cinpersonne);

           query.bindValue(":numsallee",num_salle);





    return    query.exec();}
          return  false;
    }
    int Affaire::pdf(){
        QPrinter printer;
              printer.setOutputFormat(QPrinter::PdfFormat);
              printer.setOutputFileName("C:/Users/h4561/OneDrive/Bureau/gestion des affaires/g.pdf");
              QPainter painter;
              if (! painter.begin(&printer)) { // failed to open file
                  qWarning("failed to open file, is it writable?");
                  return 1;
              }
              painter.drawText(10, 10, "Test");
              if (! printer.newPage()) {
                  qWarning("failed in flushing page to disk, disk full?");
                  return 1;
              }
              painter.drawText(10, 10, "Test 2");
              painter.end();
              return 1;


    }
