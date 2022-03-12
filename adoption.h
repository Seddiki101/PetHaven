#ifndef ADOPTION_H
#define ADOPTION_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

class Adoption
{
public:

    QSqlQueryModel * afficher();
    Adoption(){};
    Adoption(int ido,int ida,int idp,QDate dates);
    bool ajouter();
    bool supprimer(int ido);
    QSqlQueryModel * triAlpha();
    QSqlQueryModel * triDates();
    QSqlQueryModel * chercher(QString nom);
    bool modifier();

private:

int ida;
int idp;
int idAdoption;
QDate dates;
};

class animal
{
public:

    QSqlQueryModel * afficher();

int age;
};

class patient
{
public:

    QSqlQueryModel * afficher();

int age;
};

#endif // ADOPTION_H
