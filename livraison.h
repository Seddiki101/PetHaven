#ifndef LIVRAISON_H
#define LIVRAISON_H
#include<QString>
#include<QDateTime>
#include<QSqlQueryModel>
#include<QTableView>
#include<QPdfWriter>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>

/*
#include <QObject>
#include <QWidget>
#include <QFile>
#include <QPainter>
#include <QMessageBox>
#include <QTextStream>
#include <QDesktopServices>
#include <QUrl>
#include <QCoreApplication>
#include <QFileDialog>
*/

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

private:
    int id;
    QDateTime DateTime;
    QString adresse, adresse_dep;

};

#endif // EMPLOYE_H




