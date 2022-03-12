#ifndef LIVRAISON_H
#define LIVRAISON_H
#include<QString>
#include<QDate>
#include<QSqlQueryModel>

class Livraison
{
public:
    Livraison();
    Livraison(QDate,QString,QString);
    QDate getdate(){return date;};
    QString getadresse(){return adresse;};
    QString getadresse_dep(){return adresse_dep;};


    void setdate(QDate);
    void setadresse(QString);
    void setadresse_dep(QString);


    bool ajouter();
    QSqlQueryModel* afficher();
    bool modifier(int id);
    bool supprimer(int id);

private:
    int id;
    QDate date;
    QString adresse, adresse_dep;

};

#endif // EMPLOYE_H




