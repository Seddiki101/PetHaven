#include "employe.h"
#include <QSqlQuery>
#include<QtDebug>
#include <QObject>

Employe::Employe()
{
    id=0;
    nom="";
    prenom="";
    email="";
    mdp="";
    login="";
  }


    Employe::Employe(int id,QString nom ,QString prenom,QString email,QString login,QString mdp)
    {
    this->id=id; this->nom=nom; this->prenom=prenom;this->email=email; this->login=login; this->mdp=mdp;
    }


        int Employe::getid()
        {
            return id;
        }


        QString Employe::getnom()
        {
            return nom;
        }

        QString Employe::getprenom()
        {
            return prenom ;
        }

        QString Employe::getemail()
        {
            return email ;
        }


        QString Employe::getmdp()
        {
            return mdp;
        }

        QString Employe::getlogin()
        {
            return login;
        }

    void Employe::setid(int id){this->id=id;}
    void Employe::setnom(QString nom){this->nom=nom;}
    void Employe::setprenom(QString prenom){this->prenom=prenom;}
    void Employe::setemail(QString email){this->email=email;}
    void Employe::setmdp(QString mdp){this->mdp=mdp;}
    void Employe::setlogin(QString login){this->login=login;}
    bool Employe::ajouter()
    {

        QSqlQuery query;
        QString id_string=QString::number(id);
              query.prepare("INSERT INTO employe (ide, nom, prenom,email,login,mdp) "
                            "VALUES (DEFAULT, :nom, :prenom, :email, :login, :mdp)");
              //query.bindValue(":id", id_string);
              query.bindValue(":nom", nom);
              query.bindValue(":prenom", prenom);
              query.bindValue(":email", email);
              query.bindValue(":login", login);
              query.bindValue(":mdp", mdp);

              return query.exec();
    }

bool Employe::supprimer(int id)
    {
    QSqlQuery query;
    QString id_string=QString::number(id);
          query.prepare("DELETE FROM employe WHERE ide=:ide");
          query.bindValue(":ide", id);


          return query.exec();
    }

QSqlQueryModel* Employe::afficher()
{
  QSqlQueryModel* model =new QSqlQueryModel();

  model->setQuery("SELECT * FROM employe");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_Employe"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("Username"));
  model->setHeaderData(5, Qt::Horizontal, QObject::tr("Mot De Passe"));

return model;
}

bool Employe::modifier(int id)
{
    QSqlQuery query;
    QString id_string=QString::number(id);

//    QString status_string=QString::number(status);
          query.prepare("UPDATE employe SET "
                  "  nom=:nom,prenom=:prenom,email=:email,login=:login,mdp=:mdp "
                  "WHERE IDe=:ide");
          query.bindValue(":ide",id_string);
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":email", email);
          query.bindValue(":login", login);
          query.bindValue(":mdp", mdp);

          return query.exec();
}

bool Employe::Verif_Email()
{
    if (email.contains("@",Qt::CaseInsensitive)==false)
       return true;
    else return false;
}

