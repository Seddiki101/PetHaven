#ifndef BENEFICIARE_H
#define BENEFICIARE_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QDate>
#include <string>
#include <QTableView>
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
#include <QDateTime>
#include <string>
#include <algorithm>
#include <cctype>


using namespace std;

class Beneficiaire
{



int CIN; QString name;QString lastname; int age; QString adress; QString type; int num; QDateTime date;


public:
    Beneficiaire();
    Beneficiaire(int CIN, QString name,QString lastname, int age, QString adress, QString type, int num, QDateTime date);
    QSqlQueryModel * afficher(QString search, int tri);
    bool ajouter();
    bool supprimer(int CIN);
    bool modifier(int CIN, QString name,QString lastname, int age, QString adress, QString type, int num);
    void exportPDF(QTableView * tableView);
    void log(int x,QString username);

    void setCIN(int CIN);
    void setName(QString NAME);
    void setLastName(QString LASTNAME);
    void setAge(int AGE);
    void setAdress(QString ADRESS);
    void setType(QString TYPE);
    void setNum(int NUM);
    void setDate(QDateTime DATE);

    int getCIN();
    QString getName();
    QString getLastName();
    int getAge();
    QString getAdress();
    QString getType();
    int getNum();
    QDateTime getDate();
bool is_number(const std::string& s);
bool has_any_digits(const std::string& s);


};


#endif // BENEFICIARE_H
