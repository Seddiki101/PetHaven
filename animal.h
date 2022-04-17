#ifndef ANIMAL_H
#define ANIMAL_H


#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>

#include <QObject>
#include <QString>
#include <QDate>
#include <QDateTime>
#include <QTableView>
#include <QtWidgets>

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QTextDocument>
#include <QPrinter>
#include <QPrintDialog>
#include <QPdfWriter>

#include <QDebug>



class Animal
{

protected:
    int age, status, imageID;
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
    void setImage(int); // Simply sets an int corresponding to an image's ID

    QSqlTableModel* afficher();
    bool ajouter();
    bool modifier(int);
    bool supprimer(int);
    bool isEmpty(QString);

    QSqlTableModel* sortData(QString = "", int = -1, Qt::SortOrder = Qt::AscendingOrder);
    QString historic(QString);
    bool addImage(QString, QString);
    bool updateImage(int, QString, QString);

    void generatePdf(QTableView*);
};

class AnimalEdit : public Animal
{

public:
    // Used to construct some queries, kinda useless ngl
    QString QueryConstructor(QString, QString, QString = "", QString = "");
    // Construct some Edit query to edit one element of the database at once
    bool Edit(int, QString, QString = "", int = -1, QDate = QDate::currentDate());

};


#endif // ANIMAL_H
