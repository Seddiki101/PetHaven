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

    int Age = ui->le_Age->text().toUInt();
    QString Nom = ui->le_Nom->text();
    QString Espece = ui->le_Espece->text();
    QString Race = ui->le_Race->text();
    QDate Date = ui->le_Date_arr->date();

    Animal A(Age, 0, Nom, Espece, Race, Date);


    if ( ! (A.Empty(Nom) || A.Empty(Espece) || A.Empty(Race)) ) {
        QMessageBox msgBox;
        if(A.ajouter())
        {
            msgBox.setText ("Ajout avec succes.");
            ui->tableView->setModel (A.afficher());
            ui->list_historic->addItem(A.historic("Animal '" + Nom + "' added with success."));
        }
        else
        {
            ui->list_historic->addItem(A.historic("Failed to add."));
        }
    }
    else
    {
        ui->list_historic->addItem(A.historic("Failed to add, missing arguments."));
    }
}

bool test(QVariant test) {
    return test.isNull();
}

void MainWindow::on_btn_Update_clicked()
{
    QModelIndex index=ui->tableView->selectionModel()->currentIndex();
    QVariant value=index.sibling(index.row(), 0).data();
    QVariant tempNom = index.sibling(index.row(), 1).data();   // gather NOM of the selected row

    int Status = ui->status->isChecked();
    int Age = ui->le_Age->text().toUInt();
    QString Nom = ui->le_Nom->text();
    QString Espece = ui->le_Espece->text();
    QString Race = ui->le_Race->text();
    QDate Date = ui->le_Date_arr->date();

    Animal A(Age, Status, Nom, Espece, Race, Date);
    QMessageBox msgBox;

    if ( ! (A.Empty(Nom) || A.Empty(Espece) || A.Empty(Race) || value.isNull() ) ) {
        if(A.modifier(value.toUInt()))
        {
            msgBox.setText ("Modification avec succes.");
            ui->tableView->setModel (A.afficher());

            if (Nom != tempNom.toString())
            {
                ui->list_historic->addItem(A.historic("Animal '" + tempNom.toString() + "' modified to '"+ Nom +"' with success."));
            }
            else
            {
                ui->list_historic->addItem(A.historic("Animal '" + Nom + "' modified with success."));
            }
        }
        else
        {
            ui->list_historic->addItem(A.historic("Failed to modify."));
        }
    }
    else
    {
        ui->list_historic->addItem(A.historic("Failed to update, missing arguments or nothing selected."));
    }
}


void MainWindow::on_btn_Delete_clicked()
{
    Animal A;

    QModelIndex index = ui->tableView->selectionModel()->currentIndex();
    QVariant value = index.sibling(index.row(), 0).data();      // gather ID  of the selected row
    QVariant tempName = index.sibling(index.row(), 1).data();   // gather NOM of the selected row


    QMessageBox msgBox;
    if(A.supprimer(value.toUInt()) && !value.isNull())
    {
        msgBox.setText("suppression avec succes.");
        ui->tableView->setModel(A.afficher());
        ui->list_historic->addItem(A.historic("Deleted Animal '" + tempName.toString() + "' with success."));
    }
    else
    {
        ui->list_historic->addItem(A.historic("Failed to delete, nothing selected."));
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

void MainWindow::on_btn_Upload_clicked()
{
    Animal A;

    QString link = ui->le_Image->text();

//    link = "..\\Gestion Animal\\res\\dededepression.jpg";
//    link = "..\\Gestion Animal\\res\\dededepression.png";

    QPixmap pixmap(link);
    QIcon ButtonIcon(pixmap);
    ui->btn_Upload->setIcon(ButtonIcon);

    ui->btn_Upload->resize(pixmap.rect().size());
    ui->btn_Upload->setIconSize(pixmap.rect().size());
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

void MainWindow::on_Black_clicked()
{
    ui->stackedWidget->setStyleSheet("");
    ui->centralwidget->setStyleSheet("");

    ui->Title->setStyleSheet("");
    ui->list_title->setStyleSheet("");
    ui->list_historic->setStyleSheet("");
    ui->btn_Sort->setStyleSheet("");
    ui->btn_Add->setStyleSheet("");
    ui->btn_Update->setStyleSheet("");
    ui->btn_Delete->setStyleSheet("");
    ui->btn_PDF->setStyleSheet("");
    ui->btn_Refresh->setStyleSheet("");
    ui->btn_Upload->setStyleSheet("");

    ui->White->setStyleSheet("");
    ui->Black->setStyleSheet("");

    ui->le_Search->setStyleSheet("");
    ui->le_Nom->setStyleSheet("");
    ui->le_Race->setStyleSheet("");
    ui->le_Espece->setStyleSheet("");
    ui->le_Age->setStyleSheet("");
    ui->le_Date_arr->setStyleSheet("");
    ui->le_Image->setStyleSheet("");

    ui->label_age->setStyleSheet("");
    ui->label_nom->setStyleSheet("");
    ui->label_race->setStyleSheet("");
    ui->label_espece->setStyleSheet("");
    ui->label_date_arr->setStyleSheet("");
    ui->label_historic->setStyleSheet("");
    ui->status->setStyleSheet("");

    ui->sort_date->setStyleSheet("");
    ui->sort_name->setStyleSheet("");

    ui->stackedWidget->show();
    ui->list_historic->addItem(A.historic("Switched to dark mode."));
}

void MainWindow::on_White_clicked()
{
    ui->stackedWidget->setStyleSheet("background-color: white ;");
    ui->centralwidget->setStyleSheet("background-color: white ;");

    ui->Title->setStyleSheet("color: black ;");
    ui->list_title->setStyleSheet("color: black ;");
    ui->list_historic->setStyleSheet("background-color: black; alternate-background-color: black;");
    ui->btn_Sort->setStyleSheet("background-color: black ;");
    ui->btn_Add->setStyleSheet("background-color: black ;");
    ui->btn_Update->setStyleSheet("background-color: black ;");
    ui->btn_Delete->setStyleSheet("background-color: black ;");
    ui->btn_PDF->setStyleSheet("background-color: black ;");
    ui->btn_Refresh->setStyleSheet("background-color: black ;");
    ui->btn_Upload->setStyleSheet("background-color: black ;");

    ui->White->setStyleSheet("background-color: black ;");
    ui->Black->setStyleSheet("background-color: black ;");

    ui->le_Search->setStyleSheet("background-color: black ;");
    ui->le_Nom->setStyleSheet("background-color: black ;");
    ui->le_Race->setStyleSheet("background-color: black ;");
    ui->le_Espece->setStyleSheet("background-color: black ;");
    ui->le_Age->setStyleSheet("background-color: black ;");
    ui->le_Date_arr->setStyleSheet("background-color: black ;");
    ui->le_Image->setStyleSheet("background-color: black ;");

    ui->label_age->setStyleSheet("color: black ;");
    ui->label_nom->setStyleSheet("color: black ;");
    ui->label_race->setStyleSheet("color: black ;");
    ui->label_espece->setStyleSheet("color: black ;");
    ui->label_date_arr->setStyleSheet("color: black ;");
    ui->label_historic->setStyleSheet("color: black ;");
    ui->status->setStyleSheet("color: black ;");

    ui->sort_date->setStyleSheet("color: black ;");
    ui->sort_name->setStyleSheet("color: black ; ");

    ui->stackedWidget->show();
    ui->list_historic->addItem(A.historic("Switched to white mode."));
}
