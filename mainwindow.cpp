#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "misc.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(2);
    ui->tableView->setModel(B.afficher());
    ui->lineEdit_CIN_2->setEnabled(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//ajouter
void MainWindow::on_pushButton_3_clicked()
{   bool ok=true;
    QString errormsg="";
    int CIN,age,num;

    QString nom, prenom, adresse, type;

    if(ui->lineEdit_CIN->text().toInt()>99999999 ||ui->lineEdit_CIN->text().toInt()<10000000)
    {
        errormsg= errormsg.append("CIN non valid. ");
    }


    if(ui->lineEdit_Age->text().isEmpty() || ui->lineEdit_Age->text().toInt()<0 || ui->lineEdit_Age->text().toInt()>130 || !is_number(ui->lineEdit_Age->text().toStdString()))
    {

         errormsg= errormsg.append("Age non valid. ");
    }


    if(ui->lineEdit_Name->text().isEmpty() || ui->lineEdit_LastName->text().isEmpty() || has_any_digits(ui->lineEdit_Name->text().toStdString()) || has_any_digits(ui->lineEdit_LastName->text().toStdString()))
    {
        errormsg= errormsg.append("Name or last name non valid.");
    }


    if(ui->lineEdit_Num->text().toInt()>99999999 || ui->lineEdit_Num->text().toInt()<10000000)
    {
        errormsg= errormsg.append("Invalid phone number.");
    }

    if(errormsg!="")
        ok=false;


  CIN=ui->lineEdit_CIN->text().toInt();
    age=ui->lineEdit_Age->text().toInt();
    nom=ui->lineEdit_Name->text();
   prenom=ui->lineEdit_LastName->text();
    adresse=ui->lineEdit_Adress->text();
   type=ui->lineEdit_Type->text();
   num=ui->lineEdit_Num->text().toInt();

ui->label_19->setText(errormsg);
if(ok)
{
    Beneficiaire B(CIN,nom, prenom, age, adresse, type, num);
    B.ajouter();
    ui->tableView->setModel(B.afficher());
}


}

//supprimer
void MainWindow::on_pushButton_4_clicked()
{
int v1;
    QModelIndex index=ui->tableView->selectionModel()->currentIndex();
    QVariant value=index.sibling(index.row(),index.column()).data(); //will get the value of the clicked cell.
    v1=value.toInt();
    Beneficiaire B;
   B.supprimer(v1);
    ui->tableView->setModel(B.afficher());


}

void MainWindow::on_pushButton_7_clicked()
{
// modifier
    bool ok=true;
        QString errormsg="";
    int CIN,age,num;
    QString nom, prenom, adress, type;


        QModelIndex index=ui->tableView->selectionModel()->currentIndex();
        QVariant CIN_string=index.sibling(index.row(),index.column()).data(); //will get the value of the clicked cell.
        CIN=CIN_string.toInt();


        if(ui->lineEdit_Age_2->text().isEmpty() || ui->lineEdit_Age_2->text().toInt()<0 || ui->lineEdit_Age_2->text().toInt()>130 || !is_number(ui->lineEdit_Age_2->text().toStdString()))
        {

             errormsg= errormsg.append("Age non valid. ");
        }


        if(ui->lineEdit_Name_2->text().isEmpty() || ui->lineEdit_LastName_2->text().isEmpty() || has_any_digits(ui->lineEdit_Name_2->text().toStdString()) || has_any_digits(ui->lineEdit_LastName_2->text().toStdString()))
        {
            errormsg= errormsg.append("Name or last name non valid.");
        }


        if(ui->lineEdit_Num_2->text().toInt()>99999999 || ui->lineEdit_Num_2->text().toInt()<10000000)
        {
            errormsg= errormsg.append("Invalid phone number.");
        }

        if(errormsg!="")
            ok=false;

        ui->label_20->setText(errormsg);

    age=ui->lineEdit_Age_2->text().toInt();
    nom=ui->lineEdit_Name_2->text();
   prenom=ui->lineEdit_LastName_2->text();
    adress=ui->lineEdit_Adress_2->text();
   type=ui->lineEdit_Type_2->text();
   num=ui->lineEdit_Num_2->text().toInt();

if(ok)
{
    Beneficiaire B(CIN,nom, prenom, age, adress, type, num);
    B.modifier(CIN,nom, prenom, age, adress, type, num);
    int nextIndex = ui->stackedWidget->currentIndex() - 1;
    if( nextIndex < ui->stackedWidget->count())
           ui->stackedWidget->setCurrentIndex(nextIndex);
}




}

void MainWindow::on_pushButton_5_clicked()
{
    QModelIndex index=ui->tableView->selectionModel()->currentIndex();
    QVariant CIN_string=index.sibling(index.row(),index.column()).data(); //will get the value of the clicked cell
    if(!CIN_string.isNull())
    {
                int nextIndex = ui->stackedWidget->currentIndex() + 1;
                if( nextIndex < ui->stackedWidget->count())
                       ui->stackedWidget->setCurrentIndex(nextIndex);
    }
}
