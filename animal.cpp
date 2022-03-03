#include "animal.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>


Animal::Animal()
{
    age=0;
    nom="";
    espece="";
    race="";
}

    Animal::Animal(int age, QString nom, QString espece, QString race, QDate date_arr)
    {
        this->age=age; this->nom=nom; this->espece=espece; this->race=race; this->date_arr=date_arr;
    }

    int Animal::getAge()
    {
        return age;
    }
    QString Animal::getNom()
    {
        return nom;
    }
    QString Animal::getEspece()
    {
        return espece;
    }
    QString Animal::getRace()
    {
        return race;
    }
    QDate Animal::getDate_arr()
    {
        return date_arr;
    }


void Animal::setAge(int age)                {this->age=age;}
void Animal::setNom(QString nom)            {this->nom=nom;}
void Animal::setEspece(QString espece)      {this->espece=espece;}
void Animal::setRace(QString race)          {this->race=race;}
void Animal::setDate_arr(QDate date_arr)    {this->date_arr=date_arr;}

bool Animal::ajouter()
{
    QSqlQuery query;
    QString age_string=QString::number(age);
    query.prepare("INSERT INTO animals (id_animal, age, nom, espece, race, date_arr) "
                  "VALUES (DEFAULT, :age, :nom, :espece, :race, :date_arr)");

    query.bindValue(":age", age_string);
    query.bindValue(":nom", nom);
    query.bindValue(":espece", espece);
    query.bindValue(":race", race);
    query.bindValue(":date_arr", date_arr);

    return query.exec();
}

bool Animal::supprimer(int id)
{
    QSqlQuery query;
    QString id_string=QString::number(id);

    query.prepare("DELETE FROM animals WHERE id_animal=:id");
    query.bindValue(":id", id_string);
    return query.exec();
}

QSqlQueryModel* Animal::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery ("SELECT * FROM animals");
    model->setHeaderData (0, Qt::Horizontal, QObject::tr("ID Animal"));
    model->setHeaderData (1, Qt::Horizontal, QObject::tr("Age"));
    model->setHeaderData (2, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData (3, Qt::Horizontal, QObject::tr("Espece"));
    model->setHeaderData (4, Qt::Horizontal, QObject::tr("Race"));
    model->setHeaderData (5, Qt::Horizontal, QObject::tr("Date"));

    return model;
}

