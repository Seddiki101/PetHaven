#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;

     //if odbc works for you
db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Project");
db.setUserName("seddiki");//inserer nom de l'utilisateur
db.setPassword("1212");//inserer mot de passe de cet utilisateur

   //if no working odbc
//db = QSqlDatabase::addDatabase("QSQLITE");
//db.setDatabaseName("C:/SQL/DB1/peto.db");

if (db.open())
test=true;





    return  test;
}


void Connection::closeconnect()
{
db.close();
}
