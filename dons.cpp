#include "dons.h"

Dons::Dons()
{
    //id=0;
    nom_don="";adresse="";email="";montant=0;
}
Dons::Dons(QString nom_don,QString adresse,QString email,QDate date,int montant)
{
//this->id=id;
//this->type=type;
this->nom_don=nom_don;
this->adresse=adresse;
this->email=email;
this->date=date;
this->montant=montant;
}

int Dons::get_id(){return id;}
int Dons::get_mont(){return montant;}
//QString get_type(){return type;}
QString Dons::get_nom(){return nom_don;}
QString Dons::get_ads(){return adresse;}
QString Dons::get_email(){return email;}
QDate Dons::get_date(){return date;}

void Dons::set_id(int i){id=i;}
void Dons::set_mont(int m){montant=m;}
//void set_type(QString t){type=t;}
void Dons::set_nom(QString n){nom_don=n;}
void Dons::set_ads(QString a){adresse=a;}
void Dons::set_email(QString ma){email=ma;}
void Dons::set_date(QDate d){date=d;}

bool Dons::ajouter()
{
   QSqlQuery Query;
   //QString res= QString::number(id);
   Query.prepare("INSERT INTO DONS (id,nom_don,adresse,email,date_don,montant)" "values(DEFAULT,:nom_don,:adresse,:email,:date_don,:montant)");
  //Query.bindValue(0,res);
   Query.bindValue(":nom_don",nom_don);
   //Query.bindValue(":type",type);
   Query.bindValue(":adresse",adresse);
   Query.bindValue(":email",email);
   Query.bindValue(":date_don",date);
   Query.bindValue(":montant",montant);

   return Query.exec();
}

bool Dons::supprimer(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("DELETE FROM DONS WHERE id=:id");
    query.bindValue(":id",id);
    return query.exec();
}
QSqlQueryModel * Dons::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM DONS");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Email"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Montant"));
    return model;
}
bool Dons::modifier(int id)
{
    QSqlQuery query;
       QString res=QString::number(id);
//query.bindValue(0,res);
          query.prepare("UPDATE DONS set nom_don=?,ADRESSE=?,EMAIL=?,DATE_DON=?,MONTANT=? where id=:id");

          query.addBindValue(nom_don);
          //Query.bindValue(":type",type);
          query.addBindValue(adresse);
          query.addBindValue(email);
          query.addBindValue(date);
          query.addBindValue(montant);
          query.addBindValue(res);

          return query.exec();
}
bool Dons::Verif_email()
{
    if (email.contains("@",Qt::CaseInsensitive)==false)
       return true;
    else return false;
}
bool Dons::Verif_nom()
{
    if (nom_don.isEmpty())
    return true;
    else return false;
}
bool Dons::Verif_adresse()
{
    if(adresse.isEmpty())
        return true;
    else return false;
}
bool Dons::Verif_montant_z()
{
    if(montant == 0)
        return true;
    else return false;
}
bool Dons::Verif_id()
{
    if(id==0)
        return true;
    else return false;
}

QSqlQueryModel * Dons::Trier()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM DONS ORDER BY MONTANT DESC");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Email"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Montant"));
    return model;
}

QSqlQueryModel * Dons::Trier_ID()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM DONS ORDER BY ID DESC");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Email"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Montant"));
    return model;
}

QSqlQueryModel * Dons::Trier_NOM()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM DONS ORDER BY NOM_DON ASC ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Email"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Montant"));
    return model;
}

QSqlQueryModel* Dons::rechercher(QString recherche)
{
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT * FROM DONS where ID LIKE '"+recherche+"%' OR NOM_DON LIKE '"+recherche+"%'  OR LOWER(NOM_DON) LIKE '"+recherche+"%'");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Adresse"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Email"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Date"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Montant"));
    return model;





}
QSqlQueryModel* Dons::Total_don()
{
    QSqlQuery query;
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT SUM(MONTANT)as SOMME FROM DONS");

    return model;
}
