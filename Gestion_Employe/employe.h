#ifndef EMPLOYE_H
#define EMPLOYE_H
#include<QString>
#include<QSqlQueryModel>

class Employe
{
public:
    Employe();
    Employe(int,QString,QString,QString,QString,QString);
    int getid();
    QString getnom();
    QString getprenom();
    QString getemail();
    QString getmdp();
    QString getlogin();
    void setid(int);
    void setnom(QString);
    void setprenom(QString);
    void setemail(QString);
    void setmdp(QString);
    void setlogin(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id);
    bool modifier(int id);
    bool Verif_Email();

private:
    int id;
    QString nom,prenom,email,mdp,login;
};

#endif // EMPLOYE_H
