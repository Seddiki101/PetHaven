#include "../headers/livraison.h"

using namespace std;

Livraison::Livraison()
{
    adresse="";
    adresse_dep="";
}


Livraison::Livraison(QDateTime DateTime, QString adresse ,QString adresse_dep)
{
    this->DateTime=DateTime; this->adresse=adresse; this->adresse_dep=adresse_dep;
}


void Livraison::setadresse(QString adresse){this->adresse=adresse;}
void Livraison::setadresse_dep(QString adresse_dep){this->adresse_dep=adresse_dep;}
void Livraison::setDateTime(QDateTime DateTime){this->DateTime=DateTime;}

bool Livraison::ajouter()
{

    QSqlQuery query;
    QString id_string=QString::number(id);
    query.prepare("INSERT INTO livraison (idl, Datel, adresse, adresse_dep) "
                  "VALUES (DEFAULT, :Datel, :adresse, :adresse_dep)");
    query.bindValue(":Datel", DateTime);
    query.bindValue(":adresse", adresse);
    query.bindValue(":adresse_dep", adresse_dep);


    return query.exec();
}

bool Livraison::controlAD()
{
    if (adresse_dep.isEmpty())
        return true;
    else return false;
}

bool Livraison::controlA()
{
    if (adresse.isEmpty())
        return true;
    else return false;
}

bool Livraison::modifier(int id)
{
    QSqlQuery query;
    QString id_string=QString::number(id);
    query.prepare("UPDATE livraison SET "
                  "Datel=:Datel, adresse=:adresse, adresse_dep=:adresse_dep "
                  "WHERE idl=:idl");

    query.bindValue(":idl", id_string);
    query.bindValue(":Datel", DateTime);
    query.bindValue(":adresse", adresse);
    query.bindValue(":adresse_dep", adresse_dep);

    return query.exec();
}

bool Livraison::supprimer(int id)
{
    QSqlQuery query;
    QString id_string=QString::number(id);
    query.prepare("DELETE FROM livraison WHERE idl=:idl");
    query.bindValue(":idl", id);


    return query.exec();
}

QSqlQueryModel* Livraison::afficher()
{
    QSqlQueryModel* model =new QSqlQueryModel();

    model->setQuery("SELECT * FROM livraison");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Livraison"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse Départ"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse Livraison"));

    return model;
}

QSqlQueryModel* Livraison::triAlpha()
{
    QSqlQueryModel* model =new QSqlQueryModel();

    model->setQuery("SELECT * FROM livraison Order By Adresse");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Livraison"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse Départ"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse Livraison"));


    return model;
}


QSqlQueryModel* Livraison::triDate()
{
    QSqlQueryModel* model =new QSqlQueryModel();

    model->setQuery("SELECT * FROM livraison Order By Datel");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Livraison"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse Départ"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse Livraison"));


    return model;
}

QSqlQueryModel* Livraison::chercher(QString recherche) //recherche par ID
{
    QSqlQueryModel* model=new QSqlQueryModel();
    QSqlQuery query;

    if (recherche.length()!=0)
    {
    query.prepare("SELECT * FROM Livraison where IDL=?");
    query.addBindValue(recherche);
    query.exec();
    model->setQuery(query);
    }
    else
    {
        model->setQuery("SELECT * FROM Livraison");
    }
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Livraison"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse Départ"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse Livraison"));

    return model;

}


QSqlQueryModel* Livraison::search(QString recherche) //recherche par Adresse
{
    QSqlQueryModel* model=new QSqlQueryModel();
    QSqlQuery query;

    if (recherche.length()!=0)
    {
    query.prepare("SELECT * FROM Livraison WHERE Adresse LIKE '%"+recherche+"%' OR Adresse_dep LIKE '%"+recherche+"%' ");
    query.addBindValue(recherche);
    query.exec();
    model->setQuery(query);
    }
    else
    {
        model->setQuery("SELECT * FROM Livraison");
    }
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID Livraison"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse Départ"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Adresse Livraison"));

    return model;

}


void Livraison::generatePdf(QTableView * tableView)
{
    QString strStream;
    QTextStream out(&strStream);

    const int rowCount = tableView->model()->rowCount();
    const int columnCount = tableView->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"
        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%1</title>\n").arg("test")
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<table border=1 cellspacing=0 cellpadding=2>\n";

    // headers
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (!tableView->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(tableView->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    // data table
    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!tableView->isColumnHidden(column)) {
                QString data = tableView->model()->data(tableView->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete document;
}




QList<QVariant> Livraison::fetchDates()
{
    QList<QVariant> list;
    QSqlQuery query;

    query.prepare("SELECT datel FROM livraison");
    query.exec();
    while (query.next()) {
        list.append(query.value("datel"));
    }
    return list;
}
