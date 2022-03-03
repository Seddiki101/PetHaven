#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(B.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_3_clicked()
{
    int CIN,age;
    QString nom, prenom, adresse, type;

    CIN=ui->lineEdit_CIN->text().toInt();
    age=ui->lineEdit_Age->text().toInt();
    nom=ui->lineEdit_Name->text();
   prenom=ui->lineEdit_LastName->text();
    adresse=ui->lineEdit_Adress->text();
   type=ui->lineEdit_Type->text();


    Beneficiaire B(CIN,nom, prenom, age, adresse, type);
    B.ajouter();
     ui->tableView->setModel(B.afficher());
}

//supprimer
void MainWindow::on_pushButton_4_clicked()
{
    int CIN_search;
    Beneficiaire B;
   CIN_search=ui->lineEdit_5->text().toInt();
   B.supprimer(CIN_search);
    ui->tableView->setModel(B.afficher());


}
