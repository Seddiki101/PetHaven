#include "../headers/adoption.h"

Adoption::Adoption(int ido,int ida,int idp,QDate dates)
{
    this->idAdoption=ido;
    this->ida=ida;
    this->idp=idp;
    this->dates=dates;
}

QSqlQueryModel * animal::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from animals where animals.status = 1")	;
    return model;
}



QSqlQueryModel * beneficiaire::afficher()
{
	QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from BENEFICIAIRES where BENEFICIAIRES.status = 1")	;
    return model;
}




QSqlQueryModel * Adoption::affichAdo()
{
	QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT adoption.ido,adoption.ida,animals.nom,adoption.dates,adoption.cin,beneficiaires.Prenom,beneficiaires.nom "
                    "FROM adoption,beneficiaires,animals "
                    "WHERE ( adoption.IDA = animals.IDA AND adoption.cin = beneficiaires.cin )");
    return model;
}

QSqlQueryModel * Adoption::affichAnimals()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM animals "
                    "WHERE status=1");
    return model;
}

QSqlQueryModel * Adoption::affichBeneficiaires()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM beneficiaires "
                    "WHERE status=1");
    return model;
}



QSqlQueryModel * Adoption::triAlphAdo()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT adoption.ido,adoption.ida,animals.nom,adoption.dates,adoption.cin,beneficiaires.Prenom,beneficiaires.nom "
                    "FROM adoption,beneficiaires,animals "
                    "WHERE ( adoption.IDA = animals.IDA AND adoption.cin = beneficiaires.cin ) "
                    "ORDER BY animals.nom");
    return model;
}



QSqlQueryModel * Adoption::triDatesAdo()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT adoption.ido,adoption.ida,animals.nom,adoption.dates,adoption.cin,beneficiaires.Prenom,beneficiaires.nom "
                    "FROM adoption,beneficiaires,animals "
                    "WHERE ( adoption.IDA = animals.IDA AND adoption.cin = beneficiaires.cin ) "
                    "ORDER BY adoption.dates desc");
    return model;
}




bool Adoption::ajoutAdo()
{
    QSqlQuery query,qury,qery;
    QString ida_string=QString::number(ida);
    QString idp_string=QString::number(idp);

    query.prepare("insert into ADOPTION (IDO,IDA,CIN,DATES) "
                  "values(DEFAULT, :IDA, :IDP, :DATES)");

    query.bindValue(":IDA",ida_string);
    query.bindValue(":IDP",idp_string);
    query.bindValue(":DATES",dates);

    qury.prepare("UPDATE animals set status=0 WHERE IDA=:IDA");
    qury.bindValue(":IDA",ida_string);

    qery.prepare("UPDATE BENEFICIAIRES set status=0 WHERE CIN=:IDP");
    qery.bindValue(":IDP",idp_string);

    qury.exec();
    qery.exec();

    return query.exec() && qury.exec();
}


bool Adoption::supprimAdo(int ido, int ida, int idp)
{
    QSqlQuery query,qury,qery;
    QString id_string=QString::number(ido);
    query.prepare("DELETE FROM ADOPTION WHERE ido=:ido");
    query.bindValue(":ido", id_string);

    qury.prepare("UPDATE animals set status=1 WHERE IDA=:IDA");
    qury.bindValue(":IDA", ida);

    qery.prepare("UPDATE BENEFICIAIRES set status=1 WHERE CIN=:IDP");
    qery.bindValue(":IDP", idp);

    qury.exec();
    qery.exec();

    return query.exec() && qury.exec();
}



bool Adoption::modifierAdo(int ido,int idp,int ida)
{
    QSqlQuery query;
    query.prepare("UPDATE adoption set cin=:idp,ida=:ida "
                  "WHERE ido=:ido");
    query.bindValue(":ido",ido);
    query.bindValue(":idp",idp);
    query.bindValue(":ida",ida);
    return query.exec();
}


QSqlQueryModel* Adoption::chercherAdo(QString recherche)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    QSqlQuery query;

    if (recherche.length() != 0)
    {
        query.prepare("SELECT o.ido,o.ida,a.nom,o.dates,o.cin,b.Prenom,b.nom "
                      "FROM Beneficiaires b INNER JOIN adoption o ON b.CIN = o.CIN INNER JOIN Animals a ON o.IDA = a.IDA "
                      "WHERE IDO=?");
        query.addBindValue(recherche);
        query.exec();
        model->setQuery(query);
    }
    else
    {
        model = affichAdo();
    }

    return model;
}



QSqlQueryModel* Adoption::searchAdo(QString recherche)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    QSqlQuery query;

    if (recherche.length() != 0)
    {
        query.prepare("SELECT o.ido,o.ida,a.nom,o.dates,o.cin,b.Prenom,b.nom "
                      "FROM Beneficiaires b INNER JOIN adoption o ON b.CIN = o.CIN INNER JOIN Animals a ON o.IDA = a.IDA "
                      "WHERE b.prenom LIKE '"+recherche+"%' OR b.nom LIKE '"+recherche+"%' OR a.nom LIKE '"+recherche+"%' ");
        query.addBindValue(recherche);
        query.exec();
        model->setQuery(query);
    }
    else
    {
        model = affichAdo();
    }
    return model;
}


void Adoption::genereExcel(QTableView *table)
{

         QString filters("CSV files (.csv);;All files (.*)");
         QString defaultFilter("CSV files (*.csv)");
         QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                                  filters, &defaultFilter);
               QFile file(fileName);

               QAbstractItemModel *model =  table->model();
               if (file.open(QFile::WriteOnly | QFile::Truncate)) {
                   QTextStream data(&file);
                   QStringList strList;
                   for (int i = 0; i < model->columnCount(); i++) {
                       if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                           strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                       else
                           strList.append("");
                   }
                   data << strList.join(";") << "\n";
                   for (int i = 0; i < model->rowCount(); i++) {
                       strList.clear();
                       for (int j = 0; j < model->columnCount(); j++) {

                           if (model->data(model->index(i, j)).toString().length() > 0)
                               strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                           else
                               strList.append("");
                       }
                       data << strList.join(";") + "\n";
                   }
                   file.close();
                   QMessageBox::information(nullptr, QObject::tr("GENERATION EXCEL"),
                                             QObject::tr("GENERATION REALISEE AVEC SUCCES\n"
                                                         "Click OK to exit."), QMessageBox::Ok);
               }

}






void Adoption::generatePdf(QTableView * tableView)
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





QSqlQueryModel * Adoption::Totado()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT TO_CHAR(TO_DATE((Extract(MONTH from Dates)), 'MM'), 'MONTH') as mois,count (dates) from adoption group by Extract(MONTH from Dates) ;")	;
    return model;
}
