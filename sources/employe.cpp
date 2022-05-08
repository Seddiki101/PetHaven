#include "../headers/employe.h"


Employe::Employe()
{
    id=0;
    nom="";
    prenom="";
    email="";
    mdp="";
    login="";
    appreciations=0;
    key_card="";
}


Employe::Employe(int id,QString nom ,QString prenom,QString email,QString login,QString mdp, int appreciations,QString key_card)
{
    this->id=id; this->nom=nom; this->prenom=prenom;this->email=email; this->login=login; this->mdp=mdp; this->appreciations=appreciations;
    this->key_card=key_card;
}


int Employe::getid_Employe()                                {return id;}
QString Employe::getnom_Employe()                           {return nom;}
QString Employe::getprenom_Employe()                        {return prenom;}
QString Employe::getemail_Employe()                         {return email;}
QString Employe::getmdp_Employe()                           {return mdp;}
QString Employe::getlogin_Employe()                         {return login;}
int Employe::getappreciations_Employe()                     {return appreciations;}

void Employe::setid_Employe(int id)                         {this->id=id;}
void Employe::setnom_Employe(QString nom)                   {this->nom=nom;}
void Employe::setprenom_Employe(QString prenom)             {this->prenom=prenom;}
void Employe::setemail_Employe(QString email)               {this->email=email;}
void Employe::setmdp_Employe(QString mdp)                   {this->mdp=mdp;}
void Employe::setlogin_Employe(QString login)               {this->login=login;}
void Employe::setappreciations_Employe(int appreciations)   {this->appreciations=appreciations;}

bool Employe::ajouter_Employe()
{
    QSqlQuery query;
    query.prepare("INSERT INTO employe (ide, nom, prenom,email,login,mdp,appreciations,key_card) "
                "VALUES (DEFAULT, :nom, :prenom, :email, :login, :mdp, :appreciations, :key_card)");

    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":login", login);
    mdp=Cryptage_Employe(mdp);
    query.bindValue(":mdp", mdp);
    query.bindValue(":appreciations", appreciations);
    query.bindValue(":key_card", key_card);

    return query.exec();
}

bool Employe::supprimer_Employe(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM employe WHERE ide=:ide");
    query.bindValue(":ide", id);

    return query.exec();
}

QSqlQueryModel* Employe::afficher_Employe()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("SELECT * FROM employe");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID_Employe"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Username"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Mot De Passe"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Appreciations"));
    return model;
}

bool Employe::modifier_Employe(int id)
{
    QSqlQuery query;
    query.prepare("UPDATE employe SET "
          "nom=:nom,prenom=:prenom,email=:email,login=:login,mdp=:mdp,appreciations=:appreciations "
          "WHERE IDe=:ide");
    query.bindValue(":ide",id);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":email", email);
    query.bindValue(":login", login);
    query.bindValue(":mdp", Cryptage_Employe(mdp));
    query.bindValue(":appreciations", appreciations);

    return query.exec();
}

bool Employe::Verif_Email_Employe()
{
    if (email.contains("@",Qt::CaseInsensitive)==false)
       return true;
    else
        return false;
}

QSqlQueryModel* Employe::triNom_Employe()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM employe order by employe.nom");
    return model;
}

QSqlQueryModel* Employe::triLogin_Employe()
{
    QSqlQueryModel* model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM employe order by employe.login");
    return model;
}

QSqlQueryModel* Employe::chercherID_Employe(QString recherche)
{
    QSqlQueryModel* model =new QSqlQueryModel();
    QSqlQuery query;
    if (recherche.length()!=0) {
        query.prepare("SELECT * FROM employe where ide=?");
        query.addBindValue(recherche.toInt());
        query.exec();
        model->setQuery(query);
    }
    else {
        model->setQuery("SELECT * FROM employe");
    }
    return model;
}

QSqlQueryModel* Employe::chercherNom_Employe(QString recherche)
{
    QSqlQueryModel* model =new QSqlQueryModel();
    QSqlQuery query;
    if (recherche.length()!=0) {
        query.prepare("SELECT * FROM employe where nom LIKE'"+recherche+"%'");
        query.addBindValue(recherche);
        query.exec();
        model->setQuery(query);
    }
    else {
        model->setQuery("SELECT * FROM employe");
    }
    return model;
}

void Employe::pdf_Employe(QTableView *tableView)
{
    QString header, css, text;
    const int rowCount = tableView->model()->rowCount();
    const int columnCount = tableView->model()->columnCount();

// Create the header
    header += "<html><head><meta Content='Text/html; charset=Windows-1251'>";
    header += "<title>Some epic PDF File</title>";
    header += "<link rel='stylesheet' type='text/css' href='./../Peth_Haven/ressources/table.css'>";
    header += "</head><body>";

// Some simple css in case files are too complicated to link
//    css += "<style type='text/css'>";
//    css += "table {border: solid 1px #DDEEEE;border-collapse: collapse;border-spacing: 0;font: normal 13px Arial, sans-serif;}";
//    css += "</style>";

// Create the table
    text += "<table><thead><tr>";

// Fill the table headers
    for (int column = 0; column < columnCount; column++) {
        if (!tableView->isColumnHidden(column)) {
            text += QString("<th>%1</th>").arg(tableView->model()->headerData(column, Qt::Horizontal).toString());
        }
    }
    text += "</tr></thead><tbody>";

// Fill table cells
    for (int row = 0; row < rowCount; row++) {
        text += "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!tableView->isColumnHidden(column)) {
                QString data = tableView->model()->data(tableView->model()->index(row, column)).toString().simplified();
                text += QString("<td>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        text += "</tr></tbody>";
    }
    text += "</table></body></html>";

    // Epic new HTML document, ready to be printed
    QTextDocument *document = new QTextDocument();
    document->setHtml(header + text);

    // Printing dat bad bo
    QPrinter printer;
    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete document;
}

QString Employe::Cryptage_Employe(QString motdepasse)
{
    std::string text = motdepasse.toLocal8Bit().constData();

    //int ascii;
    for(int i=0;i<(int)text.size();i++)
    {
       // ascii = motdepasse.at(i).toAscii();
       // ascii = ascii + 5 ;
       // motdepasse(i).toChar(ascii);
        text[i]=text[i]+1;

    }
    motdepasse=QString::fromStdString(text);
    return(motdepasse);
}

QString Employe::Decryptage_Employe(QString motdepasse)
{
    std::string text = motdepasse.toLocal8Bit().constData();

    //int ascii;
    for(int i=0;i<(int)text.size();i++)
    {
       // ascii = motdepasse.at(i).toAscii();
       // ascii = ascii + 5 ;
       // motdepasse(i).toChar(ascii);
        text[i]=text[i]-1;

    }
    motdepasse=QString::fromStdString(text);
    return(motdepasse);
}

QList<QVariant> Employe::appreciation_Employe(int arg)
{
    QSqlQuery query;
    query.prepare("SELECT nom,prenom FROM employe WHERE appreciations=:value");
    query.bindValue(":value", arg);
    query.exec();

    QList<QVariant> list;
    while (query.next()) {
        list.append(query.value("nom"));
        list.append(query.value("prenom"));
    }

    return list;
}

bool Employe::verifyLogin(QString login, QString mdp)
{
    QSqlQuery query;
    query.prepare("SELECT IDE FROM employe WHERE login=:login AND mdp=:mdp");
    query.bindValue(":login", login);
    query.bindValue(":mdp", mdp);

    query.exec();
    return query.first();
}
