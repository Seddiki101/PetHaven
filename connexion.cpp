#include "connexion.h"


Connexion::Connexion()
{

}

bool Connexion::createconnect()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName ( "Source_Projet2A" );      // the name should be the same for everyone
    db.setUserName ( "Ilyes" );                    // insert the username of the databse connexion
    db.setPassword ( "minouche" );                 // and its password

    if (db.open()) {
        return true;
    }

    return false;
}

void Connexion::closeconnexion()
{
    db.close();
}
