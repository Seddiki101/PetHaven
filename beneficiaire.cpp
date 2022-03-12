#include "beneficiaire.h"
//#include "mainwindow.h"
#include <QDebug>

Beneficiaire::Beneficiaire(){
    CIN=0; name=""; lastname="";  age=0;  adress="";  type=""; num=0;
};
Beneficiaire::Beneficiaire(int CIN, QString name,QString lastname, int age, QString adress, QString type, int num)
{
    this->CIN=CIN;
    this->name=name;
    this->lastname=lastname;
    this->age=age;
    this->adress=adress;
    this->type=type;
    this->num=num;
}


void Beneficiaire::setCIN(int cin)
{
    CIN=cin;
}
void Beneficiaire::setName(QString NAME)
{
    name=NAME;
}
void Beneficiaire::setLastName(QString LASTNAME)
{
    lastname=LASTNAME;
}
void Beneficiaire::setAge(int AGE)
{
    age=AGE;
}
void Beneficiaire::setAdress(QString ADRESS)
{
    adress=ADRESS;
}
void Beneficiaire::setType(QString TYPE)
{
    type=TYPE;
}

void Beneficiaire::setNum(int NUM)
{
    type=NUM;
}

int Beneficiaire::getCIN(){return CIN;}
QString Beneficiaire::getName(){return name;}
QString Beneficiaire::getLastName(){return lastname;}
int Beneficiaire::getAge(){return age;}
QString Beneficiaire::getAdress(){return adress;}
QString Beneficiaire::getType(){return type;}
int Beneficiaire::getNum(){return num;}

//affcihage

QSqlQueryModel * Beneficiaire::afficher()
{
	QSqlQueryModel * model=new QSqlQueryModel();
	
model->setQuery("select * from BENEFICIAIRES")	;
model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("AGE"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("ADRESSE"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("TYPE"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("NUM"));
return model;
}


bool Beneficiaire::ajouter()
{
        QSqlQuery query;
        QString CIN_string=QString::number(CIN);
        QString age_string=QString::number(age);
        QString num_string=QString::number(num);



        //prepare() prend la requete en paramètre pour la préparer à l'éxécution

        query.prepare("insert into BENEFICIAIRES (CIN,NOM,PRENOM,AGE,ADRESSE,TYPE,NUM) values (:CIN, :name, :lastname, :age, :adress, :type, :num)");


        query.bindValue(":CIN",CIN_string);
        query.bindValue(":age",age_string);
        query.bindValue(":name",name);
        query.bindValue(":lastname",lastname);
        query.bindValue(":adress",adress);
        query.bindValue(":type",type);
        query.bindValue(":num",num_string);

        //qDebug() << "Name value : " << name;

      return query.exec(); //exec() envoie la requete pour l'exécuter.
}


bool Beneficiaire::supprimer(int CIN)
{




        QSqlQuery query;
        QString CIN_string=QString::number(CIN);
              query.prepare("DELETE FROM BENEFICIAIRES WHERE CIN=:CIN");
              query.bindValue(":CIN", CIN_string);


              return query.exec();
}

bool Beneficiaire::modifier( int CIN, QString name,QString lastname, int age, QString adresse, QString type, int num)
{
    QSqlQuery query;
    //QString OLDCIN_string=QString::number(OLDCIN);
     //QString CIN_string=QString::number(CIN);
     //QString age_string=QString::number(age);
     //QString num_string=QString::number(num);

          query.prepare("UPDATE beneficiaires set age=:age, nom=:name, prenom=:lastname, adresse=:adresse, type=:type, num=:num where CIN=:CIN");


          query.bindValue(":CIN",CIN);
          query.bindValue(":age",age);
          query.bindValue(":name",name);
          query.bindValue(":lastname",lastname);
          query.bindValue(":adresse",adresse);
          query.bindValue(":type",type);
         query.bindValue(":num",num);

          return query.exec();
}
