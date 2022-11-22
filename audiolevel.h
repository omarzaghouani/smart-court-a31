#ifndef AUDIOLEVEL_H
#define AUDIOLEVEL_H


#include<QWidget>
class audiolevel:public QWidget
{
    Q_OBJECT
public:
    explicit audiolevel(QWidget *parent = 0);

    // Using [0; 1.0] range
    void setLevel(qreal level);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    qreal m_level = 0.0;
};

#endif // AUDIOLEVEL_H
