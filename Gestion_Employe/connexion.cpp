#include "connexion.h"

Connexion::Connexion()
{

}

bool Connexion::createconnect()
{
    bool test=false;
db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");
db.setUserName("Mehdi");//inserer nom de l'utilisateur
db.setPassword("mehdi2110");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

    return  test;
}

void Connexion::closeconnexion()
{
    db.close();
}
