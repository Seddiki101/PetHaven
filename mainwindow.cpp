#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "animal.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_Age->setValidator(new QIntValidator(0,1000,this));

    QRegExp reg("^[a-zA-Z]{1,20}$");
    QValidator *validator = new QRegExpValidator(reg, this);

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
    ui->tableView->setModel (A.afficher());
}


void MainWindow::on_btn_Add_clicked()
{

    int Age=ui->le_Age->text().toUInt();
    QString Nom=ui->le_Nom->text();
    QString Espece=ui->le_Espece->text();
    QString Race=ui->le_Race->text();
    QDate Date=ui->le_Date_arr->date();

    Animal A(Age, 0, Nom, Espece, Race, Date);

    if ( ! (A.Empty(Nom) || A.Empty(Espece) || A.Empty(Race)) ) {
        bool test=A.ajouter();
        QMessageBox msgBox;
        if(test)
        {
            msgBox.setText ("Ajout avec succes.");
            ui->tableView->setModel (A.afficher());
        }
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
    QModelIndex index = ui->tableView->selectionModel()->currentIndex();
    QVariant value = index.sibling(index.row(), index.column()).data();
    id = value.toUInt();

    bool test = A1.supprimer(id);
    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText("suppression avec succes.");
        ui->tableView->setModel(A.afficher());
    }
}

void MainWindow::on_btn_Sort_clicked()
{
    Animal A;

    if (ui->sort_name->isChecked()) {
        ui->tableView->setModel(A.sortName());
    }
    else if (ui->sort_date->isChecked()) {
        ui->tableView->setModel(A.sortDates());
    }
    else {
        ui->tableView->setModel(A.afficher());
    }

}

void MainWindow::on_btn_PDF_clicked()
{
    Animal A;
    A.generatePdf(ui->tableView);
}


void MainWindow::on_le_Search_textChanged()
{
    Animal A;
    QString research = ui->le_Search->text();
    ui->tableView->setModel(A.searchName(research));
}

void MainWindow::on_btn_Search_clicked()
{
    Animal A;
    QString research = ui->le_Search->text();
    ui->tableView->setModel(A.searchName(research));
}



void MainWindow::on_Black_clicked()
{
    ui->stackedWidget->setStyleSheet("");
    ui->centralwidget->setStyleSheet("");

    ui->Title->setStyleSheet("");
    ui->list_title->setStyleSheet("");
    ui->btn_Search->setStyleSheet("");
    ui->btn_Sort->setStyleSheet("");
    ui->btn_Add->setStyleSheet("");
    ui->btn_Update->setStyleSheet("");
    ui->btn_Delete->setStyleSheet("");
    ui->btn_PDF->setStyleSheet("");
    ui->btn_Refresh->setStyleSheet("");

    ui->White->setStyleSheet("");
    ui->Black->setStyleSheet("");

    ui->le_Search->setStyleSheet("");
    ui->le_Nom->setStyleSheet("");
    ui->le_Race->setStyleSheet("");
    ui->le_Espece->setStyleSheet("");
    ui->le_Age->setStyleSheet("");
    ui->le_Date_arr->setStyleSheet("");

    ui->label_age->setStyleSheet("");
    ui->label_nom->setStyleSheet("");
    ui->label_race->setStyleSheet("");
    ui->label_espece->setStyleSheet("");
    ui->label_date_arr->setStyleSheet("");
    ui->status->setStyleSheet("");

    ui->sort_date->setStyleSheet("");
    ui->sort_name->setStyleSheet("");

    ui->stackedWidget->show();
}

void MainWindow::on_White_clicked()
{
    ui->stackedWidget->setStyleSheet("background-color: white ;");
    ui->centralwidget->setStyleSheet("background-color: white ;");

    ui->Title->setStyleSheet("color: black ;");
    ui->list_title->setStyleSheet("color: black ;");
    ui->btn_Search->setStyleSheet("background-color: black ;");
    ui->btn_Sort->setStyleSheet("background-color: black ;");
    ui->btn_Add->setStyleSheet("background-color: black ;");
    ui->btn_Update->setStyleSheet("background-color: black ;");
    ui->btn_Delete->setStyleSheet("background-color: black ;");
    ui->btn_PDF->setStyleSheet("background-color: black ;");
    ui->btn_Refresh->setStyleSheet("background-color: black ;");

    ui->White->setStyleSheet("background-color: black ;");
    ui->Black->setStyleSheet("background-color: black ;");

    ui->le_Search->setStyleSheet("background-color: black ;");
    ui->le_Nom->setStyleSheet("background-color: black ;");
    ui->le_Race->setStyleSheet("background-color: black ;");
    ui->le_Espece->setStyleSheet("background-color: black ;");
    ui->le_Age->setStyleSheet("background-color: black ;");
    ui->le_Date_arr->setStyleSheet("background-color: black ;");

    ui->label_age->setStyleSheet("color: black ;");
    ui->label_nom->setStyleSheet("color: black ;");
    ui->label_race->setStyleSheet("color: black ;");
    ui->label_espece->setStyleSheet("color: black ;");
    ui->label_date_arr->setStyleSheet("color: black ;");
    ui->status->setStyleSheet("color: black ;");

    ui->sort_date->setStyleSheet("color: black ;");
    ui->sort_name->setStyleSheet("color: black ;");

    ui->stackedWidget->show();
}
