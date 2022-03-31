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
#include "qrcodegen.hpp"

using std::uint8_t;
using qrcodegen::QrCode;
using qrcodegen::QrSegment;

class Adoption
{
public:

    QSqlQueryModel * afficher();
    Adoption(){};
    Adoption(int ido,int ida,int idp,QDate dates);
    bool ajouter();
    bool supprimer(int ido);
    QSqlQueryModel * triAlpha();
    QSqlQueryModel * triDates();
    QSqlQueryModel * chercher(QString);  //recherche par ID
    QSqlQueryModel * search(QString);    // recherche par nom
    bool modifier(int,int,int);
    void generatePdf(QTableView *tableView);
    void genereExcel(QTableView *table);

private:
int ido;
int ida;
int idp;
int idAdoption;
QDate dates;
};

class animal
{
public:

    QSqlQueryModel * afficher();

int age;
};

class patient
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
