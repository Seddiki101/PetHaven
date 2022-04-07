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
 //   connect(ui->Confirmer, SIGNAL(clicked()),this, SLOT(sendMail()));
   // connect(ui->Annuler, SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->Confirmer, SIGNAL(clicked()),this, SLOT(sendMail()));
       connect(ui->Annuler, SIGNAL(clicked()),this, SLOT(close()));
       ui->server->setText("smtp.gmail.com");
        ui->port->setText("465");
        ui->uname->setText("mmarrouki52@gmail.com");
        ui->paswd->setText("Marrouki21062001!");
        ui->subject->setText("Donation success");

   // ui->le_id->setValidator(new QIntValidator(0, 99999999,this));
    ui->le_id_Supp->setValidator(new QIntValidator(0, 99999999,this));
    ui->le_id_Modif->setValidator(new QIntValidator(0, 99999999,this));
    ui->le_montant->setValidator(new QIntValidator(0, 99999999,this));
    ui->le_montant_Modif->setValidator(new QIntValidator(0, 99999999,this));
    QRegExp reg("^([a-zA-Z0-9_\-\.]+)@([a-zA-Z0-9_\-\.]+)\.([a-zA-Z]{2,5})$ ");
        QValidator *validator = new QRegExpValidator(reg, this);
        ui->le_email->setValidator(validator);
        ui->le_email_Modif->setValidator(validator);
    ui->tableView->setModel(Dtmp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendMail()
{
     Smtp* smtp = new Smtp("mmarrouki52@gmail.com","Marrouki21062001!","smtp.gmail.com",465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail("mmarrouki52@gmail.com",ui->le_email->text(),"Donation success","Thank you for your support");
}
void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

void MainWindow::on_Confirmer_clicked()
{
    //int id=ui->le_id->text().toInt();
   // Smtp* smtp = new Smtp("mmarrouki52@gmail.com","Marrouki21062001!","smtp.gmail.com",465);
    //connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    QString nom=ui->le_nom_don->text();
    QString adresse=ui->le_adresse->text();
    QString email=ui->le_email->text();
    int montant=ui->le_montant->text().toInt();
    QDate date=ui->de->date();
    Dons Dtmp(nom,adresse,email,date,montant);
    if ((Dtmp.Verif_email()) || (Dtmp.Verif_nom()) || (Dtmp.Verif_adresse()) || (Dtmp.Verif_montant_z()))
{        if(Dtmp.Verif_email())
           { ui->email_verif->clear();
        ui->email_verif->setText("Email doit être valide : @exemple.ex");
        ui->le_email->clear();}
        if(Dtmp.Verif_nom())
           { ui->email_verif->clear();
        ui->email_verif->setText("Le nom doit être non vide");
        ui->le_nom_don->clear();}
        if(Dtmp.Verif_adresse())
         {   ui->email_verif->clear();
        ui->email_verif->setText("L'adresse doit être non vide");
        ui->le_adresse->clear();}
        if(Dtmp.Verif_montant_z())
        {ui->email_verif->clear();
        ui->email_verif->setText("Le montant doit être different de 0");
        ui->le_montant->clear();}
        /*if(Dtmp.Verif_id())
        {ui->email_verif->clear();
            ui->email_verif->setText("L'ID doit être different de 0");
        ui->le_id->clear();}*/
}
   else{
        QString s=ui->le_email->text();
        ui->rcpt->setText(s);
        Smtp* smtp = new Smtp(ui->uname->text(),ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
           connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


           smtp->sendMail(ui->uname->text(),  ui->rcpt->text() , ui->subject->text(),"Thank you for your support");

           QMessageBox::information(nullptr, QObject::tr("Succès"),
                       QObject::tr("Le mail a été envoyé avec succès.\n"
                                   "Cliquer sur Cancel to exit."), QMessageBox::Cancel);
ui->email_verif->clear();
    bool test=Dtmp.ajouter();
    //ui->le_id->clear();
    ui->le_email->clear();
    ui->le_adresse->clear();
    ui->le_montant->clear();
    ui->le_nom_don->clear();
    ui->de->clear();
}
    ui->tableView->setModel(Dtmp.afficher());

}

void MainWindow::on_supprimer_clicked()
{
    int id=ui->le_id_Supp->text().toInt();
    bool test=Dtmp.supprimer(id);
    ui->tableView->setModel(Dtmp.afficher());
    ui->le_id_Supp->clear();
}


/*void MainWindow::on_Refresh_clicked()
{
    ui->tableView->setModel(Dtmp.afficher());
}*/

void MainWindow::on_Modifier_clicked()
{

   int id = ui->le_id_Modif->text().toInt();
    int montant=ui->le_montant_Modif->text().toInt();
    // QString cin_string= QString::number(cin);
     QString nom=ui->le_nom_Modif->text();
     QString adresse = ui->le_adresse_Modif->text();
     QString email = ui->le_email_Modif->text();
     QDate date_don = ui->de_Modif->date();
     Dons Dtmp(nom,adresse,email,date_don,montant);
     if ((Dtmp.Verif_email()) || (Dtmp.Verif_nom()) || (Dtmp.Verif_adresse()) || (Dtmp.Verif_montant_z()) || (Dtmp.Verif_id()))
 {        if(Dtmp.Verif_email())
            { ui->email_verif_Modif->clear();
         ui->email_verif_Modif->setText("Email doit être valide : @exemple.ex");
          ui->le_email_Modif->clear();}
         if(Dtmp.Verif_nom())
            { ui->email_verif_Modif->clear();
         ui->email_verif_Modif->setText("Le nom doit être non vide");
         ui->le_nom_Modif->clear();}
         if(Dtmp.Verif_adresse())
          {   ui->email_verif_Modif->clear();
         ui->email_verif_Modif->setText("L'adresse doit être non vide");
         ui->le_adresse_Modif->clear();}
         if(Dtmp.Verif_montant_z())
         {ui->email_verif_Modif->clear();
         ui->email_verif_Modif->setText("Le montant doit être different de 0");
          ui->le_montant_Modif->clear();}
         if(Dtmp.Verif_id())
         {ui->email_verif_Modif->clear();
             ui->email_verif_Modif->setText("L'ID doit être different de 0");
              ui->le_id_Modif->clear();}
 }
    else{
 ui->email_verif_Modif->clear();
    bool test = Dtmp.modifier(id);
    ui->le_id_Modif->clear();
    ui->le_email_Modif->clear();
    ui->le_adresse_Modif->clear();
    ui->le_montant_Modif->clear();
    ui->le_nom_Modif->clear();
    ui->de_Modif->clear();

     }
     ui->tableView->setModel(Dtmp.afficher());
}



void MainWindow::on_pushButton_2_clicked()
{
    //ui->le_id->clear();
    ui->le_email->clear();
    ui->le_adresse->clear();
    ui->le_montant->clear();
    ui->le_nom_don->clear();
    ui->de->clear();
    ui->email_verif->clear();
}



void MainWindow::on_Annuler_clicked()
{
    ui->le_id_Modif->clear();
    ui->le_email_Modif->clear();
    ui->le_adresse_Modif->clear();
    ui->le_montant_Modif->clear();
    ui->le_nom_Modif->clear();
    ui->de_Modif->clear();
    ui->email_verif_Modif->clear();
}

void MainWindow::on_Trier_clicked()
{
    ui->tableView->setModel(Dtmp.Trier());
}

void MainWindow::on_Chercher_clicked()
{
    QString recherche = ui->le_chercher->text();
    if(recherche.length()!=0)
       ui->tableView->setModel(Dtmp.rechercher(recherche));
    else
    {
       ui->tableView->setModel(Dtmp.afficher());
    }
}


void MainWindow::on_Total_clicked()
{
    //ui->label_total->clear();
    //QString ch="la somme des dons est ";

    //QString chT= ch + ch1;

    ui->tableView_T->setModel(Dtmp.Total_don());
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{
    if(ui->comboBox->currentText()=="Tri")
      ui->tableView->setModel(Dtmp.afficher());
    else if(ui->comboBox->currentText()=="Par ID")
        ui->tableView->setModel(Dtmp.Trier_ID());
    else if (ui->comboBox->currentText()=="Par Nom")
        ui->tableView->setModel(Dtmp.Trier_NOM());
    else ui->tableView->setModel(Dtmp.Trier());
}

void MainWindow::on_le_chercher_textChanged(const QString &arg1)
{
    QString recherche = ui->le_chercher->text();
    if(recherche.length()!=0)
       ui->tableView->setModel(Dtmp.rechercher(recherche));
    else
    {
       ui->tableView->setModel(Dtmp.afficher());
    }
}

void MainWindow::on_PDF_clicked()
{
    QString strStream;
                       QTextStream out(&strStream);

                       const int rowCount = ui->tableView->model()->rowCount();
                       const int columnCount = ui->tableView->model()->columnCount();
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
                           if (!ui->tableView->isColumnHidden(column))
                               out << QString("<th>%1</th>").arg(ui->tableView->model()->headerData(column, Qt::Horizontal).toString());
                       out << "</tr></thead>\n";

                       // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tableView->isColumnHidden(column)) {
                                   QString data =ui->tableView->model()->data(ui->tableView->model()->index(row, column)).toString().simplified();
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

void MainWindow::on_stats_clicked()
{
    statistique s;
        s.exec();
}

void MainWindow::on_sendBtn_clicked()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
       connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


       smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),"Thank you for your support");

       QMessageBox::information(nullptr, QObject::tr("Succès"),
                   QObject::tr("Le mail a été envoyé avec succès.\n"
                               "Cliquer sur Cancel to exit."), QMessageBox::Cancel);
}
