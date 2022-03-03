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



int CIN; QString name;QString lastname; int age; QString adress; QString type;


public:
    Beneficiaire(){
        CIN=0; name=""; lastname="";  age=0;  adress="";  type="";
    };
    Beneficiaire(int CIN, QString name,QString lastname, int age, QString adress, QString type)
    {
        this->CIN=CIN;
        this->name=name;
        this->lastname=lastname;
        this->age=age;
        this->adress=adress;
        this->type=type;
    }
    QSqlQueryModel * afficher();
    bool ajouter();
    bool supprimer(int CIN);


};


#endif // BENEFICIARE_H
