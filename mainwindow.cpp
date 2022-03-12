#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>
#include <cstdlib>
#include "popup.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //popUp = new PopUp();

    //ctrl de saisi
    ui->lineEdit_4->setValidator(new QIntValidator(0,999999,this)); //id animal
    ui->lineEdit_5->setValidator(new QIntValidator(0,999999,this));   // id ajout beneficiaire
    ui->lineEdit_7->setValidator(new QIntValidator(0,999999,this));   // id ajout modif
    ui->lineEdit_8->setValidator(new QIntValidator(0,999999,this));   // id modif animal
    ui->lineEdit_9->setValidator(new QIntValidator(0,999999,this));   // id modif beneficiaire


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
    ido = 1+ (rand() % 1000);  // this is removed when auto increment is fixed

    idp=ui->lineEdit_4->text().toInt();
    ida=ui->lineEdit_5->text().toInt();


    Adoption A(ido,ida,idp,d);
    bool test=A.ajouter();
     ui->tableView->setModel(dope.afficher());




    ui->stackedWidget->setCurrentIndex(1);
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    if(test) { //popUp->setPopupText("Ajout avec succes");} else {popUp->setPopupText("Ajout Failed");
        QMessageBox::information(nullptr, QObject::tr("database is open"),
        QObject::tr("Ajout avec success.\n"
        "Click Cancel to exit."), QMessageBox::Cancel);
    } else {

        QMessageBox::information(nullptr, QObject::tr("database is open"),
        QObject::tr("erreur :Existe deja.\n"
        "Click Cancel to exit."), QMessageBox::Cancel);
    }

}

//supprimer
void MainWindow::on_pushButton_7_clicked()
{

    int id;
        QModelIndex index=ui->tableView->selectionModel()->currentIndex();
        QVariant value=index.sibling(index.row(),index.column()).data(); //will get the value of the clicked cell.
        id=value.toInt();


    int ido;
    Adoption A;
   ido=ui->lineEdit_6->text().toInt();
   A.supprimer(id);
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
//QString nom=ui->lineEdit_3->text();
//ui->tableView->setModel(A.chercher(nom));

QString recherche = ui->lineEdit_3->text();
 ui->tableView->setModel(A.rechercher(recherche));


}

void MainWindow::on_refresh_clicked()
{
    ui->tableView->setModel(dope.afficher());
}

void MainWindow::on_pushButton_9_clicked()
{
// modifier
    Adoption A;
    int ida,idp,ido;
    ido=ui->lineEdit_7->text().toInt();
    idp=ui->lineEdit_8->text().toInt();
    ida=ui->lineEdit_9->text().toInt();

bool test=A.modifier(ido,idp,ida);

ui->stackedWidget->setCurrentIndex(1);
if(test) {
    QMessageBox::information(nullptr, QObject::tr("database is open"),
    QObject::tr("Modification avec success.\n"
    "Click Cancel to exit."), QMessageBox::Cancel);

 //popUp->setPopupText("Modification avec succes");
}
else {
    QMessageBox::information(nullptr, QObject::tr("database is open"),
    QObject::tr("Ideentifiant non valide.\n"
    "Click Cancel to exit."), QMessageBox::Cancel);


}
}

void MainWindow::on_pushButton_8_clicked()
{
ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_adocsv_clicked()
{
    Adoption A;
    A.genereExcel(ui->tableView);
}

void MainWindow::on_adopdf_clicked()
{
 Adoption A;
 A.generatePdf(ui->tableView);
}
