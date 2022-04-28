#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dons.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QValidator>
#include <QPrinter>
#include <QPrintDialog>
#include <QPixmap>
#include <QTextDocument>
#include "statistique.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QIntValidator ex;
    ui->setupUi(this);
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";

    }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
    //le slot update_label suite à la reception du signal readyRead (reception des données).

 //   connect(ui->Confirmer, SIGNAL(clicked()),this, SLOT(sendMail()));
   // connect(ui->Annuler, SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->envoyer_SMTP, SIGNAL(clicked()),this, SLOT(sendMail()));
       connect(ui->Annuler_dons, SIGNAL(clicked()),this, SLOT(close()));
       ui->le_server_SMTP->setText("smtp.gmail.com");
        ui->le_port_SMTP->setText("465");
        ui->le_mail_SMTP->setText("mmarrouki52@gmail.com");
        ui->le_passwd_SMTP->setText("Marrouki21062001!");
        ui->le_objet_SMTP->setText("Donation success");

   // ui->le_id->setValidator(new QIntValidator(0, 99999999,this));
    ui->le_id_Supp_dons->setValidator(new QIntValidator(0, 99999999,this));
    ui->le_id_Modif_dons->setValidator(new QIntValidator(0, 99999999,this));
    ui->le_montant_dons->setValidator(new QIntValidator(0, 99999999,this));
    ui->le_montant_Modif_dons->setValidator(new QIntValidator(0, 99999999,this));
    QRegExp reg("^([a-zA-Z0-9_\-\.]+)@([a-zA-Z0-9_\-\.]+)\.([a-zA-Z]{2,5})$ ");
        QValidator *validator = new QRegExpValidator(reg, this);
        ui->le_email_dons->setValidator(validator);
        ui->le_email_Modif_dons->setValidator(validator);
    ui->tableView_dons->setModel(Dtmp.afficher_dons());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendMail()
{
     Smtp* smtp = new Smtp("mmarrouki52@gmail.com","Marrouki21062001!","smtp.gmail.com",465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail("mmarrouki52@gmail.com",ui->le_email_dons->text(),"Donation success","Thank you for your support");
}
void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

void MainWindow::on_Confirmer_dons_clicked()
{

    //int id=ui->le_id->text().toInt();
   // Smtp* smtp = new Smtp("mmarrouki52@gmail.com","Marrouki21062001!","smtp.gmail.com",465);
    //connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    QString nom=ui->le_nom_don->text();
    QString adresse=ui->le_adresse_dons->text();
    QString email=ui->le_email_dons->text();
    int montant=ui->le_montant_dons->text().toInt();
    QDate date=ui->de_dons->date();
    Dons Dtmp(nom,adresse,email,date,montant);
    if ((Dtmp.Verif_email()) || (Dtmp.Verif_nom()) || (Dtmp.Verif_adresse()) || (Dtmp.Verif_montant_z()))
{        if(Dtmp.Verif_email())
           { ui->email_verif_dons->clear();
        ui->email_verif_dons->setText("Email doit être valide : @exemple.ex");
        ui->le_email_dons->clear();}
        if(Dtmp.Verif_nom())
           { ui->email_verif_dons->clear();
        ui->email_verif_dons->setText("Le nom doit être non vide");
        ui->le_nom_don->clear();}
        if(Dtmp.Verif_adresse())
         {   ui->email_verif_dons->clear();
        ui->email_verif_dons->setText("L'adresse doit être non vide");
        ui->le_adresse_dons->clear();}
        if(Dtmp.Verif_montant_z())
        {ui->email_verif_dons->clear();
        ui->email_verif_dons->setText("Le montant doit être different de 0");
        ui->le_montant_dons->clear();}
        /*if(Dtmp.Verif_id())
        {ui->email_verif->clear();
            ui->email_verif->setText("L'ID doit être different de 0");
        ui->le_id->clear();}*/

}
   else{
       QString s=ui->le_email_dons->text();
        ui->le_rcpt_SMTP->setText(s);

        /*Smtp* smtp = new Smtp(ui->uname->text(),ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
           connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


           smtp->sendMail(ui->uname->text(),  ui->rcpt->text() , ui->subject->text(),"Thank you for your support");

           QMessageBox::information(nullptr, QObject::tr("Succès"),
                       QObject::tr("Le mail a été envoyé avec succès.\n"
                                   "Cliquer sur Cancel to exit."), QMessageBox::Cancel);*/

ui->email_verif_dons->clear();
    bool test=Dtmp.ajouter_dons();
    //ui->le_id->clear();
    ui->le_email_dons->clear();
    ui->le_adresse_dons->clear();
    ui->le_montant_dons->clear();
    ui->le_nom_don->clear();
    ui->de_dons->clear();
}
    ui->tableView_dons->setModel(Dtmp.afficher_dons());
    /*QString n=ui->le_nom_don->text();
    QByteArray b=b.append(n);
    A.write_to_arduino(b);*/

}

void MainWindow::on_supprimer_dons_clicked()
{
    int id=ui->le_id_Supp_dons->text().toInt();
    bool test=Dtmp.supprimer_dons(id);
    ui->tableView_dons->setModel(Dtmp.afficher_dons());
    ui->le_id_Supp_dons->clear();
}


/*void MainWindow::on_Refresh_clicked()
{
    ui->tableView_dons->setModel(Dtmp.afficher());
}*/

void MainWindow::on_Modifier_dons_clicked()
{

   int id = ui->le_id_Modif_dons->text().toInt();
    int montant=ui->le_montant_Modif_dons->text().toInt();
    // QString cin_string= QString::number(cin);
     QString nom=ui->le_nom_Modif_dons->text();
     QString adresse = ui->le_adresse_Modif_dons->text();
     QString email = ui->le_email_Modif_dons->text();
     QDate date_don = ui->de_Modif_dons->date();
     Dons Dtmp(nom,adresse,email,date_don,montant);
     if ((Dtmp.Verif_email()) || (Dtmp.Verif_nom()) || (Dtmp.Verif_adresse()) || (Dtmp.Verif_montant_z()) || (Dtmp.Verif_id()))
 {        if(Dtmp.Verif_email())
            { ui->email_verif_Modif_dons->clear();
         ui->email_verif_Modif_dons->setText("Email doit être valide : @exemple.ex");
          ui->le_email_Modif_dons->clear();}
         if(Dtmp.Verif_nom())
            { ui->email_verif_Modif_dons->clear();
         ui->email_verif_Modif_dons->setText("Le nom doit être non vide");
         ui->le_nom_Modif_dons->clear();}
         if(Dtmp.Verif_adresse())
          {   ui->email_verif_Modif_dons->clear();
         ui->email_verif_Modif_dons->setText("L'adresse doit être non vide");
         ui->le_adresse_Modif_dons->clear();}
         if(Dtmp.Verif_montant_z())
         {ui->email_verif_Modif_dons->clear();
         ui->email_verif_Modif_dons->setText("Le montant doit être different de 0");
          ui->le_montant_Modif_dons->clear();}
         if(Dtmp.Verif_id())
         {ui->email_verif_Modif_dons->clear();
             ui->email_verif_Modif_dons->setText("L'ID doit être different de 0");
              ui->le_id_Modif_dons->clear();}
 }
    else{
 ui->email_verif_Modif_dons->clear();
    bool test = Dtmp.modifier_dons(id);
    ui->le_id_Modif_dons->clear();
    ui->le_email_Modif_dons->clear();
    ui->le_adresse_Modif_dons->clear();
    ui->le_montant_Modif_dons->clear();
    ui->le_nom_Modif_dons->clear();
    ui->de_Modif_dons->clear();

     }
     ui->tableView_dons->setModel(Dtmp.afficher_dons());
}



void MainWindow::on_Annuler_dons_clicked()
{
    //ui->le_id->clear();
    ui->le_email_dons->clear();
    ui->le_adresse_dons->clear();
    ui->le_montant_dons->clear();
    ui->le_nom_don->clear();
    ui->de_dons->clear();
    ui->email_verif_dons->clear();
}



void MainWindow::on_Annuler_Modif_dons_clicked()
{
    ui->le_id_Modif_dons->clear();
    ui->le_email_Modif_dons->clear();
    ui->le_adresse_Modif_dons->clear();
    ui->le_montant_Modif_dons->clear();
    ui->le_nom_Modif_dons->clear();
    ui->de_Modif_dons->clear();
    ui->email_verif_Modif_dons->clear();
}

void MainWindow::on_Trier_clicked()
{
    ui->tableView_dons->setModel(Dtmp.Trier_dons());
}

void MainWindow::on_Chercher_clicked()
{
    QString recherche = ui->le_chercher_dons->text();
    if(recherche.length()!=0)
       ui->tableView_dons->setModel(Dtmp.rechercher_dons(recherche));
    else
    {
       ui->tableView_dons->setModel(Dtmp.afficher_dons());
    }
}


void MainWindow::on_Total_dons_clicked()
{
    //ui->label_total->clear();
    //QString ch="la somme des dons est ";

    //QString chT= ch + ch1;

    ui->tableView_T_dons->setModel(Dtmp.Total_don());
}

void MainWindow::on_comboBox_dons_activated(const QString &arg1)
{
    if(ui->comboBox_dons->currentText()=="Tri")
      ui->tableView_dons->setModel(Dtmp.afficher_dons());
    else if(ui->comboBox_dons->currentText()=="Par ID")
        ui->tableView_dons->setModel(Dtmp.Trier_ID_dons());
    else if (ui->comboBox_dons->currentText()=="Par Nom")
        ui->tableView_dons->setModel(Dtmp.Trier_NOM_dons());
    else ui->tableView_dons->setModel(Dtmp.Trier_dons());
}

void MainWindow::on_le_chercher_dons_textChanged(const QString &arg1)
{
    QString recherche = ui->le_chercher_dons->text();
    if(recherche.length()!=0)
       ui->tableView_dons->setModel(Dtmp.rechercher_dons(recherche));
    else
    {
       ui->tableView_dons->setModel(Dtmp.afficher_dons());
    }
}

void MainWindow::on_PDF_dons_clicked()
{
    QString strStream;
                       QTextStream out(&strStream);

                       const int rowCount = ui->tableView_dons->model()->rowCount();
                       const int columnCount = ui->tableView_dons->model()->columnCount();
                       QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                       out <<"<html>\n"
                             "<head>\n"
                              "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                           << "<title> LISTE DES PRODUITS<title>\n "
                           << "</head>\n"
                           "<body bgcolor=#ffffff link=#5000A0>\n"
                           "<h1 style=\"text-align: center;\"><strong> **LISTE DES DONS ** "+TT+"</strong></h1>"
                           "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                             "</br> </br>";
                       // headers
                       out << "<thead><tr bgcolor=#d6e5ff>";
                       for (int column = 0; column < columnCount; column++)
                           if (!ui->tableView_dons->isColumnHidden(column))
                               out << QString("<th>%1</th>").arg(ui->tableView_dons->model()->headerData(column, Qt::Horizontal).toString());
                       out << "</tr></thead>\n";

                       // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tableView_dons->isColumnHidden(column)) {
                                   QString data =ui->tableView_dons->model()->data(ui->tableView_dons->model()->index(row, column)).toString().simplified();
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

                       QPrintDialog *test = new QPrintDialog(&printer, NULL);
                       if (test->exec() == QDialog::Accepted) {
                           document->print(&printer);
                       }

                       delete document;
}

void MainWindow::on_stats_dons_clicked()
{
    statistique s;
        s.exec();
}

void MainWindow::on_envoyer_SMTP_clicked()
{
    Smtp* smtp = new Smtp(ui->le_mail_SMTP->text(), ui->le_passwd_SMTP->text(), ui->le_server_SMTP->text(), ui->le_port_SMTP->text().toInt());
       connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


       smtp->sendMail(ui->le_mail_SMTP->text(), ui->le_rcpt_SMTP->text() , ui->le_objet_SMTP->text(),"Thank you for your support");

       QMessageBox::information(nullptr, QObject::tr("Succès"),
                   QObject::tr("Le mail a été envoyé avec succès.\n"
                               "Cliquer sur Cancel to exit."), QMessageBox::Cancel);
}



void MainWindow::on_Arduino_dons_clicked()
{
    QString ido;
        string conv;
        const char *texto;
        QModelIndex index=ui->tableView_dons->selectionModel()->currentIndex();
        QVariant value=index.sibling(index.row(),index.column()).data(); //will get the value of the clicked cell.
        ido=value.toString();
        conv = ido.toStdString();
        texto=conv.c_str();
    A.write_to_arduino(texto);
}
void MainWindow::update_label()
{
data=A.read_from_arduino();

if(data=="1")
{
     ui->tableView_Ard_dons->setModel(Dtmp.afficher_capteur());
     QString strStream;
                        QTextStream out(&strStream);

                        const int rowCount = ui->tableView_Ard_dons->model()->rowCount();
                        const int columnCount = ui->tableView_Ard_dons->model()->columnCount();
                        QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                        out <<"<html>\n"
                              "<head>\n"
                               "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                            << "<title> LISTE DES PRODUITS<title>\n "
                            << "</head>\n"
                            "<body bgcolor=#ffffff link=#5000A0>\n"
                            "<h1 style=\"text-align: center;\"><strong> **LISTE DES DONS ** "+TT+"</strong></h1>"
                            "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                              "</br> </br>";
                        // headers
                        out << "<thead><tr bgcolor=#d6e5ff>";
                        for (int column = 0; column < columnCount; column++)
                            if (!ui->tableView_Ard_dons->isColumnHidden(column))
                                out << QString("<th>%1</th>").arg(ui->tableView_Ard_dons->model()->headerData(column, Qt::Horizontal).toString());
                        out << "</tr></thead>\n";

                        // data table
                        for (int row = 0; row < rowCount; row++) {
                            out << "<tr>";
                            for (int column = 0; column < columnCount; column++) {
                                if (!ui->tableView_Ard_dons->isColumnHidden(column)) {
                                    QString data =ui->tableView_Ard_dons->model()->data(ui->tableView_Ard_dons->model()->index(row, column)).toString().simplified();
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

                        QPrintDialog *test = new QPrintDialog(&printer, NULL);
                        if (test->exec() == QDialog::Accepted) {
                            document->print(&printer);
                        }

                        delete document;
}

else if (data=="0")
{
      ui->tableView_Ard_dons->setModel(Dtmp.afficher_capteur2());  // si les données reçues de arduino via la liaison série sont égales à 0
 //alors afficher ON
}
}
