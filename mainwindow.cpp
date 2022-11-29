#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "statistique.h"
#include "mail.h"
#include "mailsmtp.h"
#include "window.h"
#include <QVariant>
#include <QSqlQuery>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QUrl>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QtDebug>
#include <QPdfWriter>
#include <QPainter>
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>
#include <QDate>
#include <QSettings>
#include <QSettings>
#include <QApplication>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QtCore>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>


#include "calendrier.h"
#include"juje.h"
QString days="";
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    QPixmap pix("C:/Users/omarz/OneDrive/Documents/gestion_des_juges/courtt");
    ui->label_pic->setPixmap(pix.scaled(949,902,Qt::KeepAspectRatio));
   ui-> tableView_aff_h->setModel(j.afficher());
   ui-> tableView_aff_h_2->setModel(j.afficher());
// ui-> tableView_aff_h_3->setModel(j.afficher());
ui->id->setValidator(new QIntValidator(0, 999999, this));
 /*ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
  ui->quickWidget->show();

auto obj = ui->quickWidget->rootObject();

connect(this, SIGNAL(setCenter(QVariant, QVariant)), obj, SLOT(setCenter(QVariant, QVariant)));
 connect(this, SIGNAL(addMarker(QVariant, QVariant)), obj, SLOT(addMarker(QVariant, QVariant)));

 emit setCenter(25.000, 50.000);
 emit addMarker(25.000, 50.000);
*/
//for email tab
connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));

 //maps
 QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                    QCoreApplication::organizationName(), QCoreApplication::applicationName());

 ui->WebBrowser_2->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");

  //ui->axWidget->show();
 //calendrier
