#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QObject>
#include <QWidget>
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QDate>
#include <QDebug>
#include <QFile>
#include <QPdfWriter>
#include <QPainter>
#include <QMessageBox>
#include <QTextStream>
#include <QDesktopServices>
#include <QUrl>
#include <QCoreApplication>
#include <QFileDialog>
#include <QTextDocument>
#include <QPrinter>
#include <QPrintDialog>

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
    bool appreciation(int id);
    bool Verif_Email();
    QString Cryptage(QString motdepasse);
    QString Decryptage(QString motdepasse);
    QSqlQueryModel* triAlpha();
    QSqlQueryModel* triLogin();
    QSqlQueryModel* chercherID(QString recherche);
    QSqlQueryModel* chercherNom(QString recherche);
    void pdf(QTableView *tableView);



private:
    int id;
    QString nom,prenom,email,mdp,login;
    QString appreciations;
};

#endif // EMPLOYE_H
