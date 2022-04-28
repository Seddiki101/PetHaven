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
    Dons(QString,QString,QString,QDate,int);

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


    bool ajouter_dons();
    QSqlQueryModel * afficher_dons();
    bool supprimer_dons(int);
    bool modifier_dons(int);
    bool Verif_email();
    bool Verif_nom();
    bool Verif_adresse();
    bool Verif_montant_z();
    bool Verif_id();
   QSqlQueryModel * Trier_dons();
   QSqlQueryModel * Trier_ID_dons();
   QSqlQueryModel * Trier_NOM_dons();
   QSqlQueryModel * rechercher_dons(QString);
   QSqlQueryModel* Total_don();
   QSqlQueryModel * afficher_capteur();
   QSqlQueryModel * afficher_capteur2();

};

#endif // DONS_H
