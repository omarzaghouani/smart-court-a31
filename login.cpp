#include "login.h"
#include "juje.h"
#include "ui_login.h"
#include <QPixmap>
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/omarz/Dropbox/PC/Downloads/login.png");
    ui->label_3->setPixmap(pix.scaled(800,802,Qt::KeepAspectRatio));
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).
}

login::~login()
{
    delete ui;
}

void login::on_pb_connecter_clicked()
{
      QString nom_utilisateur=ui->le_nom->text();
      QString mdp=ui-> le_mdp->text();
      QSqlQuery query;
      query.prepare("select * from jugeee where identifiant=:identifiant and mdp=:mdp");
      query.addBindValue(ui->le_nom->text());
      query.addBindValue(ui-> le_mdp->text());
      query.exec();
          bool alreadyExist = false;
          alreadyExist = query.next();
          if(alreadyExist)
          {

                ui->le_nom->setText("");
                ui->le_mdp->setText("");
                this->hide();
                M=new MainWindow(this);
                M->show();
                //juje j;




               /*QMessageBox msgbox ;
               msgbox.setText("Bienvenue "+j.getid+"") ;
               msgbox.exec() ;*/



          }
          else
              {
              QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                                               QObject::tr("NOM D'UTILISATEUR OU MOT DE PASSE INCORRECTE.\n" "Click Cancel to exit."), QMessageBox::Cancel);
              ui->le_nom->setText("");
              ui->le_mdp->setText("");
               }


}

void login::update()
{
    data=A.read_from_arduino();


   if(data=="1")
     {  M=new MainWindow(this);
       M->show();


}



}
