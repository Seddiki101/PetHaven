#include "animal.h"


Animal::Animal()
{
    age=0;
    nom="";
    espece="";
    race="";
}

    Animal::Animal(int age, int status, QString nom, QString espece, QString race, QDate date_arr)
    {
        this->age=age; this->status=status; this->nom=nom; this->espece=espece; this->race=race; this->date_arr=date_arr;
    }

    int Animal::getAge()
    {
        return age;
    }
    int Animal::getStatus()
    {
        return status;
    }
    QString Animal::getNom()
    {
        return nom;
    }
    QString Animal::getEspece()
    {
        return espece;
    }
    QString Animal::getRace()
    {
        return race;
    }
    QDate Animal::getDate_arr()
    {
        return date_arr;
    }


void Animal::setAge(int age)                {this->age=age;}
void Animal::setStatus(int status)          {this->status=status;}
void Animal::setNom(QString nom)            {this->nom=nom;}
void Animal::setEspece(QString espece)      {this->espece=espece;}
void Animal::setRace(QString race)          {this->race=race;}
void Animal::setDate_arr(QDate date_arr)    {this->date_arr=date_arr;}



bool Animal::Empty(QString text)
{
    return text.size() == 0;
}


bool Animal::ajouter()
{
    QSqlQuery query;
    QString age_string=QString::number(age);
    query.prepare("INSERT INTO animals (IDA, age, nom, espece, race, status, date_arr) "
                  "VALUES (DEFAULT, :age, :nom, :espece, :race, DEFAULT, :date_arr)");

    query.bindValue(":age", age_string);
    query.bindValue(":nom", nom);
    query.bindValue(":espece", espece);
    query.bindValue(":race", race);
    query.bindValue(":date_arr", date_arr);

    return query.exec();
}

bool Animal::modifier(int id)
{
    QSqlQuery query;
    QString id_string=QString::number(id);
    QString age_string=QString::number(age);
    QString status_string=QString::number(status);
    query.prepare("UPDATE animals SET "
                  "age=:age, nom=:nom, espece=:espece, race=:race, status=:status, date_arr=:date_arr "
                  "WHERE IDA=:id");

    query.bindValue(":id", id_string);
    query.bindValue(":age", age_string);
    query.bindValue(":status", status_string);
    query.bindValue(":nom", nom);
    query.bindValue(":espece", espece);
    query.bindValue(":race", race);
    query.bindValue(":date_arr", date_arr);

    return query.exec();
}

bool Animal::supprimer(int id)
{
    QSqlQuery query;
    QString id_string=QString::number(id);

    query.prepare("DELETE FROM animals WHERE IDA=:id");
    query.bindValue(":id", id_string);
    return query.exec();
}

QSqlQueryModel* Animal::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery ("SELECT * FROM animals ");
    model->setHeaderData (0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData (1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData (2, Qt::Horizontal, QObject::tr("Race"));
    model->setHeaderData (3, Qt::Horizontal, QObject::tr("Espece"));
    model->setHeaderData (4, Qt::Horizontal, QObject::tr("Age"));
    model->setHeaderData (5, Qt::Horizontal, QObject::tr("Status"));
    model->setHeaderData (6, Qt::Horizontal, QObject::tr("Date"));

    return model;
}


QSqlQueryModel* Animal::sortName()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT * FROM animals "
                    "ORDER BY LOWER(nom) ASC");

    model->setHeaderData (0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData (1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData (2, Qt::Horizontal, QObject::tr("Race"));
    model->setHeaderData (3, Qt::Horizontal, QObject::tr("Espece"));
    model->setHeaderData (4, Qt::Horizontal, QObject::tr("Age"));
    model->setHeaderData (5, Qt::Horizontal, QObject::tr("Status"));
    model->setHeaderData (6, Qt::Horizontal, QObject::tr("Date"));

    return model;
}

QSqlQueryModel* Animal::sortDates()
{
    QSqlQueryModel* model=new QSqlQueryModel();

    model->setQuery("SELECT * FROM animals "
                    "ORDER BY date_arr DESC");

    model->setHeaderData (0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData (1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData (2, Qt::Horizontal, QObject::tr("Race"));
    model->setHeaderData (3, Qt::Horizontal, QObject::tr("Espece"));
    model->setHeaderData (4, Qt::Horizontal, QObject::tr("Age"));
    model->setHeaderData (5, Qt::Horizontal, QObject::tr("Status"));
    model->setHeaderData (6, Qt::Horizontal, QObject::tr("Date"));

    return model;
}




QSqlQueryModel* Animal::searchID(QString research)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    QSqlQuery query;

    if (research.length() != 0)
    {
    query.prepare("SELECT * FROM animals "
                  "WHERE IDA=?");
    query.addBindValue(research);
    query.exec();
    model->setQuery(query);
    }
    else
    {
        return afficher();
    }

    return model;
}



QSqlQueryModel* Animal::searchName(QString research)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    QSqlQuery query;

    if (research.length() != 0)
    {

    query.prepare("SELECT * FROM animals "
                  "WHERE nom LIKE '"+research+"%' OR race LIKE '"+research+"%' OR espece LIKE '"+research+"%'");

    query.addBindValue(research);
    query.exec();
    model->setQuery(query);

    }
    else
    {
        return afficher();
    }

    return model;
}




void Animal::generatePdf(QTableView* tableView)
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
