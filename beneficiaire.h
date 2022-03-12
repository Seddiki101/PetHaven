#ifndef BENEFICIARE_H
#define BENEFICIARE_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <string>
using namespace std;

class Beneficiaire
{



int CIN; QString name;QString lastname; int age; QString adress; QString type; int num;


public:
    Beneficiaire();
    Beneficiaire(int CIN, QString name,QString lastname, int age, QString adress, QString type, int num);
    QSqlQueryModel * afficher();
    bool ajouter();
    bool supprimer(int CIN);
    bool modifier(int CIN, QString name,QString lastname, int age, QString adress, QString type, int num);

    void setCIN(int CIN);
    void setName(QString name);
    void setLastName(QString lastname);
    void setAge(int age);
    void setAdress(QString adress);
    void setType(QString type);
    void setNum(int NUM);

    int getCIN();
    QString getName();
    QString getLastName();
    int getAge();
    QString getAdress();
    QString getType();
    int getNum();



};


#endif // BENEFICIARE_H
