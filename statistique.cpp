#include "statistique.h"
#include "ui_statistique.h"
#include "ui_mainwindow.h"
#include<iostream>
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
    QSqlQuery requete("select * from BENEFICIAIRES where AGE >18") ;
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
    QSqlQuery requete("select * from BENEFICIAIRES where AGE  <18") ;
    while(requete.next())
    {
            count++ ;
    }

return count ;
}


void statistique::paintEvent(QPaintEvent *)
{

    int b=Statistique_partie2(); //count occurences param1
    cout<<b<<endl ;
    int c=Statistique_partie3();//count occurences param2
    cout<<c<<endl ;

        float s2= b*100 ;
        float s3=c*100;
        float nb = b+c ; //number of all occurences
        float q2 ;
        q2 = s2/nb ; //param1 %
        float q3;
        q3=s3/nb; //param2 %
        float y  ;
        y = (q2*360)/100 ; //param1 on pie
        float m; //param2 on pie
        m= (q3*360)/100;
    QPainter painter(this);
    QRectF size=QRectF(350,150,this->width()-700,this->width()-700); //canvas geometry config

    painter.setBrush(Qt::blue); //color1
    painter.setBrush(Qt::red); //color2
    painter.drawPie(size,0,16*y); //draw pie slice param1 from origin
    painter.drawPie(size,16*y,16*m); //draw pie slice param2 starting where param1 ends
    ui->label_2->setText("+18") ;
    ui->label_4->setText("-18") ;
    ui->label_3->setNum(q2) ;
    ui->label_6->setNum(q3) ;


}

