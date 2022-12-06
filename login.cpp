#include "login.h"
#include "juge.h"
#include "ui_login.h"
#include <QPixmap>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
   // QPixmap pix("C:/Users/msi/Desktop/untitled3d/rsc/back.png");
    //ui->label_3->setPixmap(pix.scaled(800,802,Qt::KeepAspectRatio));
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_pb_connecter_clicked()
{    bool alreadyExist = false;
     bool alreadyExist1 = false;

      QString nom_utilisateur=ui->le_nom->text();
      int mdp=ui-> le_mdp->text().toInt();
      QSqlQuery query;
      QSqlQuery query1;

      query.prepare("select * from aff where reference=:mdp ");
      query.bindValue(":reference",mdp);

      query1.prepare("select * from jegge where mdp=:mdp ");

      query1.bindValue(":mdp",mdp);

      query.addBindValue(ui-> le_mdp->text());
      query1.addBindValue(ui-> le_mdp->text());

      query.exec();
      query1.exec();



          alreadyExist = query.next();
          alreadyExist1 = query1.next();

          if(alreadyExist)
          {

                ui->le_nom->setText("");
                ui->le_mdp->setText("");
                this->hide();
                close() ;
               QMessageBox msgbox ;
               msgbox.setText("Bienvenue "+nom_utilisateur+"") ;
               msgbox.exec() ;
             M= new MainWindow(this);
                M->show();




                QApplication::setQuitOnLastWindowClosed(false);




          }
          else  if(alreadyExist1)
              {

              ui->le_nom->setText("");
              ui->le_mdp->setText("");
              this->hide();
                  M=new MainWindow1 (this);
                  M->show();


QApplication::setQuitOnLastWindowClosed(false);
              ui->le_nom->setText("");
              ui->le_mdp->setText("");
               }else{
              QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                                                         QObject::tr("NOM D'UTILISATEUR OU MOT DE PASSE INCORRECTE.\n" "Click Cancel to exit."), QMessageBox::Cancel);}



}
int login::ret(){
    bool alreadyExist = false;
        bool alreadyExist1 = false;

         QString nom_utilisateur=ui->le_nom->text();
         int mdp=ui-> le_mdp->text().toInt();
         QSqlQuery query;
         QSqlQuery query1;

         query.prepare("select * from aff where reference=:mdp ");
         query.bindValue(":reference",mdp);

         query1.prepare("select * from jegge where mdp=:mdp ");

         query1.bindValue(":mdp",mdp);

         query.addBindValue(ui-> le_mdp->text());
         query1.addBindValue(ui-> le_mdp->text());

         query.exec();
         query1.exec();



             alreadyExist = query.next();
             alreadyExist1 = query1.next();

    if(alreadyExist){
    return 1;}          else  if(alreadyExist1){return 2;} else{return 0;}

}
int login::retmdp(){int mdp=ui-> le_mdp->text().toInt(); return mdp; }
