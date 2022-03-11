#ifndef CONNEXION_H
#define CONNEXION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>


class Connexion
{
    QSqlDatabase db;
public:
    Connexion();
      bool createconnect();
      void closeconnexion();
};

#endif // CONNEXION_H
