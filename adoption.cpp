#include "adoption.h"
#include <QString>

Adoption::Adoption(int ido,int ida,int idp,QDate dates)
{
    this->idAdoption=ido;
    this->ida=ida;
    this->idp=idp;
    this->dates=dates;
}

//affcihage




QSqlQueryModel * animal::afficher()
{
	QSqlQueryModel * model=new QSqlQueryModel();
	
model->setQuery("select * from animals where animals.status = 1")	;
//model->setHeaderData(0,Qt::Horizontal,QObject::tr("nom"));
//model->setHeaderData(1,Qt::Horizontal,QObject::tr("race"));
return model;
}



QSqlQueryModel * patient::afficher()
{
	QSqlQueryModel * model=new QSqlQueryModel();
	
model->setQuery("select * from patients")	;
//model->setHeaderData(0,Qt::Horizontal,QObject::tr("nom"));
//model->setHeaderData(1,Qt::Horizontal,QObject::tr("prenom"));

return model;
}




QSqlQueryModel * Adoption::afficher()
{
	QSqlQueryModel * model=new QSqlQueryModel();
	
model->setQuery("select animals.nom,adoption.dates,patients.Prenom from adoption,patients,animals where ( adoption.IDA = animals.IDA AND adoption.IDP = patients.IDP ) ;")	;

return model;
}



QSqlQueryModel * Adoption::triAlpha()
{
    QSqlQueryModel * model=new QSqlQueryModel();

model->setQuery("select animals.nom,adoption.dates,patients.Prenom from adoption,patients,animals where ( adoption.IDA = animals.IDA AND adoption.IDP = patients.IDP ) order by animals.nom;")	;

return model;
}



QSqlQueryModel * Adoption::triDates()
{
    QSqlQueryModel * model=new QSqlQueryModel();

model->setQuery("select animals.nom,adoption.dates,patients.Prenom from adoption,patients,animals where ( adoption.IDA = animals.IDA AND adoption.IDP = patients.IDP ) order by adoption.dates desc;")	;

return model;
}




bool Adoption::ajouter()
{
        QSqlQuery query;
        QString ida_string=QString::number(ida);
        QString idp_string=QString::number(idp);
         QString idAdoption_string=QString::number(idAdoption);



        //prepare() prend la requete en paramètre pour la préparer à l'éxécution

        query.prepare("insert into ADOPTION (IDO,IDA,IDP,DATES)"
                "values(:IDO, :IDA, :IDP, :DATES)");


        query.bindValue(":IDO",idAdoption_string);
        query.bindValue(":IDA",ida_string);
        query.bindValue(":IDP",idp_string);
        query.bindValue(":DATES",dates);


      return query.exec(); //exec() envoie la requete pour l'exécuter.
}


bool Adoption::supprimer(int ido)
{
        QSqlQuery query;
        QString id_string=QString::number(ido);
              query.prepare("DELETE FROM ADOPTION WHERE ido=:ido");
              query.bindValue(":ido", id_string);


              return query.exec();
}


QSqlQueryModel * Adoption::chercher(QString nom) //doesn
{
    QSqlQueryModel * model=new QSqlQueryModel();

model->setQuery("select animals.nom,adoption.dates,patients.Prenom from adoption,patients,animals where ( adoption.IDA = animals.IDA AND adoption.IDP = patients.IDP AND patients.prenom=:nom ) ;")	;

return model;
}




bool Adoption::modifier()
{
    QSqlQuery query;
          query.prepare("UPDATE adoption set idp=:idp,ida=:ida,dates=:dates where ido=:ido");
          query.bindValue(":idp",idp);
          query.bindValue(":ida",ida);
          query.bindValue(":dates",dates);

          return query.exec();
}
