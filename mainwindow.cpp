#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"affaire.h"
#include "audiolevel.h"

#include <QMediaPlayer>
#include <QLoggingCategory>
#include <QtTextToSpeech>
#include <QLoggingCategory>
#include<QFile>
#include <QLabel>
#include<QtCharts>
#include <QMediaRecorder>
#include <QDir>
#include <QFileDialog>
#include <QMediaRecorder>
#include <QStandardPaths>
#include <qmediadevices.h>
#include <qmediaformat.h>
#include <qaudiodevice.h>
#include <qaudiobuffer.h>
#include <qaudioinput.h>
#include <qimagecapture.h>
#include <QMimeType>
#include <QAudioOutput>

static QList<qreal> getBufferLevels(const QAudioBuffer &buffer);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    m_speech(nullptr),file("df.txt")
{
    ui->setupUi(this);

    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->resizeRowsToContents();

    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
                        QMessageBox::warning(nullptr, QObject::tr("database is open"),
                                    QObject::tr("noitq qqoooq .\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
    QTextStream out(&file);

    out<<"★★★★★★★★★★★★★★★★★★☯☯🅷🅸🆂🆃🅾🆁🅸🆀🆄🅴 🅳🅴 🅶🅴🆂🆃🅸🅾🅽 🅳🅴🆂 🅰🅵🅵🅰🅸🆁🅴🆂☯☯★★★★★★★★★★★★★★★★★\n";

    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM AFF");
    ui->tableView_aff_h->setModel(model);

    QLoggingCategory::setFilterRules(QStringLiteral("qt.speech.tts=true \n qt.speech.tts.*=true"));

    // Populate engine selection list
    ui->engine->addItem("Default", QString("default"));
    const auto engines = QTextToSpeech::availableEngines();
    for (const QString &engine : engines)
        ui->engine->addItem(engine, engine);
    ui->engine->setCurrentIndex(0);
    engineSelected(0);

    connect(ui->speakButton, &QPushButton::clicked, this, &MainWindow::speak);
    connect(ui->pitch, &QSlider::valueChanged, this, &MainWindow::setPitch);
    connect(ui->rate, &QSlider::valueChanged, this, &MainWindow::setRate);
    connect(ui->volume, &QSlider::valueChanged, this, &MainWindow::setVolume);
    connect(ui->engine, &QComboBox::currentIndexChanged, this, &MainWindow::engineSelected);
    ui->reference->setValidator(new QIntValidator(0, 999999, this));
    ui->idjuge->setValidator(new QIntValidator(0, 999999, this));
    ui->idavocat->setValidator(new QIntValidator(0, 999999, this));
    ui->cin_p->setValidator(new QIntValidator(0, 999999, this));

    ui->num_salle->setValidator(new QIntValidator(0, 999999, this));
//QObject::connect(ui->on_pushButton_15_clicked,&QPushButton::clicke,this,&MainWindow::on_pushButton_15_clicked);
    connect(ui->pushButton_15, SIGNAL(clicked()),this, SLOT(on_pushButton_15_clicked()));

    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(voice_afficher())); // permet de lancer
    //ui->tableView_aff_h_3->setModel(ff.afficher());
    ui->listView_2->setModel(ff.afficher());


    //ui->tableWidget->setRowCount(4);
    //record

    m_audioRecorder = new QMediaRecorder(this);
    m_captureSession.setRecorder(m_audioRecorder);
    m_captureSession.setAudioInput(new QAudioInput(this));
    // ### replace with a monitoring output once we have it.
//    m_probe = new QAudioProbe(this);
//    connect(m_probe, &QAudioProbe::audioBufferProbed,
//            this, &AudioRecorder::processBuffer);
//    m_probe->setSource(m_audioRecorder);

    //audio devices
    ui->audioDeviceBox_3->addItem(tr("Default"), QVariant(QString()));
    for (auto device: QMediaDevices::audioInputs()) {
        auto name = device.description();
        ui->audioDeviceBox_3->addItem(name, QVariant::fromValue(device));
    }

    //audio codecs and container formats
    updateFormats();
    connect(ui->audioCodecBox_3, &QComboBox::currentIndexChanged, this, &MainWindow::updateFormats);
    connect(ui->containerBox_3, &QComboBox::currentIndexChanged, this, &MainWindow::updateFormats);

    //sample rate
    ui->sampleRateBox_3->setRange(m_captureSession.audioInput()->device().minimumSampleRate(),
                                m_captureSession.audioInput()->device().maximumSampleRate());
    ui->sampleRateBox_3->setValue(qBound(m_captureSession.audioInput()->device().minimumSampleRate(), 44100,
                                       m_captureSession.audioInput()->device().maximumSampleRate()));

    //channels
    ui->channelsBox_3->addItem(tr("Default"), QVariant(-1));
    ui->channelsBox_3->addItem(QStringLiteral("1"), QVariant(1));
    ui->channelsBox_3->addItem(QStringLiteral("2"), QVariant(2));
    ui->channelsBox_3->addItem(QStringLiteral("4"), QVariant(4));

    //quality
    ui->qualitySlider_3->setRange(0, int(QImageCapture::VeryHighQuality));
    ui->qualitySlider_3->setValue(int(QImageCapture::NormalQuality));

    //bit rates:
    ui->bitrateBox_3->addItem(tr("Default"), QVariant(0));
    ui->bitrateBox_3->addItem(QStringLiteral("32000"), QVariant(32000));
    ui->bitrateBox_3->addItem(QStringLiteral("64000"), QVariant(64000));
    ui->bitrateBox_3->addItem(QStringLiteral("96000"), QVariant(96000));
    ui->bitrateBox_3->addItem(QStringLiteral("128000"), QVariant(128000));

    connect(m_audioRecorder, &QMediaRecorder::durationChanged, this, &MainWindow::updateProgress);
    connect(m_audioRecorder, &QMediaRecorder::recorderStateChanged, this, &MainWindow::onStateChanged);
    connect(m_audioRecorder, &QMediaRecorder::errorChanged, this, &MainWindow::displayErrorMessage);

}
void MainWindow:: voice_afficher(){
    QMediaPlayer *player = new QMediaPlayer;
               QAudioOutput* audioOutput = new QAudioOutput;
               player->setAudioOutput(audioOutput);
    data=A.read_from_arduino();
    if(data=="1")
{
        ui->tabWidget->setCurrentIndex(0);


               on_pushButton_ajouter_clicked();




}else if(data=="0"){
        ui->tabWidget->setCurrentIndex(1);

        ui->tableView_aff_h->setModel(ff.afficher());


    }else if(data=="2"){


                   player->setSource(QUrl::fromLocalFile("C:/Users/msi/Desktop/dsq/untitled3d/rsc/fichier.mp3"));
                   audioOutput->setVolume(50);
                   player->play();
        ui->tabWidget->setCurrentIndex(2);

on_outputButton_3_clicked();
on_pushButton_2_clicked();
    }else if(data=="3"){

        ui->tabWidget->setCurrentIndex(2);

        on_pauseButton_4_clicked();
        player->setSource(QUrl::fromLocalFile("C:/Users/msi/Desktop/dsq/untitled3d/rsc/succesenreg.mp3"));
        audioOutput->setVolume(50);
        player->play();

    }else if(data=="4"){
        ui->tabWidget->setCurrentIndex(4);

      on_pushButton_clicked();
    }else if(data=="5"){
        ui->tabWidget->setCurrentIndex(3);

        speak();
    }






     }








void MainWindow::speak()
{
    m_speech->say(ui->plainTextEdit->toPlainText());
}
void MainWindow::stop()
{
    m_speech->stop();
}

void MainWindow::setRate(int rate)
{
    m_speech->setRate(rate / 10.0);
}

void MainWindow::setPitch(int pitch)
{
    m_speech->setPitch(pitch / 10.0);
}

void MainWindow::setVolume(int volume)
{
    m_speech->setVolume(volume / 100.0);
}

void MainWindow::stateChanged(QTextToSpeech::State state)
{
    if (state == QTextToSpeech::Speaking) {
        ui->statusbar->showMessage("Speech started...");
    } else if (state == QTextToSpeech::Ready)
        ui->statusbar->showMessage("Speech stopped...", 2000);
    else if (state == QTextToSpeech::Paused)
        ui->statusbar->showMessage("Speech paused...");
    else
        ui->statusbar->showMessage("Speech error!");

    ui->pauseButton->setEnabled(state == QTextToSpeech::Speaking);
    ui->resumeButton->setEnabled(state == QTextToSpeech::Paused);
    ui->stopButton->setEnabled(state == QTextToSpeech::Speaking || state == QTextToSpeech::Paused);
}

void MainWindow::engineSelected(int index)
{
    QString engineName = ui->engine->itemData(index).toString();
    delete m_speech;
    if (engineName == "default")
        m_speech = new QTextToSpeech(this);
    else
        m_speech = new QTextToSpeech(engineName, this);
    disconnect(ui->language, &QComboBox::currentIndexChanged, this, &MainWindow::languageSelected);
    ui->language->clear();
    // Populate the languages combobox before connecting its signal.
    const QList<QLocale> locales = m_speech->availableLocales();
    QLocale current = m_speech->locale();
    for (const QLocale &locale : locales) {
        QString name(QString("%1 (%2)")
                     .arg(QLocale::languageToString(locale.language()))
                     .arg(QLocale::countryToString(locale.country())));
        QVariant localeVariant(locale);
        ui->language->addItem(name, localeVariant);
        if (locale.name() == current.name())
            current = locale;
    }
    setRate(ui->rate->value());
    setPitch(ui->pitch->value());
    setVolume(ui->volume->value());
    connect(ui->stopButton, &QPushButton::clicked, m_speech, [this]{ m_speech->stop(); });
    connect(ui->pauseButton, &QPushButton::clicked, m_speech, [this]{ m_speech->pause(); });
    connect(ui->resumeButton, &QPushButton::clicked, m_speech, &QTextToSpeech::resume);

    connect(m_speech, &QTextToSpeech::stateChanged, this, &MainWindow::stateChanged);
    connect(m_speech, &QTextToSpeech::localeChanged, this, &MainWindow::localeChanged);

    connect(ui->language, &QComboBox::currentIndexChanged, this, &MainWindow::languageSelected);
    localeChanged(current);
}

void MainWindow::languageSelected(int language)
{
    QLocale locale = ui->language->itemData(language).toLocale();
    m_speech->setLocale(locale);
}

void MainWindow::voiceSelected(int index)
{
    m_speech->setVoice(m_voices.at(index));
}

void MainWindow::localeChanged(const QLocale &locale)
{
    QVariant localeVariant(locale);
    ui->language->setCurrentIndex(ui->language->findData(localeVariant));

    disconnect(ui->voice, &QComboBox::currentIndexChanged, this, &MainWindow::voiceSelected);
    ui->voice->clear();

    m_voices = m_speech->availableVoices();
    QVoice currentVoice = m_speech->voice();
    for (const QVoice &voice : std::as_const(m_voices)) {
        ui->voice->addItem(QString("%1 - %2 - %3").arg(voice.name())
                          .arg(QVoice::genderName(voice.gender()))
                          .arg(QVoice::ageName(voice.age())));
        if (voice.name() == currentVoice.name())
            ui->voice->setCurrentIndex(ui->voice->count() - 1);
    }
    connect(ui->voice, &QComboBox::currentIndexChanged, this, &MainWindow::voiceSelected);


}

MainWindow:: ~MainWindow(){
    delete (ui);
    delete(m_speech);
    //delete(ui);

};
void MainWindow::on_pushButton_ajouter_clicked()
{
    QMediaPlayer *player = new QMediaPlayer;
    QAudioOutput* audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    int reference=ui->reference->text().toInt();
QString comboBox_ordre=ui->comboBox_ordre->currentText();
QString comboBox_type=ui->comboBox_type->currentText();
int idjuge=ui->idjuge->text().toInt();
int idavocat=ui->idavocat->text().toInt();
int  cin_p=ui->cin_p->text().toInt();

      int  num_salle=ui->num_salle->text().toInt();

QString datee=ui->_date_h->text();

    Affaire f(reference,comboBox_ordre,idjuge,comboBox_type,idavocat,cin_p,num_salle,datee);

    bool test=f.ajouter();

if (test)
{
    player->setSource(QUrl::fromLocalFile("C:/Users/msi/Desktop/dsq/untitled3d/rsc/vaj.mp3"));
    audioOutput->setVolume(50);
    player->play();

    QTextStream out(&file);
                     out<<"---------------------------AJOUTER------------------------------------------------------\n";

                     out << " REFERENCE DE L'AFFAIRE  : " << reference <<" a éte ajoutée avec succes \n";
                     out<<"ORDRE D'AFFAIRE : "<<comboBox_ordre<< "\n";
                     out<<"\n";
                     out<<"TYPE D'AFFAIRE : "<<comboBox_type<< "\n";
                     out<<"\n";
                     out<<"ID JUGE : "<<idjuge<< "\n \n";
                     out<<"ID AVOCAT : "<<idavocat<< "\n \n";
                     out<<"CIN DU  PERSONNE : "<<cin_p<< "\n \n";
                     out<<"NUMERO DU SALLE : "<<num_salle<< "\n \n";
                     out<< "DATE :" <<QDateTime::currentDateTime().toString()<< "\n \n";
                     out<<"ACTEUR :  GESTION DES AFFAIRES\n";
                     out<<"-----------------------------------------------------------------------------------------\n";
    ui->tableView_aff_h->setModel(ff.afficher());

    //ui->tableView_aff_h_3->setModel(ff.afficher());

    QMessageBox::information(nullptr, QObject::tr("félicitations"),
                QObject::tr("Ajout réussi.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
   // A.write_to_arduino("0"); //envoyer 1 à arduino



}
else{
    //A.write_to_arduino("1"); //envoyer 1 à arduino

    QMessageBox::warning(nullptr, QObject::tr("Échec"),
                QObject::tr("Échec de l'ajout.\n"

                  "Click Cancel to exit."), QMessageBox::Cancel);


        player->setSource(QUrl::fromLocalFile("C:/Users/msi/Desktop/dsq/untitled3d/rsc/vsaj.mp3"));
        audioOutput->setVolume(50);
        player->play();


}
}







void MainWindow::on_pushButton_Sui_m_clicked()
{QMediaPlayer * music = new QMediaPlayer();
    music->setSource(QUrl("qrc:/rsc/rsc/supprimer.mp3"));
    music->play();
    Affaire f;
    f.setref(ui->lineEdit_idS_h->text().toInt());
bool test=f.supprimer(f.getref());
/*if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                    QMessageBox::warning(nullptr, QObject::tr("database is open"),
                                QObject::tr("noitq qqq .\n"
                                            "Click Cancel to exit."), QMessageBox::Cancel);*/
                QTextStream out(&file);
                out<<"--------------SUPPRIMER----------------------------\n";
                out << " AFFAIRE DE REFERENCE : " << ui->lineEdit_idS_h->text().toInt() <<"  a éte Supprimée avec succes" <<"\n";
                out<< "DATE :" <<QDateTime::currentDateTime().toString()<<"\n";
                out<<"ACTEUR :  GESTION DES AFFAIRES\n";
                out<<"----------------------------------------------------\n";
if(test)
{

    ui->tableView_aff_h->setModel(ff.afficher());

    ui->listView_2->setModel(ff.afficher());

    QMessageBox::information(nullptr, QObject::tr("database is open"),
                QObject::tr("supp successful.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);


}
else
    QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                QObject::tr("supp failed.\n"

                  "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_chercher_2_clicked()
{
    QMediaPlayer * music = new QMediaPlayer();
            music->setSource(QUrl("qrc:/rsc/rsc/chercher.mp3"));
            music->play();
    int ch=ui->cher->text().toInt();
    Affaire f;
    f.chercher(ui->tableView_aff_h_2,ch);
    if(ui->cher->text().isEmpty())
    {
        ui->tableView_aff_h_2->setModel(f.afficher());
    }
}

void MainWindow::on_pushButton_Sui_m_2_clicked()
{
    QMediaPlayer * music = new QMediaPlayer();
            music->setSource(QUrl("qrc:/rsc/rsc/supprimer tout les affaires.mp3"));
            music->play();
    Affaire f;
    bool test=f.supprimert();
    if(test)
    {
        QTextStream out(&file);
                         out<<"--------------------------SUPPRIMER-------------------------------------------------------\n";
                         out<<"TOU LES AFFAIRES ONT ETE SUPPRIMER\n";

                         out<<"-----------------------------------------------------------------------------------------\n";

        ui->tableView_aff_h->setModel(ff.afficher());


        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("suppt successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("suppt failed.\n"

                      "Click Cancel to exit."), QMessageBox::Cancel);
    }










void MainWindow::on_pushButton_15_clicked()
{
    QMediaPlayer * music = new QMediaPlayer();
            music->setSource(QUrl("qrc:/rsc/rsc/imprimer.mp3"));
            music->play();

    QPrinter p;
    p.setPrinterName("af");
    QPrintDialog dialog(&p,this);
    if(dialog.exec()==QDialog::Rejected)return;
    ui->textEdit->print(&p);
    QMessageBox::information(nullptr, QObject::tr("print"),
                QObject::tr("printed succes.\n"

                  "Click Cancel to exit."), QMessageBox::Cancel);

}


void MainWindow::on_pushButton_14_clicked()
{

    QString strStream;
                     QTextStream out(&strStream);
                     QMediaPlayer * music = new QMediaPlayer();
                         music->setSource(QUrl("qrc:/rsc/rsc/pdf.mp3"));
                         music->play();
                     const int rowCount = ui->tableView_aff_h->model()->rowCount();
                     const int columnCount = ui->tableView_aff_h->model()->columnCount();

                     out <<  "<html>\n"
                         "<head>\n"
                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                         <<  QString("<title>%1</title>\n").arg("strTitle")
                         <<  "</head>\n"
                         "<body bgcolor=#ffffff link=#5000A0>\n"

                        //     "<align='right'> " << datefich << "</align>"
                         "<center> <H1>Liste des Affaires </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                     // headers
                     out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                     for (int column = 0; column < columnCount; column++)
                         if (!ui->tableView_aff_h->isColumnHidden(column))
                             out << QString("<th>%1</th>").arg(ui->tableView_aff_h->model()->headerData(column, Qt::Horizontal).toString());
                     out << "</tr></thead>\n";

                     // data table
                     for (int row = 0; row < rowCount; row++) {
                         out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                         for (int column = 0; column < columnCount; column++) {
                             if (!ui->tableView_aff_h->isColumnHidden(column)) {
                                 QString data = ui->tableView_aff_h->model()->data(ui->tableView_aff_h->model()->index(row, column)).toString().simplified();
                                 out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                             }
                         }
                         out << "</tr>\n";
                     }
                     out <<  "</table> </center>\n"
                         "</body>\n"
                         "</html>\n";

               QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                 if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                QPrinter printer (QPrinter::PrinterResolution);

printer.setOutputFormat(QPrinter::PdfFormat);
               printer.setOutputFileName(fileName);

                QTextDocument doc;
                 doc.setHtml(strStream);

                 doc.print(&printer);
/*Affaire f;
  bool test=f.pdf();
  if(test)
  {



      QMessageBox::critical(nullptr, QObject::tr("database is open"),
                  QObject::tr("pdf successful.\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);


  }
  else
      QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                  QObject::tr("pdf failed.\n"

                    "Click Cancel to exit."), QMessageBox::Cancel);*/
  }




void MainWindow::on_pushButton_Sui_m_3_clicked()
{
    QMediaPlayer * music = new QMediaPlayer();
            music->setSource(QUrl("qrc:/rsc/rsc/modifier.mp3"));
            music->play();
    int reference=ui->reference_2->text().toInt();
QString comboBox_ordre=ui->comboBox_ordre_2->currentText();
QString comboBox_type=ui->comboBox_type_2->currentText();
QString datee=ui->_date_h_2->text();
int idjuge=ui->idjuge_2->text().toInt();
int idavocat=ui->idavocat_2->text().toInt();
int  cin_p=ui->cin_p_2->text().toInt();

      int  num_salle=ui->num_salle_2->text().toInt();


      Affaire f(reference,comboBox_ordre,idjuge,comboBox_type,idavocat,cin_p,num_salle,datee);

    bool test=f.modifier();

if(test)
    {

    QTextStream out(&file);
                     out<<"---------------------------------MODIFIER------------------------------------------------\n";

                     out << " REFERENCE DE L'AFFAIRE  : " << reference <<" a éte Mmodifier avec succes \n";
                     out<<"ORDRE D'AFFAIRE : "<<comboBox_ordre<< "\n";
                     out<<"\n";
                     out<<"TYPE D'AFFAIRE : "<<comboBox_type<< "\n";
                     out<<"\n";
                     out<<"ID JUGE : "<<idjuge<< "\n \n";
                     out<<"ID AVOCAT : "<<idavocat<< "\n \n";
                     out<<"CIN DU  PERSONNE : "<<cin_p<< "\n \n";
                     out<<"NUMERO DU SALLE : "<<num_salle<< "\n \n";
                     out<< "DATE :" <<QDateTime::currentDateTime().toString()<< "\n \n";
                     out<<"ACTEUR :  GESTION DES AFFAIRES\n";
                     out<<"-----------------------------------------------------------------------------------------\n";
        ui->tableView_aff_h->setModel(ff.afficher());


        QMessageBox::critical(nullptr, QObject::tr("database is open"),
                    QObject::tr("modifie successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("modifie failed.\n"

                      "Click Cancel to exit."), QMessageBox::Cancel);
    }













void MainWindow::on_comboBox_ordre_3_currentIndexChanged(/*const QString &arg1*/)
{
    QString ordre_string=ui->comboBox_ordre_3->currentText();

    QSqlQuery *query=new QSqlQuery;
    QSqlQueryModel *model= new QSqlQueryModel();

    query->prepare("SELECT * FROM Aff ORDER BY "+ordre_string);


    query->exec();

    if (query->exec()&&query->next()) {
        model->setQuery(*query);

        ui->tableView_aff_h->setModel(model);
}
}

void MainWindow::on_pushButton_Actualise_h_clicked()
{
    QMediaPlayer * music = new QMediaPlayer();
            music->setSource(QUrl("qrc:/rsc/rsc/actualiser.mp3"));
            music->play();
    QSqlQuery *query=new QSqlQuery;
    QSqlQueryModel *model= new QSqlQueryModel();

    query->prepare("SELECT * FROM Aff ORDER BY reference ASC");


    query->exec();

    if (query->exec()&&query->next()) {
        model->setQuery(*query);

        ui->tableView_aff_h->setModel(model);
}
}

void MainWindow::on_tabWidget_currentChanged(/*int index*/)
{
    /*QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/rsc/rsc/1.mp3.mp3"));
       music->play();*/



}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{     QMediaPlayer * music = new QMediaPlayer();

    if(index ==0){
        music->setSource(QUrl("qrc:/rsc/rsc/1.mp3.mp3"));
        music->play();}  else if(index ==1){
        music->setSource (QUrl("qrc:/rsc/rsc/afficher.mp3"));
        music->play();} else if(index ==2){
        music->setSource(QUrl("qrc:/rsc/rsc/modifier.mp3"));
        music->play();} else if(index ==3){
        music->setSource(QUrl("qrc:/rsc/rsc/chercher.mp3"));
        music->play();} else if(index ==4){
        music->setSource(QUrl("qrc:/rsc/rsc/courrier.mp3"));
        music->play();}else if(index ==5){
        music->setSource(QUrl("qrc:/rsc/rsc/historique.mp3"));
        music->play();}
    }




void MainWindow::on_reference_selectionChanged()
{
    QMediaPlayer * music = new QMediaPlayer();
    music->setSource(QUrl("qrc:/rsc/rsc/Référence.mp3"));
    music->play();
}







void MainWindow::on_comboBox_ordre_activated(int index)
{
    if(index==1){
    QMediaPlayer * music = new QMediaPlayer();
    music->setSource(QUrl("qrc:/rsc/rsc/ordre juridique.mp3"));
    music->play();}else{
        QMediaPlayer * music = new QMediaPlayer();
        music->setSource(QUrl("qrc:/rsc/rsc/ordre administratif.mp3"));
        music->play();

    }
}

void MainWindow::on_comboBox_type_activated(int index)
{
    if(index==0){
    QMediaPlayer * music = new QMediaPlayer();
    music->setSource(QUrl("qrc:/rsc/rsc/type 1er degré.mp3"));
    music->play();}else if(index ==1){
        QMediaPlayer * music = new QMediaPlayer();
        music->setSource(QUrl("qrc:/rsc/rsc/type 2eme degré.mp3"));
        music->play();}else{
        QMediaPlayer * music = new QMediaPlayer();
        music->setSource(QUrl("qrc:/rsc/rsc/type Suprême.mp3"));
        music->play();
    }

    }

///////////////////********************///

void MainWindow::on_idjuge_selectionChanged()
{
    QMediaPlayer * music = new QMediaPlayer();
        music->setSource(QUrl("qrc:/rsc/rsc/identifiant du juge.mp3"));
        music->play();
}

void MainWindow::on_idavocat_selectionChanged()
{
    QMediaPlayer * music = new QMediaPlayer();
        music->setSource(QUrl("qrc:/rsc/rsc/identifiant de l'avocat.mp3"));
        music->play();
}

void MainWindow::on_cin_p_selectionChanged()
{
    QMediaPlayer * music = new QMediaPlayer();
        music->setSource(QUrl("qrc:/rsc/rsc/cin personne.mp3"));
        music->play();
}

void MainWindow::on_num_salle_selectionChanged()
{
    QMediaPlayer * music = new QMediaPlayer();
        music->setSource(QUrl("qrc:/rsc/rsc/numéro du salle.mp3"));
        music->play();
}



void MainWindow::on__date_h_editingFinished()
{
    QMediaPlayer * music = new QMediaPlayer();
        music->setSource(QUrl("qrc:/rsc/rsc/date.mp3"));
        music->play();
}

void MainWindow::on_groupBox_2_clicked()
{
    QMediaPlayer * music = new QMediaPlayer();
        music->setSource(QUrl("qrc:/rsc/rsc/description de l'état.mp3"));
        music->play();
}

void MainWindow::on_groupBox_2_clicked(bool checked)
{ if(checked){
    QMediaPlayer * music = new QMediaPlayer();
        music->setSource(QUrl("qrc:/rsc/rsc/description de l'état.mp3"));
        music->play();  }
}

void MainWindow::on_comboBox_ordre_3_activated(int index)
{    QMediaPlayer * music = new QMediaPlayer();

   /* if(index ==0){
        music->setSource(QUrl("qrc:/rsc/rsc/trier.mp3"));
        music->play();}  else if(index ==1){
        music->setSource(QUrl("qrc:/rsc/rsc/trier selon le référence descendant.mp3"));
        music->play();} else if(index ==2){
        music->setSource(QUrl("qrc:/rsc/rsc/trier selon le référence ascendant.mp3"));
        music->play();} else if(index ==3){
        music->setSource(QUrl("qrc:/rsc/rsc/trier selon l'ordre.mp3"));
        music->play();} else if(index ==4){
        music->setSource(QUrl("qrc:/rsc/rsc/trier selon le type.mp3"));
        music->play();}*/
}

void MainWindow::on_reference_2_selectionChanged()
{
    QMediaPlayer * music = new QMediaPlayer();
    music->setSource(QUrl("qrc:/rsc/rsc/Référence.mp3"));
    music->play();
}

void MainWindow::on_comboBox_ordre_2_activated(int index)
{
    if(index==1){
    QMediaPlayer * music = new QMediaPlayer();
    music->setSource(QUrl("qrc:/rsc/rsc/ordre juridique.mp3"));
    music->play();}else{
        QMediaPlayer * music = new QMediaPlayer();
        music->setSource(QUrl("qrc:/rsc/rsc/ordre administratif.mp3"));
        music->play();

    }
}



void MainWindow::on_comboBox_type_2_activated(int index)
{
    if(index==0){
    QMediaPlayer * music = new QMediaPlayer();
    music->setSource(QUrl("qrc:/rsc/rsc/type 1er degré.mp3"));
    music->play();}else if(index ==1){
        QMediaPlayer * music = new QMediaPlayer();
        music->setSource(QUrl("qrc:/rsc/rsc/type 2eme degré.mp3"));
        music->play();}else{
        QMediaPlayer * music = new QMediaPlayer();
        music->setSource(QUrl("qrc:/rsc/rsc/type Suprême.mp3"));
        music->play();
    }
}

void MainWindow::on_idjuge_2_selectionChanged()
{
    QMediaPlayer * music = new QMediaPlayer();
        music->setSource(QUrl("qrc:/rsc/rsc/identifiant du juge.mp3"));
        music->play();
}

void MainWindow::on_idavocat_2_selectionChanged()
{
    QMediaPlayer * music = new QMediaPlayer();
        music->setSource(QUrl("qrc:/rsc/rsc/identifiant de l'avocat.mp3"));
        music->play();
}

void MainWindow::on_cin_p_2_selectionChanged()
{
    QMediaPlayer * music = new QMediaPlayer();
        music->setSource(QUrl("qrc:/rsc/rsc/cin personne.mp3"));
        music->play();
}

void MainWindow::on_num_salle_2_selectionChanged()
{
    QMediaPlayer * music = new QMediaPlayer();
        music->setSource(QUrl("qrc:/rsc/rsc/numéro du salle.mp3"));
        music->play();
}

void MainWindow::on_pushButton_ajouter_2_clicked()
{
    QMediaPlayer * music = new QMediaPlayer();
        music->setSource(QUrl("qrc:/rsc/rsc/annuler.mp3"));
        music->play();
}

void MainWindow::on_pushButton_ajouter_3_clicked()
{
    QMediaPlayer * music = new QMediaPlayer();
        music->setSource(QUrl("qrc:/rsc/rsc/annuler.mp3"));
        music->play();
}

void MainWindow::on_pushButton_17_clicked()
{
    QMediaPlayer * music = new QMediaPlayer();
            music->setSource(QUrl("qrc:/rsc/rsc/description de l'état.mp3"));
            music->play();
    QString strStream;
                     QTextStream out(&strStream);
                         music->setSource(QUrl("qrc:/rsc/rsc/pdf.mp3"));
                         music->play();
                     const int rowCount = ui->tableView_aff_h_3->model()->rowCount();
                     const int columnCount = ui->tableView_aff_h_3->model()->columnCount();

                     out <<  "<html>\n"
                         "<head>\n"
                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                         <<  QString("<title>%1</title>\n").arg("strTitle")
                         <<  "</head>\n"
                         "<body bgcolor=#ffffff link=#5000A0>\n"

                        //     "<align='right'> " << datefich << "</align>"
                         "<center> <H1>Liste des Affaires </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

                     // headers
                     out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                     for (int column = 0; column < columnCount; column++)
                         if (!ui->tableView_aff_h_3->isColumnHidden(column))
                             out << QString("<th>%1</th>").arg(ui->tableView_aff_h_3->model()->headerData(column, Qt::Horizontal).toString());
                     out << "</tr></thead>\n";

                     // data table
                     for (int row = 0; row < rowCount; row++) {
                         out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                         for (int column = 0; column < columnCount; column++) {
                             if (!ui->tableView_aff_h_3->isColumnHidden(column)) {
                                 QString data = ui->tableView_aff_h_3->model()->data(ui->tableView_aff_h_3->model()->index(row, column)).toString().simplified();
                                 out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                             }
                         }
                         out << "</tr>\n";
                     }
                     out <<  "</table> </center>\n"
                         "</body>\n"
                         "</html>\n";

               QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                 if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                QPrinter printer (QPrinter::PrinterResolution);

printer.setOutputFormat(QPrinter::PdfFormat);
               printer.setOutputFileName(fileName);

                QTextDocument doc;
                 doc.setHtml(strStream);

                 doc.print(&printer);
}






void MainWindow::on_pushButton_ajouter_5_clicked()
{
    QString link="https://mail.google.com/mail/u/0/#inbox?compose=new";
    QDesktopServices::openUrl(link);

}




void MainWindow::on_supp_clicked()
{ file.close();
    if (!file.open(QIODevice::ReadWrite ))
                        QMessageBox::warning(nullptr, QObject::tr("database is open"),
                                    QObject::tr("read p .\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
    QTextStream in(&file);
    ui->textBrowser->setText(in.readAll());
}





void MainWindow::on_pushButton_clicked()
{

    QPieSeries *series = new QPieSeries();


                   QStringList list=ff.listeadresses("reference");

     ui-> tableView_aff_h->setModel(ff.afficher());
       //ui-> tableView_aff_h_2->setModel(j.afficher());
                   for (int i =0; i< list.size();i++)
                   {
                       series->append(list[i],ff.calcul_adresses(list[i],"reference"));
    ui-> tableView_aff_h->setModel(ff.afficher());

                   }
                   QPieSlice *slice = series->slices().at(5);
                   ui-> tableView_aff_h->setModel(ff.afficher());
                   slice->setLabelVisible();
                   slice->setExploded();


                  /* QtCharts::*/QChart *chart =new /*QtCharts::*/QChart();
                   chart->addSeries(series);
                   chart->setTitle("Statistiques");

                   chart->setAnimationOptions(QChart::AllAnimations);
                   QChartView *chartview=new QChartView(chart);
                   QGridLayout *mainLayout=new QGridLayout();
                   mainLayout->addWidget(chartview,0,0);
                   ui->frame->setLayout(mainLayout);

    ui-> tableView_aff_h->setModel(ff.afficher());


    /*setStyleSheet("QTableWidget {background-color: transparent;}"
                  "QHeaderView::section {background-color: transparent;}"
                  "QHeaderView {background-color: transparent;}"
                  "QTableCornerButton::section {background-color: transparent;}");*/


   // ui->tableWidget->setRowCount(4);
    //ui->tableWidget->setColumnCount(4);

    Affaire f;
QTableWidgetItem*item = new QTableWidgetItem;
QTableWidgetItem*item1 = new QTableWidgetItem;
QTableWidgetItem*item2 = new QTableWidgetItem;

QTableWidgetItem*item3 = new QTableWidgetItem;
QTableWidgetItem*item4 = new QTableWidgetItem;
QTableWidgetItem*item5 = new QTableWidgetItem;
QTableWidgetItem*item6 = new QTableWidgetItem;
QTableWidgetItem*item7 = new QTableWidgetItem;
QTableWidgetItem*item8 = new QTableWidgetItem;
QTableWidgetItem*item9 = new QTableWidgetItem;
QTableWidgetItem*item10 = new QTableWidgetItem;


int nbt=f.nbtout();

    int nbaa=f.nba();
    QString nbaaa=QString::number(nbaa);
    item->setText(nbaaa);
ui->tableWidget->setItem(-1, 2,item);

    int nbjj=f.nbj();
    QString nbjjj=QString::number(nbjj);
    item1->setText(nbjjj);
    ui->tableWidget->setItem(0, 2,item1);

    int nb11=f.nb1();
    QString nb111=QString::number(nb11);
    item2->setText(nb111);
    ui->tableWidget->setItem(1, 2,item2);

    int nb22=f.nb2();
    QString nb2=QString::number(nb22);
    item3->setText(nb2);
    ui->tableWidget->setItem(2, 2,item3);

    int nbs=f.nbs();
    QString nbss=QString::number(nbs);
    item4->setText(nbss);
    ui->tableWidget->setItem(3, 2,item4);
   //double pa=();
    QString paa=QString::number((float)nbaa*100 /nbt)+"%";
    item5->setText(paa);
        ui->tableWidget->setItem(-1, 3,item5);

        QString pjj=QString::number((float)nbjj*100 /nbt)+"%";
        item6->setText(pjj);
            ui->tableWidget->setItem(0, 3,item6);

            QString p11=QString::number((float)nb11*100 /nbt)+"%";
            item7->setText(p11);
                ui->tableWidget->setItem(1, 3,item7);

                QString p22=QString::number((float)nb22*100 /nbt)+"%";
                item8->setText(p22);
                    ui->tableWidget->setItem(2, 3,item8);

                    QString pss=QString::number((float)nbs*100 /nbt)+"%";
                    item9->setText(pss);
                        ui->tableWidget->setItem(3, 3,item9);

}
//********************************record
void MainWindow::updateProgress(qint64 duration)
{
    if (m_audioRecorder->error() != QMediaRecorder::NoError || duration < 2000)
        return;

    ui->statusbar->showMessage(tr("Recorded %1 sec").arg(duration / 1000));
}

void MainWindow::onStateChanged(QMediaRecorder::RecorderState state)
{
    QString statusMessage;

    switch (state) {
    case QMediaRecorder::RecordingState:
        statusMessage = tr("Recording to %1").arg(m_audioRecorder->actualLocation().toString());
        ui->recordButton_3->setText(tr("Stop"));
        ui->pauseButton->setText(tr("Pause"));
        break;
    case QMediaRecorder::PausedState:
        clearAudioLevels();
        statusMessage = tr("Paused");
        ui->recordButton_3->setText(tr("Stop"));
        ui->pauseButton->setText(tr("Resume"));
        break;
    case QMediaRecorder::StoppedState:
        clearAudioLevels();
        statusMessage = tr("Stopped");
        ui->recordButton_3->setText(tr("Record"));
        ui->pauseButton->setText(tr("Pause"));
        break;
    }

    ui->pauseButton->setEnabled(m_audioRecorder->recorderState() != QMediaRecorder::StoppedState);
    if (m_audioRecorder->error() == QMediaRecorder::NoError)
        ui->statusbar->showMessage(statusMessage);
}

static QVariant boxValue(const QComboBox *box)
{
    int idx = box->currentIndex();
    if (idx == -1)
        return QVariant();

    return box->itemData(idx);
}






void MainWindow::displayErrorMessage()
{
    ui->statusbar->showMessage(m_audioRecorder->errorString());
}

void MainWindow::updateFormats()
{
    if (m_updatingFormats)
        return;
    m_updatingFormats = true;

    QMediaFormat format;
    if (ui->containerBox_3->count())
        format.setFileFormat(boxValue(ui->containerBox_3).value<QMediaFormat::FileFormat>());
    if (ui->audioCodecBox_3->count())
        format.setAudioCodec(boxValue(ui->audioCodecBox_3).value<QMediaFormat::AudioCodec>());

    int currentIndex = 0;
    ui->audioCodecBox_3->clear();
    ui->audioCodecBox_3->addItem(tr("Default audio codec"), QVariant::fromValue(QMediaFormat::AudioCodec::Unspecified));
    for (auto codec : format.supportedAudioCodecs(QMediaFormat::Encode)) {
        if (codec == format.audioCodec())
            currentIndex = ui->audioCodecBox_3->count();
        ui->audioCodecBox_3->addItem(QMediaFormat::audioCodecDescription(codec), QVariant::fromValue(codec));
    }
    ui->audioCodecBox_3->setCurrentIndex(currentIndex);

    currentIndex = 0;
    ui->containerBox_3->clear();
    ui->containerBox_3->addItem(tr("Default file format"), QVariant::fromValue(QMediaFormat::UnspecifiedFormat));
    for (auto container : format.supportedFileFormats(QMediaFormat::Encode)) {
        if (container < QMediaFormat::Mpeg4Audio) // Skip video formats
            continue;
        if (container == format.fileFormat())
            currentIndex = ui->containerBox_3->count();
        ui->containerBox_3->addItem(QMediaFormat::fileFormatDescription(container), QVariant::fromValue(container));
    }
    ui->containerBox_3->setCurrentIndex(currentIndex);

    m_updatingFormats = false;
}

void MainWindow::clearAudioLevels()
{
    for (auto m_audioLevel : qAsConst(m_audioLevels))
        m_audioLevel->setLevel(0);
}

QMediaFormat MainWindow::selectedMediaFormat() const
{
    QMediaFormat format;
    format.setFileFormat(boxValue(ui->containerBox_3).value<QMediaFormat::FileFormat>());
    format.setAudioCodec(boxValue(ui->audioCodecBox_3).value<QMediaFormat::AudioCodec>());
    return format;
}

// returns the audio level for each channel
QList<qreal> getBufferLevels(const QAudioBuffer &buffer)
{
    QList<qreal> values;

    auto format = buffer.format();
    if (!format.isValid())
        return values;

    int channels = buffer.format().channelCount();
    values.fill(0, channels);

    int bytesPerSample = format.bytesPerSample();
    QList<qreal> max_values;
    max_values.fill(0, channels);

    const char *data = buffer.constData<char>();
    for (int i = 0; i < buffer.frameCount(); ++i) {
        for (int j = 0; j < channels; ++j) {
            qreal value = qAbs(format.normalizedSampleValue(data));
            if (value > max_values.at(j))
                max_values[j] = value;
            data += bytesPerSample;
        }
    }

    return max_values;
}

void MainWindow::processBuffer(const QAudioBuffer& buffer)
{
    if (m_audioLevels.count() != buffer.format().channelCount()) {
        qDeleteAll(m_audioLevels);
        m_audioLevels.clear();
        for (int i = 0; i < buffer.format().channelCount(); ++i) {
            audiolevel *level = new audiolevel(ui->centralwidget);
            m_audioLevels.append(level);
            ui->levelsLayout_3->addWidget(level);
        }
    }

    QList<qreal> levels = getBufferLevels(buffer);
    for (int i = 0; i < levels.count(); ++i)
        m_audioLevels.at(i)->setLevel(levels.at(i));
}










/*void MainWindow::on_pauseButton_toggled(bool checked)
{

    if (m_audioRecorder->recorderState() != QMediaRecorder::PausedState)
        m_audioRecorder->pause();
    else
        m_audioRecorder->record();
}*/







/*void MainWindow::on_recordButton_toggled(bool checked)
{
    if (m_audioRecorder->recorderState() == QMediaRecorder::StoppedState) {
        m_captureSession.audioInput()->setDevice(boxValue(ui->audioDeviceBox).value<QAudioDevice>());

        m_audioRecorder->setMediaFormat(selectedMediaFormat());
        m_audioRecorder->setAudioSampleRate(ui->sampleRateBox->value());
        m_audioRecorder->setAudioBitRate(boxValue(ui->bitrateBox).toInt());
        m_audioRecorder->setAudioChannelCount(boxValue(ui->channelsBox).toInt());
        m_audioRecorder->setQuality(QMediaRecorder::Quality(ui->qualitySlider->value()));
        m_audioRecorder->setEncodingMode(ui->constantQualityRadioButton->isChecked() ?
                                 QMediaRecorder::ConstantQualityEncoding :
                                 QMediaRecorder::ConstantBitRateEncoding);

        m_audioRecorder->record();
    }
    else {
        m_audioRecorder->stop();
    }
}*/










void MainWindow::on_pushButton_2_clicked()
{
    //if (m_audioRecorder->recorderState() == QMediaRecorder::PausedState)

    m_audioRecorder->record();
}


void MainWindow::on_outputButton_3_clicked()
{
#ifdef Q_OS_ANDROID
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Recording"),
                                                 "output."
                                                 + selectedMediaFormat().mimeType().preferredSuffix());
#else
    QString fileName = QFileDialog::getSaveFileName();
#endif
    m_audioRecorder->setOutputLocation(QUrl::fromLocalFile(fileName));
    m_outputLocationSet = true;
}


void MainWindow::on_recordButton_3_clicked()
{
    if (m_audioRecorder->recorderState() == QMediaRecorder::StoppedState) {
        m_captureSession.audioInput()->setDevice(boxValue(ui->audioDeviceBox_3).value<QAudioDevice>());

        m_audioRecorder->setMediaFormat(selectedMediaFormat());
        m_audioRecorder->setAudioSampleRate(ui->sampleRateBox_3->value());
        m_audioRecorder->setAudioBitRate(boxValue(ui->bitrateBox_3).toInt());
        m_audioRecorder->setAudioChannelCount(boxValue(ui->channelsBox_3).toInt());
        m_audioRecorder->setQuality(QMediaRecorder::Quality(ui->qualitySlider_3->value()));
        m_audioRecorder->setEncodingMode(ui->constantQualityRadioButton_3->isChecked() ?
                                 QMediaRecorder::ConstantQualityEncoding :
                                 QMediaRecorder::ConstantBitRateEncoding);

        m_audioRecorder->record();
    }
    else {
        m_audioRecorder->stop();
    }
}


void MainWindow::on_pauseButton_4_clicked()
{
    //if (m_audioRecorder->recorderState() != QMediaRecorder::PausedState)
    m_audioRecorder->stop();
}




