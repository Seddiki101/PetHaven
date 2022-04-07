#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "misc.h"
#include "statistique.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(2);
    ui->tableView->setModel(B.afficher("",0));

    ui->lineEdit_CIN_2->setEnabled(0);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(notifs()));
    timer->start(10);

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
   QDateTime date = QDateTime::currentDateTime();

ui->label_19->setText(errormsg);
if(ok)
{
    Beneficiaire B(CIN,nom, prenom, age, adresse, type, num, date);
    B.ajouter();
    ui->tableView->setModel(B.afficher("",0));
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
    ui->tableView->setModel(B.afficher("",0));


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
   QDateTime date=date.currentDateTime();

if(ok)
{
    Beneficiaire B(CIN,nom, prenom, age, adress, type, num, date);
    B.modifier(CIN,nom, prenom, age, adress, type, num);
    int nextIndex = ui->stackedWidget->currentIndex() - 1;
    if( nextIndex < ui->stackedWidget->count())
           ui->stackedWidget->setCurrentIndex(nextIndex);
}




}
//go to modifier
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

//search
void MainWindow::on_lineEdit_search_textChanged(const QString &arg1)
{
    Beneficiaire B;

    QString search = ui->lineEdit_search->text();
     ui->tableView->setModel(B.afficher(search,0));
}
//tri
void MainWindow::on_pushButton_clicked()
{
    if (ui->radioButton) {
    ui->tableView->setModel(B.afficher("",1));}


    if (ui->radioButton_2) {
    ui->tableView->setModel(B.afficher("",2));}


}
//export pdf
void MainWindow::on_pushButton_6_clicked()
{
    Beneficiaire B;
    B.exportPDF(ui->tableView);
}

void MainWindow::on_pushButton_8_clicked()
{
    statistique s;
    s.setModal(true);
    s.exec();
}
//notifs
void MainWindow::notifs()
{QString c1,c2,c3;
    QStringList List;

    QSqlQuery query;
    query.prepare("select * from LOGS");
    while(query.next())
    {
    c1 = query.value(0).toString();
    c2 = query.value(1).toString();
    c3 = query.value(2).toString();
    c1.append(": ");
    c1.append(c2);
    c1.append(" has ");
    c1.append(c3);
    c1.append("an entry.");
    List << c1;
    ui->listWidget->addItem("bazoula");
    }


            //QSqlQueryModel * model=new QSqlQueryModel();
        //"select COUNT(*) from LOGS where DATEOP > SYSDATETIME()"
            //model->setQuery("select * from LOGS where DATEOP > SYSDATETIME()" )	;

            //QString col1 = model->data(model->index(i,1));
            // ui->listView->setModel(model);

}



void MainWindow::on_pushButton_16_clicked()
{
    QString c1,c2,c3;
        QStringList List;

        QSqlQuery query;
        query.prepare("select * from LOGS WHERE DATEOP < SYSDATE");
        query.exec();
        while(query.next())
        {
        c1 = query.value(0).toString();
        c2 = query.value(1).toString();
        c3 = query.value(2).toString();
        c1.append(": ");
        c1.append(c2);
        c1.append(" has ");
        c1.append(c3);
        c1.append("an entry.");

        ui->listWidget->addItem(c1);
        }
}
