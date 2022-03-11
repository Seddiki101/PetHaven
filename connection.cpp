#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");
db.setUserName("Marmar");//inserer nom de l'utilisateur
db.setPassword("Mohamed21");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

    return  test;
}
void Connection::closeConnection()
{
    db.close();
}
