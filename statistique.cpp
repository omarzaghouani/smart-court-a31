#include "statistique.h"
#include "ui_statistique.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "mainwindow.h"


statistique::statistique(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistique)
{
    ui->setupUi(this);
}

statistique::~statistique()
{
    delete ui;
}
int statistique::Statistique_partie2()
{
    QSqlQuery query;
    int count=0 ;
    QSqlQuery requete("select * from CALENDRIER where mois = 'avirl'") ;
    while(requete.next())
    {
            count++ ;
    }

return count ;
}

int statistique::Statistique_partie3()
{
    QSqlQuery query;
    int count=0 ;
    QSqlQuery requete("select * from CALENDRIER where mois = 'mai'") ;
    while(requete.next())
    {
            count++ ;
    }

return count ;
}
int statistique::Statistique_partie4()
{
    QSqlQuery query;
    int count=0 ;
    QSqlQuery requete("select * from CALENDRIER where mois = 'mars'") ;
    while(requete.next())
    {
            count++ ;
    }

return count ;
}
int statistique::Statistique_partie5()
{
    QSqlQuery query;
    int count=0 ;
    QSqlQuery requete("select * from  CALENDRIER where mois = 'juillet'") ;
    while(requete.next())
    {
            count++ ;
    }

return count ;
}
int statistique::Statistique_partie6()
{
    QSqlQuery query;
    int count=0 ;
    QSqlQuery requete("select * from  CALENDRIER where mois = 'octobre'") ;
    while(requete.next())
    {
            count++ ;
    }

return count ;
}

void statistique::paintEvent(QPaintEvent *)
{

    int b=Statistique_partie2();
    cout<<b<<endl ;
    int c=Statistique_partie3();
    cout<<c<<endl ;
    int d=Statistique_partie4();
    cout<<d<<endl ;
    int e=Statistique_partie5();
    cout<<e<<endl ;
    int f=Statistique_partie6();
    cout<<f<<endl ;


        float s2= b*100 ;
        float s3=c*100;
        float s4=d*100;
        float s5=e*100;
        float s6=f*100;
        float nb = b+c+d+e+f ;
        float q2 ;
        q2 = s2/nb ;
        float q3;
        q3=s3/nb;
        float q4;
        q4=s4/nb;
        float q5;
        q5=s5/nb;
        float q6;
        q6=s6/nb;
        float y  ;
        y = (q2*360)/100 ;
        float m;
        m= (q3*360)/100;
        float p;
        p= (q4*360)/100;
        float v;
        v= (q5*360)/100;
        float w;
        w= (q6*360)/100;
    QPainter painter(this);
    QRectF size=QRectF(150,40,this->width()-600,this->width()-600);

    painter.setBrush(Qt::blue);
    painter.drawPie(size,0,16*y);
    ui->label_13->setText(" janvier") ;
    painter.setBrush(Qt::green);
    painter.drawPie(size,16*y,16*m);
     ui->label_14->setText(" fevrier") ;
    painter.setBrush(Qt::black);
    painter.drawPie(size,16*(m+y),16*p);
     ui->label_10->setText(" mars") ;
    painter.setBrush(Qt::yellow);
    painter.drawPie(size,16*(m+y+p),16*v);
     ui->label_9->setText(" mai") ;
    painter.setBrush(Qt::red);
    painter.drawPie(size,16*(m+y+p+v),16*w);
     ui->label_7->setText(" avril") ;
    std::string stat_text("33,33%");


   /* QStaticText bleu(stat_text.c_str());
    painter.drawStaticText(80,150,bleu);

    std::string stat_text2("33,33%");
    QStaticText red(stat_text2.c_str());
    painter.drawStaticText(400,100,red);

    std::string stat_text3("33.33%");
    QStaticText green(stat_text3.c_str());
    painter.drawStaticText(250,300,green);*/


}
