#ifndef ANIMAL_H
#define ANIMAL_H
#include <QString>
#include <QDate>
#include <QSqlQueryModel>


class Animal
{
    int age, status;
    QString nom, espece, race;
    QDate date_arr;

public:
    Animal();
    Animal(int, int, QString, QString, QString, QDate);

    int getAge();
    int getStatus();
    QString getNom();
    QString getEspece();
    QString getRace();
    QDate getDate_arr();

    void setAge (int);
    void setStatus (int);
    void setNom (QString);
    void setEspece (QString);
    void setRace (QString);
    void setDate_arr (QDate);

    QSqlQueryModel* afficher();
    bool ajouter();
    bool modifier(int id);
    bool supprimer(int id);
};


#endif // ANIMAL_H
