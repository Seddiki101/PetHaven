#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int ret = Ar.connect_arduino();             // Start the connexion with Arduino
    switch (ret) {
        case 0:
            qDebug() << "Arduino avaible and connected to : " << Ar.getarduino_port_name();
        break;
        case 1:
            qDebug() << "Arduino avaible but not connected to : " << Ar.getarduino_port_name();
        break;
        case -1:
            qDebug() << "Arduino is not doing the worky worky.";
        break;
    }

    // Starts the slot (or function) 'update_label' after receiving 'readyRead' signal (meaning the arduino card just yeeted some data over)
    QObject::connect(Ar.getserial(), SIGNAL(readyRead()), this, SLOT(update_label()));

    // Create new RegExp then make it into a validator
    QRegExp reg("^[a-zA-Z]{1,20}$");
    QValidator *validator = new QRegExpValidator(reg, this);

    // Set validators for some inputs
    ui->le_Age->setValidator(new QIntValidator(0,1000,this));
    ui->le_Nom->setValidator(validator);
    ui->le_Race->setValidator(validator);
    ui->le_Espece->setValidator(validator);

    ui->tableView->setModel(A.afficher());      // Display database content in the tableView
    ui->tableView->hideColumn(0);               // Hide the ID Column
    ui->tableView->hideColumn(7);               // Hide the Image Column

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_label()
{
    data = Ar.read_from_arduino();
    if (data == "1")
        ui->label_test->setText("WE CONNECTED BABYYYYYY");
    else if (data == "0")
        ui->label_test->setText("AAAAAAAAAAAAAAAAAAAAAA");
    else if (data == "2")
        ui->label_test->setText(".2. .U. >-< '-' 'u' ^^' ");
    else if (data == "3")
        ui->label_test->setText("3 is like Ɛ or is Ɛ like 3 ?");
    else
        ui->label_test->setText("nothing");
}

void MainWindow::on_btn_Refresh_clicked()
{
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


    if ( ! (A.isEmpty(Nom) || A.isEmpty(Espece) || A.isEmpty(Race)) ) {
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

    if ( ! (A.isEmpty(Nom) || A.isEmpty(Espece) || A.isEmpty(Race) || value.isNull() ) ) {
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
    if (ui->sort_name->isChecked()) {
        ui->tableView->setModel(A.sortData("", 1));
    }
    else if (ui->sort_date->isChecked()) {
        ui->tableView->setModel(A.sortData("", 6, Qt::DescendingOrder));
    }
    else {
        ui->tableView->setModel(A.sortData());
    }
}

void MainWindow::on_btn_Upload_clicked()
{

    QString imageFile = QFileDialog::getOpenFileName(0, "Select Image", "C:\\", "Image Files (*.jpg *.jpeg *.png)");

    QFileInfo info(imageFile);
    QString filename = info.fileName();
    QString filepath = info.absoluteFilePath();

    QPixmap image (imageFile);

    ui->lblBkImge->setPixmap(image);
    ui->lblBkImge->setScaledContents( true );
    ui->lblBkImge->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
//    ui->lblBkImge->show();

//    QIcon ButtonIcon(image);
//    ui->btn_Upload->setIcon(ButtonIcon);

//    ui->btn_Upload->resize(image.rect().size());
//    ui->btn_Upload->setIconSize(image.rect().size());

    A.addImage(filepath, filename);
}

void MainWindow::on_btn_PDF_clicked()
{
    A.generatePdf(ui->tableView);
}


void MainWindow::on_le_Search_textChanged()
{
    QString research = ui->le_Search->text();
    ui->tableView->setModel(A.sortData("nom LIKE '"+research+"%' OR race LIKE '"+research+"%' OR espece LIKE '"+research+"%' OR IDA LIKE '"+research+"%' OR age LIKE '"+research+"%'"));
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

void MainWindow::on_btn_test0_clicked()
{
    Ar.write_to_arduino("0");           // Sends 0 to Arduino
}

void MainWindow::on_btn_test1_clicked()
{
    Ar.write_to_arduino("1");           // Sends 1 to Arduino
}

void MainWindow::on_btn_test2_clicked()
{
   Ar.write_to_arduino("2");           // Sends 2 to Arduino
}

void MainWindow::on_btn_test3_clicked()
{
   Ar.write_to_arduino("3");           // Sends 3 to Arduino
}



// The start of something that would finally be good i hope

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    qDebug() << "\nRow: " << index.row() << " Column: " << index.column();

//     index.data()         <-- Contains data type and actual data of the clicked cell
//     index.row()          <-- Contains the row (int) of the clicked cell
//     index.column()       <-- Contains the column (int) of the clicked cell
//    ui->tableView->setCurrentIndex(index);
//    ui->tableView->edit(index);

//    ui->tableView->model()->insertRows(index.row()+1, 1);


    //    QModelIndex index = model->index(0, 7);
    //    QByteArray Bytes = model->data(index).toByteArray();
    //    QPixmap pixmap;
    //    pixmap.loadFromData(Bytes);
    //    model->setData(index, pixmap.loadFromData(Bytes));
        // pixmap Contains the actual image
        // Doing setPixmap or something similar will set the image

    // Grab the data of the 7th row (hidden)
    QVariant value = index.sibling(index.row(), 7).data();
    qDebug() << value;


    // Test if there's an image
    if (value.isNull()) {
        QPixmap pixmap(":/res/noImage.png");
        ui->label_image->setScaledContents(true);
        ui->label_image->setPixmap(pixmap);
    }
    else {
        QPixmap pixmap;
        QByteArray Bytes = value.toByteArray();
        pixmap.loadFromData(Bytes);
        ui->label_image->setScaledContents(true);
        ui->label_image->setPixmap(pixmap);
    }

    qDebug() << "index data : " << index.data();
    qDebug() << "ui index data : " << ui->tableView->model()->data(index);
}
