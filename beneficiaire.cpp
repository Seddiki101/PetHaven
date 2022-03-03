#include "beneficiaire.h"
#include <QDebug>



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
return model;
}


bool Beneficiaire::ajouter()
{
        QSqlQuery query;
        QString CIN_string=QString::number(CIN);
        QString age_string=QString::number(age);



        //prepare() prend la requete en paramètre pour la préparer à l'éxécution

        query.prepare("insert into BENEFICIAIRES (CIN,NOM,PRENOM,AGE,ADRESSE,TYPE) values (:CIN, :name, :lastname, :age, :adress, :type)");


        query.bindValue(":CIN",CIN_string);
        query.bindValue(":age",age_string);
        query.bindValue(":name",name);
        query.bindValue(":lastname",lastname);
        query.bindValue(":adress",adress);
        query.bindValue(":type",type);

        qDebug() << "Name value : " << name;

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
