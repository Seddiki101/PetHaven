#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "animal.h"
#include <QMessageBox>
#include <QIntValidator>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_Age->setValidator(new QIntValidator(0,9999999,this));
    ui->tab_employe->setModel(A.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_ajouter_clicked()
{
    int Age=ui->le_Age->text().toUInt();
    QString Nom=ui->le_Nom->text();
    QString Espece=ui->le_Espece->text();
    QString Race=ui->le_Race->text();
    QDate Date=ui->le_Date->date();

    Animal A(Age, Nom, Espece, Race, Date);
    bool test=A.ajouter();
    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText ("Ajout avec succes.");
        ui->tab_employe->setModel (A.afficher());
    }
}


void MainWindow::on_pushButton_clicked()
{
    Animal A1;
    int id = ui->le_id_supp->text().toInt();
    bool test = A1.supprimer(id);
    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText("suppression avec succes.");
        ui->tab_employe->setModel(A.afficher());
    }
}

void MainWindow::on_pb_ajouter_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pb_ajouter_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
