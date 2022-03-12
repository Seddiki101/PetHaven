#include "livraison.h"
#include <QSqlQuery>
#include<QtDebug>
#include <QObject>

Livraison::Livraison()
{
    adresse="";
    adresse_dep="";
}


Livraison::Livraison(QDate date, QString adresse ,QString adresse_dep)
{
    this->date=date; this->adresse=adresse; this->adresse_dep=adresse_dep;
}


void Livraison::setadresse(QString adresse){this->adresse=adresse;}
void Livraison::setadresse_dep(QString adresse_dep){this->adresse_dep=adresse_dep;}
void Livraison::setdate(QDate date){this->date=date;}

bool Livraison::ajouter()
{

    QSqlQuery query;
    QString id_string=QString::number(id);
    query.prepare("INSERT INTO livraison (idl, datel, adresse, adresse_dep) "
                  "VALUES (DEFAULT, :datel, :adresse, :adresse_dep)");
    query.bindValue(":datel", date);
    query.bindValue(":adresse", adresse);
    query.bindValue(":adresse_dep", adresse_dep);


    return query.exec();
}

bool Livraison::modifier(int id)
{
    QSqlQuery query;
    QString id_string=QString::number(id);
    query.prepare("UPDATE livraison SET "
                  "datel=:datel, adresse=:adresse, adresse_dep=:adresse_dep "
                  "WHERE idl=:idl");

    query.bindValue(":idl", id_string);
    query.bindValue(":datel", date);
    query.bindValue(":adresse", adresse);
    query.bindValue(":adresse_dep", adresse_dep);

    return query.exec();
}

bool Livraison::supprimer(int id)
{
    QSqlQuery query;
    QString id_string=QString::number(id);
    query.prepare("DELETE FROM livraison WHERE idl=:idl");
    query.bindValue(":idl", id);


    return query.exec();
}

QSqlQueryModel* Livraison::afficher()
{
    QSqlQueryModel* model =new QSqlQueryModel();

    model->setQuery("SELECT * FROM livraison");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_Livraison"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse_dep"));


    return model;
}

