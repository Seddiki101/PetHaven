#ifndef EMPLOYE_H
#define EMPLOYE_H


#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>

#include <QDate>
#include <QString>
#include <QTableView>

#include <QFile>
#include <QFileDialog>
#include <QTextDocument>
#include <QPrinter>
#include <QPrintDialog>
#include <QPdfWriter>


class Employe
{
public:
    Employe();
    Employe(int,QString,QString,QString,QString,QString,int,QString);

    int getid_Employe();
    QString getnom_Employe();
    QString getprenom_Employe();
    QString getemail_Employe();
    QString getmdp_Employe();
    QString getlogin_Employe();
    int getappreciations_Employe();

    void setid_Employe(int);
    void setnom_Employe(QString);
    void setprenom_Employe(QString);
    void setemail_Employe(QString);
    void setmdp_Employe(QString);
    void setlogin_Employe(QString);
    void setappreciations_Employe(int);

    QSqlQueryModel* afficher_Employe();
    QList<QVariant> appreciation_Employe(int);
    bool ajouter_Employe();
    bool supprimer_Employe(int id);
    bool modifier_Employe(int id);
    bool Verif_Email_Employe();

    QString Cryptage_Employe(QString motdepasse);
    QString Decryptage_Employe(QString motdepasse);

    QSqlQueryModel* triNom_Employe();
    QSqlQueryModel* triLogin_Employe();
    QSqlQueryModel* chercherID_Employe(QString recherche);
    QSqlQueryModel* chercherNom_Employe(QString recherche);

    void pdf_Employe(QTableView *tableView);
    bool verifyLogin(QString, QString);

private:
    int id, appreciations;
    QString nom,prenom,email,mdp,login,key_card;
};


#endif // EMPLOYE_H
