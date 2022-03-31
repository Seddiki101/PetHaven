#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "livraison.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QValidator>


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
    ui->tableView->setModel(L.afficher());
}


void MainWindow::on_btn_Add_clicked()
{
    QDateTime DateTime=ui->le_Date->dateTime();
    QString Adresse=ui->le_Arrive->text();
    QString Adresse_dep=ui->le_Depart->text();

    Livraison L(DateTime,Adresse,Adresse_dep);
    if (L.controlA() || L.controlAD())
    {
        if (L.controlA())
        {
            ui->err2->clear();
            ui->err2->setText("Champ Obligatoire");
            ui->le_Arrive->clear();
        }

        if (L.controlAD())
        {
            ui->err1->clear();
            ui->err1->setText("Champ Obligatoire");
            ui->le_Depart->clear();
        }

    }
    bool test=L.ajouter();
    QMessageBox msgBox;
    if(test)
    { msgBox.setText("Ajout avec succes.");
        ui->tableView->setModel(L.afficher());
    }

    QRegularExpression reg("^([0-9]{1,5}\\s[a-zA-Z0-9\\s]{1,99})$");
    QRegularExpressionValidator validator(reg, 0);

    int pos = 0;
    QString temp = ui->le_Depart->text();
    validator.validate (temp, pos);
}

void MainWindow::on_btn_Update_clicked()
{
    int id;
    QModelIndex index=ui->tableView->selectionModel()->currentIndex();
    QVariant value=index.sibling(index.row(),index.column()).data();
    id=value.toUInt();

    QDateTime DateTime=ui->le_Date->dateTime();
    QString Adresse=ui->le_Arrive->text();
    QString Adresse_dep=ui->le_Depart->text();

    Livraison L(DateTime,Adresse,Adresse_dep);
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



void MainWindow::on_btn_Sort_clicked()
{
    Livraison L;
    if (ui->sort_name->isChecked())
    {
        ui->tableView->setModel(L.triAlpha());
    }

    if (ui->sort_date->isChecked())
    {
        ui->tableView->setModel(L.triDate());
    }
}

void MainWindow::on_btn_PDF_clicked()
{
    Livraison L;
    L.generatePdf(ui->tableView);
}

void MainWindow::on_btn_Search_clicked()
{
    Livraison L;
    QString recherche=ui->le_Search->text();
    ui->tableView->setModel(L.chercher(recherche));
}

void MainWindow::on_le_Search_textChanged(const QString &arg1)
{
    Livraison L;
    QString recherche=ui->le_Search->text();
    ui->tableView->setModel(L.search(recherche));

}


//void MainWindow::on_pb_afficher_clicked()
//{
//    ui->stackedWidget->setCurrentIndex(1);
//}

//void MainWindow::on_pb_supprimer_clicked()
//{
//    ui->stackedWidget->setCurrentIndex(2);
//}

