#include "connexion.h"

Connexion::Connexion()
{

}

bool Connexion::createconnect()
{
    bool test=false;
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("Ilyes");                //inserer nom de l'utilisateur
    db.setPassword("minouche");             //inserer mot de passe de cet utilisateur

    if (db.open())
        test=true;

    return  test;
}

void Connexion::closeconnexion()
{
    db.close();
}
