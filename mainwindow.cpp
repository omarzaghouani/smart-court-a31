#include "mainwindow.h"
#include "ui_mainwindow.h"
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
#include <QApplication>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QtCore>



#include"juje.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/omarz/OneDrive/Documents/gestion_des_juges/courtt");
    ui->label_pic->setPixmap(pix.scaled(949,902,Qt::KeepAspectRatio));
   ui-> tableView_aff_h->setModel(j.afficher());
   ui-> tableView_aff_h_2->setModel(j.afficher());

ui->id->setValidator(new QIntValidator(0, 999999, this));
 ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/map.qml")));
  ui->quickWidget->show();

auto obj = ui->quickWidget->rootObject();

connect(this, SIGNAL(setCenter(QVariant, QVariant)), obj, SLOT(setCenter(QVariant, QVariant)));
 connect(this, SIGNAL(addMarker(QVariant, QVariant)), obj, SLOT(addMarker(QVariant, QVariant)));

 emit setCenter(25.000, 50.000);
 emit addMarker(25.000, 50.000);

 /*//maps
 QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                    QCoreApplication::organizationName(), QCoreApplication::applicationName());

 ui->quickWidget->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");

*/

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

        query->prepare("SELECT * FROM jugeee ORDER BY identifiant ASC");


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


/*//mailing
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

}*/
/*
 * void   MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("mohamedaziz.benhaha@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("mohamedaziz.benhaha@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("mohamedaziz.benhaha@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
 */


/*
 * void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->id->clear();
    ui->nom->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}

  */


/*
 * //pdf : vous trouver le fichier dans le dossier build
void MainWindow::on_pdf_clicked()
{

    QString strStream;
                QTextStream out(&strStream);
                const int rowCount = ui->tableau->model()->rowCount();
                const int columnCount =ui->tableau->model()->columnCount();


                out <<  "<html>\n"
                        "<head>\n"
                        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                        <<  QString("<title>%1</title>\n").arg("eleve")
                        <<  "</head>\n"
                        "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                            "<h1>Liste des Evenements</h1>"

                            "<table border=1 cellspacing=0 cellpadding=2>\n";

                // headers
                    out << "<thead><tr bgcolor=#f0f0f0>";
                    for (int column = 0; column < columnCount; column++)
                        if (!ui->tableau->isColumnHidden(column))
                            out << QString("<th>%1</th>").arg(ui->tableau->model()->headerData(column, Qt::Horizontal).toString());
                    out << "</tr></thead>\n";
                    // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tableau->isColumnHidden(column)) {
                                   QString data = ui->tableau->model()->data(ui->tableau->model()->index(row, column)).toString().simplified();
                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                               }
                           }
                           out << "</tr>\n";
                       }
                       out <<  "</table>\n"
                           "</body>\n"
                           "</html>\n";



        QTextDocument *document = new QTextDocument();
        document->setHtml(strStream);


        //QTextDocument document;
        //document.setHtml(html);
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("mypdffile.pdf");
        document->print(&printer);

}

 **/





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

                                       painter.drawPixmap(QRect(100,100,2000,2000),QPixmap("C:/Users/Admin/Desktop/logo.png"));
                                           painter.drawText(900,650,"omar zaghouani");

                                            //painter.drawPixmap(QRect(7600,100,2100,2700),QPixmap("C:/Users/Admin/Desktop/logo.png"));

                                            painter.setPen(Qt::blue);
                                            painter.setFont(QFont("Time New Roman", 25));
                                            painter.drawText(3000,1400,"Liste Des juges");
                                            painter.setPen(Qt::black);
                                            painter.setFont(QFont("Time New Roman", 15));
                                            painter.drawRect(100,100,9400,2500);
                                            painter.drawRect(100,3000,9400,500);
                                            painter.setFont(QFont("Time New Roman", 9));
                                            painter.drawText(300,3300,"identifiant");
                                            painter.drawText(2300,3300,"Prenom");
                                            painter.drawText(4300,3300,"Nom");
                                            painter.drawText(6300,3300,"type");
                                            painter.drawText(7500,3300,"mot de passe");
                                           /* painter.drawText(8500,3300,"ema");
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
