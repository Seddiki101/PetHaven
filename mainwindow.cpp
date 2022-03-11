#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dons.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QValidator>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QIntValidator ex;
    ui->setupUi(this);
    ui->le_id->setValidator(new QIntValidator(0, 99999999,this));
    ui->le_id_Supp->setValidator(new QIntValidator(0, 99999999,this));
    ui->le_id_Modif->setValidator(new QIntValidator(0, 99999999,this));
    ui->le_montant->setValidator(new QIntValidator(0, 99999999,this));
    ui->le_montant_Modif->setValidator(new QIntValidator(0, 99999999,this));
    ui->tableView->setModel(Dtmp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_Confirmer_clicked()
{
    int id=ui->le_id->text().toInt();
    QString nom=ui->le_nom_don->text();
    QString adresse=ui->le_adresse->text();
    QString email=ui->le_email->text();
    int montant=ui->le_montant->text().toInt();
    QDate date=ui->de->date();
    Dons Dtmp(id,nom,adresse,email,date,montant);
    if ((Dtmp.Verif_email()) || (Dtmp.Verif_nom()) || (Dtmp.Verif_adresse()) || (Dtmp.Verif_montant_z()) || (Dtmp.Verif_id()))
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
        if(Dtmp.Verif_id())
        {ui->email_verif->clear();
            ui->email_verif->setText("L'ID doit être different de 0");
        ui->le_id->clear();}
}
   else{
ui->email_verif->clear();
    bool test=Dtmp.ajouter();
    ui->le_id->clear();
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
     QDate date_m = ui->de_Modif->date();
     Dons Dtmp(id,nom,adresse,email,date_m,montant);
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
    bool test = Dtmp.modifier();
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
    ui->le_id->clear();
    ui->le_email->clear();
    ui->le_adresse->clear();
    ui->le_montant->clear();
    ui->le_nom_don->clear();
    ui->de->clear();
}



void MainWindow::on_Annuler_clicked()
{
    ui->le_id_Modif->clear();
    ui->le_email_Modif->clear();
    ui->le_adresse_Modif->clear();
    ui->le_montant_Modif->clear();
    ui->le_nom_Modif->clear();
    ui->de_Modif->clear();
}
