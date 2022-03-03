#ifndef ANIMAL_H
#define ANIMAL_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>


class Animal
{
    int age;
    QString nom, espece, race;
    QDate date_arr;

public:
    Animal();
    Animal(int, QString, QString, QString, QDate);

    int getAge();
    QString getNom();
    QString getEspece();
    QString getRace();
    QDate getDate_arr();

    void setAge (int);
    void setNom (QString);
    void setEspece (QString);
    void setRace (QString);
    void setDate_arr (QDate);

    QSqlQueryModel* afficher();
    bool ajouter();
    bool supprimer(int id);
};


#endif // ANIMAL_H
