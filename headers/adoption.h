#ifndef ADOPTION_H
#define ADOPTION_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QDate>
#include <QFile>
#include <QPdfWriter>
#include <QPainter>
#include <QMessageBox>
#include <QTextStream>
#include <QDesktopServices>
#include <QUrl>
#include <QCoreApplication>
#include <QFileDialog>
#include <QTextDocument>
#include <QPrinter>
#include <QPrintDialog>

#include "qrcodegen.h"

using std::uint8_t;
using qrcodegen::QrCode;
using qrcodegen::QrSegment;

class Adoption
{
public:

    QSqlQueryModel * affichAdo();
    QSqlQueryModel * affichAnimals();
    QSqlQueryModel * affichBeneficiaires();
    Adoption(){};
    Adoption(int,int,int, QDate);
    bool ajoutAdo();
    bool supprimAdo(int, int, int);
    QSqlQueryModel * triAlphAdo();
    QSqlQueryModel * triDatesAdo();
    QSqlQueryModel * Totado();
    QSqlQueryModel * chercherAdo(QString);  //recherche par ID
    QSqlQueryModel * searchAdo(QString);    // recherche par nom
    bool modifierAdo(int,int,int);
    void generatePdf(QTableView *tableView);
    void genereExcel(QTableView *table);

private:
int ido;
int ida;
int idp;
int idAdoption;
QDate dates;
};

//animal and patient are only for testing
class animal
{
public:

    QSqlQueryModel * afficher();

int age;
};

class beneficiaire
{
public:

    QSqlQueryModel * afficher();

int age;
};











//advance
static void dosicDemo(char * text);
static std::string toSvgString(const QrCode &qr, int border);
static void printQr(const QrCode &qr);



#endif // ADOPTION_H
