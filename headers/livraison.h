#ifndef LIVRAISON_H
#define LIVRAISON_H


#include <QApplication>
#include <QString>
#include <QDateTime>
#include <QSqlQueryModel>
#include <QTableView>

#include <QSqlQuery>
#include <QObject>

#include <QPdfWriter>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QTextStream>

#include <QGeoAddress>
#include <QGeoCoordinate>
#include <QGeoLocation>
#include <QGeoCodingManager>
#include <QGeoServiceProvider>
#include <QDebug>

using namespace std;


class Livraison
{
public:
    Livraison();
    Livraison(QDateTime,QString,QString);
    QDateTime getDateTime(){return DateTime;};
    QString getadresse(){return adresse;};
    QString getadresse_dep(){return adresse_dep;};


    void setDateTime(QDateTime);
    void setadresse(QString);
    void setadresse_dep(QString);


    bool ajouter();
    bool controlAD();
    bool controlA();
    QSqlQueryModel* afficher();
    QSqlQueryModel* triAlpha();
    QSqlQueryModel* triDate();
    QSqlQueryModel* chercher(QString recherche);
    QSqlQueryModel* search(QString recherche);
    void generatePdf(QTableView *);
    bool modifier(int id);
    bool supprimer(int id);

    QList<QVariant> fetchDates();

private:
    int id;
    QDateTime DateTime;
    QString adresse, adresse_dep;

};

#endif // LIVRAISON_H




