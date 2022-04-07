#include "beneficiaire.h"
//#include "mainwindow.h"


Beneficiaire::Beneficiaire(){
    CIN=0; name=""; lastname="";  age=0;  adress="";  type=""; num=0; QDateTime date = QDateTime::currentDateTime();
};
Beneficiaire::Beneficiaire(int CIN, QString name,QString lastname, int age, QString adress, QString type, int num, QDateTime date)
{
    this->CIN=CIN;
    this->name=name;
    this->lastname=lastname;
    this->age=age;
    this->adress=adress;
    this->type=type;
    this->num=num;
    this->date=date;
}


void Beneficiaire::setCIN(int cin)
{
    CIN=cin;
}
void Beneficiaire::setName(QString NAME)
{
    name=NAME;
}
void Beneficiaire::setLastName(QString LASTNAME)
{
    lastname=LASTNAME;
}
void Beneficiaire::setAge(int AGE)
{
    age=AGE;
}
void Beneficiaire::setAdress(QString ADRESS)
{
    adress=ADRESS;
}
void Beneficiaire::setType(QString TYPE)
{
    type=TYPE;
}

void Beneficiaire::setNum(int NUM)
{
    type=NUM;
}

void Beneficiaire::setDate(QDateTime DATE)
{
    date=DATE;
}

int Beneficiaire::getCIN(){return CIN;}
QString Beneficiaire::getName(){return name;}
QString Beneficiaire::getLastName(){return lastname;}
int Beneficiaire::getAge(){return age;}
QString Beneficiaire::getAdress(){return adress;}
QString Beneficiaire::getType(){return type;}
int Beneficiaire::getNum(){return num;}
QDateTime Beneficiaire::getDate(){return date;}

//affcihage

QSqlQueryModel * Beneficiaire::afficher(QString search, int tri)
{
	QSqlQueryModel * model=new QSqlQueryModel();


    if(tri==1)
    model->setQuery("select * from BENEFICIAIRES ODER BY nom desc" )	;
    else if(tri==2)
    model->setQuery("select * from BENEFICIAIRES ORDER BY age desc")	;
    else if(tri==0)
    model->setQuery("select * from BENEFICIAIRES")	;

    if(search.length()!=0 && tri==0)
    {
        model->setQuery("select * from BENEFICIAIRES where nom LIKE '"+search+"%'" );
    }

model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("AGE"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("ADRESSE"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("TYPE"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("NUM"));
model->setHeaderData(7,Qt::Horizontal,QObject::tr("DATE"));
return model;
}


bool Beneficiaire::ajouter()
{
        QSqlQuery query;
        QString CIN_string=QString::number(CIN);
        QString age_string=QString::number(age);
        QString num_string=QString::number(num);



        //prepare() prend la requete en paramètre pour la préparer à l'éxécution

        query.prepare("insert into BENEFICIAIRES (CIN,NOM,PRENOM,AGE,ADRESSE,TYPE,NUM,DATEAJOUT) values (:CIN, :name, :lastname, :age, :adress, :type, :num, :date)");


        query.bindValue(":CIN",CIN_string);
        query.bindValue(":age",age_string);
        query.bindValue(":name",name);
        query.bindValue(":lastname",lastname);
        query.bindValue(":adress",adress);
        query.bindValue(":type",type);
        query.bindValue(":num",num_string);
        query.bindValue(":date",date);

        //qDebug() << "Name value : " << name;

      return query.exec(); //exec() envoie la requete pour l'exécuter.
}


bool Beneficiaire::supprimer(int CIN)
{




        QSqlQuery query;
        QString CIN_string=QString::number(CIN);
              query.prepare("DELETE FROM BENEFICIAIRES WHERE CIN=:CIN");
              query.bindValue(":CIN", CIN_string);


              return query.exec();
}

bool Beneficiaire::modifier( int CIN, QString name,QString lastname, int age, QString adresse, QString type, int num)
{
    QSqlQuery query;
    //QString OLDCIN_string=QString::number(OLDCIN);
     //QString CIN_string=QString::number(CIN);
     //QString age_string=QString::number(age);
     //QString num_string=QString::number(num);

          query.prepare("UPDATE beneficiaires set age=:age, nom=:name, prenom=:lastname, adresse=:adresse, type=:type, num=:num where CIN=:CIN");


          query.bindValue(":CIN",CIN);
          query.bindValue(":age",age);
          query.bindValue(":name",name);
          query.bindValue(":lastname",lastname);
          query.bindValue(":adresse",adresse);
          query.bindValue(":type",type);
         query.bindValue(":num",num);

          return query.exec();
}

void Beneficiaire::exportPDF(QTableView * tableView)
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
