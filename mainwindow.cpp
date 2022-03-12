#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "livraison.h"
#include <QMessageBox>
#include <QIntValidator>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(L.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_Refresh_clicked()
{
    Livraison L;
    L.afficher();
}


void MainWindow::on_btn_Add_clicked()
{
    QDate Date=ui->le_Date->date();
    QString Adresse=ui->le_Arrive->text();
    QString Adresse_dep=ui->le_Depart->text();

    Livraison L(Date,Adresse,Adresse_dep);
    bool test=L.ajouter();
    QMessageBox msgBox;
    if(test)
    { msgBox.setText("Ajout avec succes.");
        ui->tableView->setModel(L.afficher());
    }
}

void MainWindow::on_btn_Update_clicked()
{
    int id;
    QModelIndex index=ui->tableView->selectionModel()->currentIndex();
    QVariant value=index.sibling(index.row(),index.column()).data();
    id=value.toUInt();

    QDate Date=ui->le_Date->date();
    QString Adresse=ui->le_Arrive->text();
    QString Adresse_dep=ui->le_Depart->text();

    Livraison L(Date,Adresse,Adresse_dep);
    bool test=L.modifier(id);
    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText ("Modification avec succes.");
        ui->tableView->setModel (L.afficher());
    }
}


void MainWindow::on_btn_Delete_clicked()
{
    Livraison L1;

    int id;
    QModelIndex index=ui->tableView->selectionModel()->currentIndex();
    QVariant value=index.sibling(index.row(),index.column()).data();
    id=value.toUInt();

    bool test = L1.supprimer(id);
    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText("suppression avec succes.");
        ui->tableView->setModel(L.afficher());
    }
}

void MainWindow::on_btn_Search_clicked()
{
    Livraison L;
    L.afficher();
}

void MainWindow::on_btn_Sort_clicked()
{
    Livraison L;
    L.afficher();
}

void MainWindow::on_btn_PDF_clicked()
{
    Livraison L;
    L.afficher();
}

//void MainWindow::on_pb_afficher_clicked()
//{
//    ui->stackedWidget->setCurrentIndex(1);
//}

//void MainWindow::on_pb_supprimer_clicked()
//{
//    ui->stackedWidget->setCurrentIndex(2);
//}
