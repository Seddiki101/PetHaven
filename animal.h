#ifndef ANIMAL_H
#define ANIMAL_H

#include <QSqlQueryModel>
#include <QSqlQuery>

#include <QObject>
#include <QString>
#include <QDate>
#include <QDateTime>
#include <QTableView>

#include <QFile>
#include <QTextStream>
#include <QTextDocument>
#include <QPrinter>
#include <QPrintDialog>
#include <QPdfWriter>

#include <QDebug>


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
    bool Empty(QString);

    QSqlQueryModel* sortName();
    QSqlQueryModel* sortDates();
    QSqlQueryModel* searchID(QString);
    QSqlQueryModel* searchName(QString);

    QString historic(QString);
    void modifyRessource(QString);

    void generatePdf(QTableView*);
};


#endif // ANIMAL_H
