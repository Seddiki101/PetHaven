#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_ID->setValidator(new QIntValidator(0,9999999,this));
    ui->tableView->setModel(E.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_pushButton_clicked()
{
      ui->stackedWidget->setCurrentIndex(1);
}





void MainWindow::on_pushButton_5_clicked()
{
    int ID=ui->le_ID->text().toUInt();
    QString Nom=ui->le_Nom->text();
    QString Prenom=ui->le_Prenom->text();
    QString Email=ui->le_Email->text();
    QString Login=ui->le_Login->text();
    QString Mdp=ui->le_Mdp->text();
    Employe E(ID,Nom,Prenom,Email,Login,Mdp);

       if(E.Verif_Email())
           { ui->email_verif->clear();
        ui->email_verif->setText("Email doit être valide : @exemple.ex");
        ui->le_Email->clear();}
       ui->email_verif->clear();
    bool test=E.ajouter();
    QMessageBox msgBox;
    if(test)
    { msgBox.setText("Ajout avec succes.");
    ui->tableView->setModel(E.afficher());
}
}





void MainWindow::on_pushButton_7_clicked()
{
    Employe E1;
    int id;
        QModelIndex index=ui->tableView->selectionModel()->currentIndex();
        QVariant value=index.sibling(index.row(),index.column()).data(); //will get the value of the clicked cell.
        id=value.toUInt();


    bool test=E1.supprimer(id);
    QMessageBox msgBox;
    if(test)
    {msgBox.setText("suppression avec succes.");
        ui->tableView->setModel(E.afficher());
}
}

void MainWindow::on_pushButton_8_clicked()
{
    int id;
        QModelIndex index=ui->tableView->selectionModel()->currentIndex();
        QVariant value=index.sibling(index.row(),index.column()).data(); //will get the value of the clicked cell.
        id=value.toUInt();

        QString Nom=ui->le_Nom->text();
        QString Prenom=ui->le_Prenom->text();
        QString Email=ui->le_Email->text();
        QString Login=ui->le_Login->text();
        QString Mdp=ui->le_Mdp->text();
        Employe E(id,Nom,Prenom,Email,Login,Mdp);
        bool test=E.modifier(id);
        QMessageBox msgBox;
        if(test)
        {
            msgBox.setText ("Modification avec succes.");
            ui->tableView->setModel (E.afficher());
        }
}
