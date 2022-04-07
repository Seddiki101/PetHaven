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

void MainWindow::on_pushButton_3_clicked()
{
    if(ui->radioButton)
    {
        ui->tableView->setModel(E.triAlpha());
    }
    if(ui->radioButton_2)
    {
        ui->tableView->setModel(E.triLogin());
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    Employe E1;
    QString recherche = ui->le_recherche->text();
    ui->tableView->setModel(E1.chercherID(recherche));
}

void MainWindow::on_le_recherche_textChanged(const QString &arg1)
{
    Employe E1;
    QString recherche = ui->le_recherche->text();
    ui->tableView->setModel(E1.chercherNom(recherche));
}

void MainWindow::on_refresh_clicked()
{

    ui->stackedWidget->setStyleSheet("background-color: white ;");
    ui->centralwidget->setStyleSheet("background-color: white ;");
    ui->pushButton_5->setStyleSheet("background-color: black ;");
    ui->pushButton_2->setStyleSheet("background-color: black ;");
    ui->pushButton_7->setStyleSheet("background-color: black ;");
    ui->pushButton_8->setStyleSheet("background-color: black ;");
    ui->pushButton_3->setStyleSheet("background-color: black ;");
    ui->pushButton_2->setStyleSheet("background-color: black ;");
    ui->pushButton_4->setStyleSheet("background-color: black ;");
    ui->pushButton_9->setStyleSheet("background-color: black ;");
    ui->refresh->setStyleSheet("background-color: black ;");
    ui->refresh_2->setStyleSheet("background-color: black ;");
    ui->le_ID->setStyleSheet("background-color: black ;");
    ui->le_Mdp->setStyleSheet("background-color: black ;");
    ui->le_Nom->setStyleSheet("background-color: black ;");
    ui->le_Email->setStyleSheet("background-color: black ;");
    ui->le_Login->setStyleSheet("background-color: black ;");
    ui->le_Prenom->setStyleSheet("background-color: black ;");
    ui->le_recherche->setStyleSheet("background-color: black ;");
    ui->textEdit->setStyleSheet("background-color: black ;");
    ui->label_3->setStyleSheet("color: black ;");
    ui->label_4->setStyleSheet("color: black ;");
    ui->label_5->setStyleSheet("color: black ;");
    ui->label_6->setStyleSheet("color: black ;");
    ui->label_7->setStyleSheet("color: black ;");
    ui->label_8->setStyleSheet("color: black ;");
    ui->label_9->setStyleSheet("color: black ;");
    ui->label_14->setStyleSheet("color: black ;");
    ui->radioButton->setStyleSheet("color: black;");
    ui->radioButton_2->setStyleSheet("color: black;");
    ui->stackedWidget->show();




}

void MainWindow::on_pushButton_4_clicked()
{
    Employe E1;
    E.pdf(ui->tableView);
}

void MainWindow::on_refresh_2_clicked()
{
    ui->stackedWidget->setStyleSheet("");
    ui->centralwidget->setStyleSheet("");
    ui->pushButton_5->setStyleSheet("");
    ui->pushButton_2->setStyleSheet("");
    ui->pushButton_7->setStyleSheet("");
    ui->pushButton_8->setStyleSheet("");
    ui->pushButton_3->setStyleSheet("");
    ui->pushButton_2->setStyleSheet("");
    ui->pushButton_4->setStyleSheet("");
    ui->pushButton_9->setStyleSheet("");
    ui->refresh->setStyleSheet("");
    ui->refresh_2->setStyleSheet("");
    ui->le_ID->setStyleSheet("");
    ui->le_Mdp->setStyleSheet("");
    ui->le_Nom->setStyleSheet("");
    ui->le_Email->setStyleSheet("");
    ui->le_Login->setStyleSheet("");
    ui->le_Prenom->setStyleSheet("");
    ui->le_recherche->setStyleSheet("");
    ui->textEdit->setStyleSheet("");
    ui->label->setStyleSheet("");
    ui->label_3->setStyleSheet("");
    ui->label_4->setStyleSheet("");
    ui->label_5->setStyleSheet("");
    ui->label_6->setStyleSheet("");
    ui->label_7->setStyleSheet("");
    ui->label_8->setStyleSheet("");
    ui->label_9->setStyleSheet("");
    ui->label_14->setStyleSheet("");
    ui->radioButton->setStyleSheet("");
    ui->radioButton_2->setStyleSheet("");
    ui->stackedWidget->show();
}

void MainWindow::on_pushButton_9_clicked()
{
    Employe E1;
    int id;
        QModelIndex index=ui->tableView->selectionModel()->currentIndex();
        QVariant value=index.sibling(index.row(),index.column()).data(); //will get the value of the clicked cell.
        id=value.toUInt();

    QString appreciations=ui->textEdit->toPlainText();
    bool test=E1.appreciation(id);
    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText("suppression avec succes.");
        ui->tableView->setModel(E.afficher());
}
}
