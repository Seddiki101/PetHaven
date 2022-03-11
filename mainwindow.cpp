#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "animal.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_Age->setValidator(new QIntValidator(0,1000,this));

    QRegExp rx("^[a-zA-Z]{1,20}$");
    QValidator *validator = new QRegExpValidator(rx, this);
    ui->le_Nom->setValidator(validator);
    ui->le_Race->setValidator(validator);
    ui->le_Espece->setValidator(validator);

    ui->tableView->setModel(A.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_Refresh_clicked()
{
    Animal A;
    A.afficher();
}


void MainWindow::on_btn_Add_clicked()
{
    int Age=ui->le_Age->text().toUInt();
    QString Nom=ui->le_Nom->text();
    QString Espece=ui->le_Espece->text();
    QString Race=ui->le_Race->text();
    QDate Date=ui->le_Date_arr->date();

    Animal A(Age, 0, Nom, Espece, Race, Date);
    bool test=A.ajouter();
    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText ("Ajout avec succes.");
        ui->tableView->setModel (A.afficher());
    }
}

void MainWindow::on_btn_Update_clicked()
{
    int id;
    QModelIndex index=ui->tableView->selectionModel()->currentIndex();
    QVariant value=index.sibling(index.row(),index.column()).data();
    id=value.toUInt();

    int Status=ui->status->isChecked();
    int Age=ui->le_Age->text().toUInt();
    QString Nom=ui->le_Nom->text();
    QString Espece=ui->le_Espece->text();
    QString Race=ui->le_Race->text();
    QDate Date=ui->le_Date_arr->date();

    Animal A(Age, Status, Nom, Espece, Race, Date);
    bool test=A.modifier(id);
    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText ("Modification avec succes.");
        ui->tableView->setModel (A.afficher());
    }
}


void MainWindow::on_btn_Delete_clicked()
{
    Animal A1;

    int id;
    QModelIndex index=ui->tableView->selectionModel()->currentIndex();
    QVariant value=index.sibling(index.row(),index.column()).data();
    id=value.toUInt();

    bool test = A1.supprimer(id);
    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText("suppression avec succes.");
        ui->tableView->setModel(A.afficher());
    }
}

void MainWindow::on_btn_Search_clicked()
{
    Animal A;
    A.afficher();
}

void MainWindow::on_btn_Sort_clicked()
{
    Animal A;
    A.afficher();
}

void MainWindow::on_btn_PDF_clicked()
{
    Animal A;
    A.afficher();
}

//void MainWindow::on_pb_afficher_clicked()
//{
//    ui->stackedWidget->setCurrentIndex(1);
//}

//void MainWindow::on_pb_supprimer_clicked()
//{
//    ui->stackedWidget->setCurrentIndex(2);
//}