/*QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                   (QCoreApplication::organizationName(), QCoreApplication::applicationName());

 ui->WebBrowser_3->dynamicCall("Navigate(const QString&)", "https://calendar.google.com/calendar/u/0/r");*/

}
void MainWindow::update()
{
    data=A.read_from_arduino();


   if(data=="1")
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr(" rrrr"+data+"rrr.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_ajouter_clicked()
{
    int idd=ui->id->text().toInt();
    QString mdpp=ui->mdp->text();
    QString nomm=ui->nom->text();

            QString prenomn=ui->prenom->text();
            QString maill=ui->mail->text();
          QString date=ui->_date_h_2->text();

                    QString typee=ui->comboBox_9->currentText();
                    juje j( idd, mdpp, prenomn, nomm, typee,  maill,date);
                    ui-> tableView_aff_h->setModel(j.afficher());

bool test =j.ajouter();
if(test )
{
    QMessageBox::information(nullptr, QObject::tr("database is open"),
                QObject::tr("ajout successful.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
    ui-> tableView_aff_h->setModel(j.afficher());

ui-> tableView_aff_h_2->setModel(j.afficher());

}
else{
    QMessageBox::information(nullptr, QObject::tr("database is not open"),
                QObject::tr("ajout failed.\n"

                  "Click Cancel to exit."), QMessageBox::Cancel);}
}




void MainWindow::on_pushButton_Sui_m_clicked()
{
    juje j;
    j.setid(ui->lineEdit_idS_h->text().toInt());
    bool test =j.supprimer(j.getid());
    if(test )
    {
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("supprimer successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui-> tableView_aff_h->setModel(j.afficher());

ui-> tableView_aff_h_2->setModel(j.afficher());

    }
    else{
        QMessageBox::information(nullptr, QObject::tr("database is not open"),
                    QObject::tr("supprimer failed.\n"

                      "Click Cancel to exit."), QMessageBox::Cancel);}
    }



void MainWindow::on_pushButton_trier_3_clicked()
{
    int ch=ui->Psearch_5->text().toInt();
    juje j;
   // j.chercher()
     j.chercher(ui->tableView,ch);

     /*if(ui->Psearch_5->text().isEmpty())
         {
             ui->tableView->setModel(j.afficher());
         }*/
}

void MainWindow::on_pushButton_ajouter_4_clicked()
{


    int idd=ui->id_2->text().toInt();
    QString mdpp=ui->mdp_2->text();
    QString nomm=ui->nom_2->text();

            QString prenomn=ui->prenom_2->text();
            QString maill=ui->mail_2->text();
          QString date=ui->_date_h_2->text();

                    QString typee=ui->comboBox_10->currentText();

                    juje j( idd, mdpp, prenomn, nomm, typee,  maill,date);




                    bool test =j.modifier();
                    if(test )
                    {
                        QMessageBox::information(nullptr, QObject::tr("database is open"),
                                    QObject::tr("modifier successful.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
 ui-> tableView_aff_h->setModel(j.afficher());
ui-> tableView_aff_h_2->setModel(j.afficher());
                    }
                    else{
                        QMessageBox::information(nullptr, QObject::tr("database is not open"),
                                    QObject::tr("modifier failed.\n"

                                      "Click Cancel to exit."), QMessageBox::Cancel);}
                    }









void MainWindow::on_pushButton_trier_clicked()
{

        QSqlQueryModel *model= new QSqlQueryModel();
        QSqlQuery *query=new QSqlQuery;

        query->prepare("SELECT * FROM jugeee ORDER BY identifiant  DESC ");


        query->exec();

        if (query->exec()&&query->next()) {
            model->setQuery(*query);

            ui->tableView_aff_h->setModel(model);

    QMessageBox::information(nullptr, QObject::tr("database is not open"),
                                    QObject::tr("trie succes.\n"

                                      "Click Cancel to exit."), QMessageBox::Cancel);
                    }}

/*//recherche dynamique
void MainWindow::on_recherche_textChanged(const QString &arg1)
{
proxy->setFilterFixedString(arg1);
}*/


//mailing
void  MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}

  void   MainWindow::sendMail()
{
      Smtp* smtp = new Smtp("omar.zaghouani@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
      connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

      if( !files.isEmpty() )
          smtp->sendMail("omar.zaghouani@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
      else
          smtp->sendMail("omar.zaghouani@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}




  void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->id->clear();
    ui->nom->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}





void MainWindow::on_pushButton_17_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                           "/home",
                                                           QFileDialog::ShowDirsOnly
                                                           | QFileDialog::DontResolveSymlinks);
               qDebug()<<dir;
               QPdfWriter pdf(dir+"/PdfList.pdf");
                                      QPainter painter(&pdf);
                                     int i = 4000;

       //   painter.drawPixmap(QRect(100,100,2000,2000),QPixmap("C:/Users/omarz/Dropbox/PC/Downloads/logo.png"));

                                         painter.drawText(900,650,"omar zaghouani");

                                          painter.drawPixmap(QRect(7600,100,1900,2500),QPixmap("C:/Users/omarz/Dropbox/PC/Downloads/logo.png"));

                                          painter.setPen(Qt::darkYellow);
                                          painter.setFont(QFont("Time New Roman", 25));
                                          painter.drawText(3000,1400,"Liste Des juges");
                                          painter.setPen(Qt::darkYellow);
                                          painter.setFont(QFont("Time New Roman", 15));
                                          painter.drawRect(100,100,9400,2500);
                                          painter.drawRect(100,3000,9400,500);
                                          painter.setFont(QFont("Time New Roman", 9));
                                          painter.drawText(300,3300,"identifiant");
                                          painter.drawText(2300,3300,"Prenom");
                                          painter.drawText(4300,3300,"Nom");
                                          painter.drawText(6300,3300,"mot de passe");
                                          painter.drawText(7500,3300,"type");
                                         /* painter.drawText(8500,3300,"Date ");
                                          painter.drawText(9500,3300,"Date Retour");
                                          painter.drawText(10500,3300,"Date Naissance");*/

                                          painter.drawRect(100,3000,9400,10700);


                                          QTextDocument previewDoc;
                                          QString pdflist = QDate::currentDate().toString("'data_'MM_dd_yyyy'.txt'");


                                          QTextCursor cursor(&previewDoc);



                                          QSqlQuery query;
                                          query.prepare("select * from jugeee");
                                          query.exec();
                                          while (query.next())
                                          {
                                              painter.drawText(300,i,query.value(0).toString());
                                              painter.drawText(2300,i,query.value(1).toString());
                                              painter.drawText(4300,i,query.value(2).toString());
                                              painter.drawText(6300,i,query.value(3).toString());
                                              painter.drawText(7500,i,query.value(4).toString());
                                             /* painter.drawText(8500,i,query.value(5).toString());
                                              painter.drawText(9500,i,query.value(6).toString());
                                              painter.drawText(10500,i,query.value(7).toString());*/




                                             i = i +500;
                                          }
                                          int reponse = QMessageBox::question(this, "Générer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                                                              QMessageBox::Yes|QMessageBox::No);
                                              if (reponse == QMessageBox::Yes)
                                              {
                                                  QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfList.pdf"));

                                                  painter.end();
                                              }
                                              else
                                              {
                                                   painter.end();
     }

}

void MainWindow::on_pushButton_Actualise_h_clicked()
{
    QSqlQueryModel *model= new QSqlQueryModel();
    QSqlQuery *query=new QSqlQuery;

    query->prepare("SELECT * FROM jugeee ORDER BY identifiant  ASC ");


    query->exec();

    if (query->exec()&&query->next()) {
        model->setQuery(*query);

        ui->tableView_aff_h->setModel(model);

QMessageBox::information(nullptr, QObject::tr("database is not open"),
                                QObject::tr("trie succes.\n"

                                  "Click Cancel to exit."), QMessageBox::Cancel);
                }

}

void MainWindow::on_pushButton_Sui_m_2_clicked()
{


   statistique s;
           s.exec();
}

void MainWindow::on_pushButton_ajouter_5_clicked()
{
    int idd=ui->id->text().toInt();
    QString mdpp=ui->mdp->text();
    QString nomm=ui->nom->text();

            QString prenomn=ui->prenom->text();
            QString maill=ui->mail->text();
          QString date=ui->_date_h_2->text();

                    QString typee=ui->comboBox_9->currentText();
                    juje j( idd, mdpp, prenomn, nomm, typee,  maill,date);
                    ui-> tableView_aff_h->setModel(j.afficher());

bool test =j.ajouter();
if(test )
{
    QMessageBox::information(nullptr, QObject::tr("database is open"),
                QObject::tr("ajout successful.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
  //  ui-> tableView_aff_h->setModel(j.afficher());

//ui-> tableView_aff_h_2->setModel(j.afficher());

}
else{
    QMessageBox::information(nullptr, QObject::tr("database is not open"),
                QObject::tr("ajout failed.\n"

                  "Click Cancel to exit."), QMessageBox::Cancel);}
}



void MainWindow::on_sendBtn_clicked()
{
    Smtp* smtp = new Smtp("omar.zaghouani@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("omar.zaghouani@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("omar.zaghouani@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());

    {
            QMessageBox::information(nullptr, QObject::tr("OK"),
                        QObject::tr("mail envoyé\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);


            /*QString link="https://mail.google.com/mail/u/0/#inbox?compose=new";
                QDesktopServices::openUrl(link);*/

    }
  }








void MainWindow::on_sendBtn_2_clicked()
{
    QString link="https://mail.google.com/mail/u/1/#inbox?compose=new";
        QDesktopServices::openUrl(link);
}


void MainWindow::on_calendarWidget_clicked(const QDate &date)

{
    days=days+date.toString()+"|";
        ui->les_jours->setText(days);


}








/*void MainWindow::on_pushButton_ajouter_6_clicked()
{
    QString moiss=ui->mois->text();
    QString jourr=ui->jour->text();

            QString anneee=ui->annee->text();
            bool test =j.ajouter();
            if(test )
            {
                QMessageBox::information(nullptr, QObject::tr("database is open"),
                            QObject::tr("ajout calendrier successful.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);
               // ui-> tableView_aff_h->setModel(j.afficher());

            //ui-> tableView_aff_h_2->setModel(j.afficher());
                ui-> tableView_aff_h_3->setModel(j.afficher());

            }
            else{
                QMessageBox::information(nullptr, QObject::tr("database is not open"),
                            QObject::tr("ajout  calendrier failed.\n"

                              "Click Cancel to exit."), QMessageBox::Cancel);}

}
*/

void MainWindow::on_pushButton_Sui_m_3_clicked()
{

    QPieSeries *series = new QPieSeries();


               QStringList list=j.listeadresses("identifiant");

 ui-> tableView_aff_h->setModel(j.afficher());
   //ui-> tableView_aff_h_2->setModel(j.afficher());
               for (int i =0; i< list.size();i++)
               {
                   //series->append(list[i],j.calcul_adresses(list[i],"identifiant"));
ui-> tableView_aff_h->setModel(j.afficher());

               }
               QPieSlice *slice = series->slices().at(5);
               ui-> tableView_aff_h->setModel(j.afficher());
               slice->setLabelVisible();
               slice->setExploded();


               QtCharts::QChart *chart =new QtCharts::QChart();
               chart->addSeries(series);
               chart->setTitle("Statistiques");
               chart->setAnimationOptions(QChart::AllAnimations);
               QChartView *chartview=new QChartView(chart);
               //modi
               chartview = new QChartView(chart,ui->statistiques_4);
                                   chartview->setRenderHint(QPainter::Antialiasing);
                                   chartview->setMinimumSize(600,380);
               QGridLayout *mainLayout=new QGridLayout();
               mainLayout->addWidget(chartview,0,0);
               ui->statistiques_4->setLayout(mainLayout);

ui-> tableView_aff_h->setModel(j.afficher());
}

void MainWindow::on_sendBtn_3_clicked()
{
    QString link="https://calendar.google.com/calendar/u/0/r";
        QDesktopServices::openUrl(link);
}

void MainWindow::on_sendBtn_4_clicked()
{
    QString link="https://calendar.google.com/calendar/u/0/r";
        QDesktopServices::openUrl(link);
}

void MainWindow::on_ent_date_Aj_userDateChanged(const QDate &date)
{
    days=days+date.toString()+"|";
        ui->les_jours->setText(days);
}
