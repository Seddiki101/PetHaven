#ifndef DONS_H
#define DONS_H
#include<QString>
#include<QDate>
#include<QSqlQuery>
#include<QtDebug>
#include<QSqlQueryModel>

class Dons
{
    int id;
    QString nom_don,adresse,email;
    QDate date;
    int montant;


public:
    Dons();
    Dons(int,QString,QString,QString,QDate,int);

    int get_id();
    int get_mont();
    //QString get_type(){return type;}
    QString get_nom();
    QString get_ads();
    QString get_email();
    QDate get_date();

    void set_id(int);
    void set_mont(int);
    //void set_type(QString t){type=t;}
    void set_nom(QString);
    void set_ads(QString);
    void set_email(QString);
    void set_date(QDate);


    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();
    bool Verif_email();
    bool Verif_nom();
    bool Verif_adresse();
    bool Verif_montant_z();
    bool Verif_id();

};

#endif // DONS_H
