#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ui_mainwindow.h"
#include"arduino.h"
#include <QMainWindow>

#include <QtWidgets/qmainwindow.h>
#include <QMediaRecorder>
#include <QMediaCaptureSession>
#include <QUrl>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>

#include <QtTextToSpeech>
#include <QMessageBox>
#include<QtCharts>
#include"affaire.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QAudioBuffer;

QT_END_NAMESPACE
class audiolevel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
  ~MainWindow();
public slots:
    void speak();
    void stop();
 void voice_afficher();
    void setRate(int);
    void setPitch(int);
    void setVolume(int volume);

    void stateChanged(QTextToSpeech::State state);
    void engineSelected(int index);
    void languageSelected(int language);
    void voiceSelected(int index);

    void localeChanged(const QLocale &locale);

    void processBuffer(const QAudioBuffer&);
private slots:
    void on_pushButton_ajouter_clicked();

    void on_pushButton_Sui_m_clicked();

    void on_chercher_2_clicked();

    void on_pushButton_Sui_m_2_clicked();





    void on_pushButton_15_clicked();


    void on_pushButton_14_clicked();

    void on_pushButton_Sui_m_3_clicked();





    void on_comboBox_ordre_3_currentIndexChanged(/*const QString &arg1*/);

    void on_pushButton_Actualise_h_clicked();

    void on_tabWidget_currentChanged(/*int index*/);

    void on_tabWidget_tabBarClicked(int index);




    void on_reference_selectionChanged();




    void on_comboBox_ordre_activated(int index);

    void on_comboBox_type_activated(int index);

    void on_idjuge_selectionChanged();

    void on_idavocat_selectionChanged();

    void on_cin_p_selectionChanged();

    void on_num_salle_selectionChanged();



    void on__date_h_editingFinished();

    void on_groupBox_2_clicked();

    void on_groupBox_2_clicked(bool checked);

    void on_comboBox_ordre_3_activated(int index);

    void on_reference_2_selectionChanged();

    void on_comboBox_ordre_2_activated(int index);


    void on_comboBox_type_2_activated(int index);

    void on_idjuge_2_selectionChanged();

    void on_idavocat_2_selectionChanged();

    void on_cin_p_2_selectionChanged();

    void on_num_salle_2_selectionChanged();

    void on_pushButton_ajouter_2_clicked();

    void on_pushButton_ajouter_3_clicked();

    void on_pushButton_17_clicked();



    void on_pushButton_ajouter_5_clicked();


    void on_supp_clicked();
    void on_pushButton_clicked();


    ////record

    void onStateChanged(QMediaRecorder::RecorderState);
    void updateProgress(qint64 pos);
    void displayErrorMessage();

    void updateFormats();







    //void on_recordButton_toggled(bool checked);


    //void on_pauseButton_toggled(bool checked);


    //void on_pushButton_clicked();


    void on_pushButton_2_clicked();

    void on_outputButton_3_clicked();

    void on_recordButton_3_clicked();

    void on_pauseButton_4_clicked();


private:
    Ui::MainWindow *ui;
    QTextToSpeech *m_speech;
    QList<QVoice> m_voices;
    Affaire ff;
    QFile file;
    QByteArray data; // variable contenant les données reçues

    arduino A; // objet temporaire
    void clearAudioLevels();
    QMediaFormat selectedMediaFormat() const;
    QMediaCaptureSession m_captureSession;
    QMediaRecorder *m_audioRecorder = nullptr;
    QList<audiolevel*> m_audioLevels;
    bool m_outputLocationSet = false;
    bool m_updatingFormats = false;
};
#endif // MAINWINDOW_H
