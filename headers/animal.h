#ifndef ANIMAL_H
#define ANIMAL_H

#include <QSqlQuery>
#include <QSqlTableModel>
#include <QStyledItemDelegate>
#include <QPainter>

#include <QString>
#include <QDate>
#include <QDateTime>
#include <QTableView>
#include <QtWidgets>

#include <QFile>
#include <QFileDialog>
#include <QTextDocument>
#include <QPrinter>
#include <QPrintDialog>
#include <QPdfWriter>

#include <QDebug>


class CustomModel : public QSqlTableModel
{
protected:
    QVariant data(const QModelIndex &idx, int role = Qt::DisplayRole) const override;
};

class CustomStyle : public QStyledItemDelegate
{
protected:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};


class Animal
{

private:
    int age, status;
    QString nom, espece, race;
    QDate date_arr;

public:

    Animal();
    Animal(int, int, QString, QString, QString, QDate);

    // The army of getters even though probably none of them will ever be used
    int getAge();
    int getStatus();
    QString getNom();
    QString getEspece();
    QString getRace();
    QDate getDate_arr();

    // The army of setters even though probably none of them will ever be used
    void setAge (int);
    void setStatus (int);
    void setNom (QString);
    void setEspece (QString);
    void setRace (QString);
    void setDate_arr (QDate);

    void afficher (QTableView*);                // Show the data from the database
    bool ajouter ();                            // Add some stuff to the database
    bool modifier (int);                        // Modify some stuff, will probably be deprecated, Edit() is technically more practical
    bool supprimer (int);                       // Delete some stuff from the database. Cool function, deleting stuff is amusing
    bool isEmpty (QString);                     // Test if a string is empty even though QString::isNull() already exists

    QSqlTableModel* sortData (QString = "", int = -1, Qt::SortOrder = Qt::AscendingOrder);  // Epic function to sort data, works like a query constructor for SELECT, WHERE, LIKE etc.
    QString historic (QString);                                                             // Print in the current session and on a text file changes made during the execution of the application
    bool updateImage (int, QString);                                                        // Upload an image to the databse from the pc
    void generatePdf (QTableView*);                                                         // Generates a PDF file through HTML

    QString QueryConstructor (QString, QString, QString = "", QString = "");                // Used to construct some queries, kinda useless ngl
    bool Edit (int, QString, QString = "", int = -1, QDate = QDate::currentDate());         // Construct some Edit query to edit one element of the database at once
    void setWidgets (QTableView *table);
};


#endif // ANIMAL_H
