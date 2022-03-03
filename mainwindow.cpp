#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>
#include <cstdlib>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableView_2->setModel(pato.afficher());
    ui->tableView_3->setModel(annie.afficher());
    ui->tableView->setModel(dope.afficher());

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
    ui->stackedWidget->setCurrentIndex(2);
}

//ajouter
void MainWindow::on_pushButton_6_clicked()
{
    int idp,ida,ido;
    QDate d=QDate::currentDate();
    ido = 1+ (rand() % 1000);  //

    idp=ui->lineEdit_4->text().toInt();
    ida=ui->lineEdit_5->text().toInt();


    Adoption A(ido,ida,idp,d);
    A.ajouter();
     ui->tableView->setModel(dope.afficher());




    ui->stackedWidget->setCurrentIndex(1);

}

//supprimer
void MainWindow::on_pushButton_7_clicked()
{
    int ido;
    Adoption A;
   ido=ui->lineEdit_6->text().toInt();
   A.supprimer(ido);
    ui->tableView->setModel(dope.afficher());


}

void MainWindow::on_pushButton_3_clicked()
{
    if (ui->radioButton) {
    ui->tableView->setModel(dope.triDates());}


    if (ui->radioButton_2) {
    ui->tableView->setModel(dope.triAlpha());}
}


void MainWindow::on_pushButton_2_clicked()
{
Adoption A;
QString nom=ui->lineEdit_3->text();
ui->tableView->setModel(A.chercher(nom));
}

void MainWindow::on_refresh_clicked()
{
    ui->tableView->setModel(dope.afficher());
}
