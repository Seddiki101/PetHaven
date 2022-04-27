#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SwitchButton.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    int ret = Ar.connect_arduino();             // Start the connexion with Arduino
//    QObject::connect(Ar.getserial(), SIGNAL(readyRead()), this, SLOT(update_label()));

    // Create new RegExp then make it into a validator
    QRegExp reg("^[a-zA-Z]{1,20}$");
    QValidator *validator = new QRegExpValidator(reg, this);

    // Set validators for some inputs
    ui->animal_le_Age->setValidator(new QIntValidator(0, 1000, this));
    ui->animal_le_Nom->setValidator(validator);
    ui->animal_le_Race->setValidator(validator);
    ui->animal_le_Espece->setValidator(validator);

    A.afficher(ui->animal_tableView);           // Display database content in the tableView
    ui->animal_tableView->hideColumn(0);        // Hide the ID Column
    ui->animal_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->animal_tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QObject::connect(ui->animal_tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(header_headerClicked()));

    // Creates the epic Switch button to switch some stuff left and right
    Switch* switchWidget = new Switch("", ui->switch_widget);
    switchWidget->setLayoutDirection(Qt::LeftToRight);
    switchWidget->setChecked(true);
    QObject::connect(switchWidget, SIGNAL(clicked()), this, SLOT(switch_switchClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::toggle_stylesheet(QString path)
{
    QApplication *app = qApp;
    if (app == NULL) {
        qDebug() << "No app running somehow";
    }

    QFile file(path);
    file.open(QFile::ReadOnly | QFile::Text);
    app->setStyleSheet(QString(file.readAll()));
}


void MainWindow::on_animal_btn_Refresh_clicked()
{
    A.afficher(ui->animal_tableView);
    ui->animal_checkbox_Status->setCheckState(Qt::Unchecked);
    ui->animal_checkbox_Status->setText("Select an animal");
}

void MainWindow::on_animal_btn_Add_clicked()
{

    int Age = ui->animal_le_Age->text().toUInt();
    QString Nom = ui->animal_le_Nom->text();
    QString Espece = ui->animal_le_Espece->text();
    QString Race = ui->animal_le_Race->text();
    QDate Date = ui->animal_le_dateArr->date();

    Animal A(Age, 0, Nom, Espece, Race, Date);

    if ( ! (A.isEmpty(Nom) || A.isEmpty(Espece) || A.isEmpty(Race)) ) {
        if (A.ajouter()) {
            A.afficher(ui->animal_tableView);
            ui->animal_Historic->addItem(A.historic("Animal '" + Nom + "' added with success."));
        }
        else {
            ui->animal_Historic->addItem(A.historic("Failed to add."));
        }
    }
    else {
        ui->animal_Historic->addItem(A.historic("Failed to add, missing arguments."));
    }
}

void MainWindow::on_animal_btn_Update_clicked()
{
    QModelIndex index = ui->animal_tableView->selectionModel()->currentIndex();
    QVariant id = index.sibling(index.row(), 0).data();
    QVariant tempNom = index.sibling(index.row(), 1).data();   // gather NOM of the selected row

    int Status = ui->animal_checkbox_Status->isChecked();
    int Age = ui->animal_le_Age->text().toUInt();
    QString Nom = ui->animal_le_Nom->text();
    QString Espece = ui->animal_le_Espece->text();
    QString Race = ui->animal_le_Race->text();
    QDate Date = ui->animal_le_dateArr->date();

    Animal A(Age, Status, Nom, Espece, Race, Date);

    if ( ! (A.isEmpty(Nom) || A.isEmpty(Espece) || A.isEmpty(Race) || id.isNull() ) ) {
        if(A.modifier(id.toUInt())) {
            A.afficher(ui->animal_tableView);
            if (Nom != tempNom.toString()) {
                ui->animal_Historic->addItem(A.historic("Animal '" + tempNom.toString() + "' modified to '"+ Nom +"' with success."));
            }
            else {
                ui->animal_Historic->addItem(A.historic("Animal '" + Nom + "' modified with success."));
            }
        }
        else {
            ui->animal_Historic->addItem(A.historic("Failed to modify."));
        }
    }
    else {
        ui->animal_Historic->addItem(A.historic("Failed to update, missing arguments or nothing selected."));
    }
}

void MainWindow::on_animal_btn_Delete_clicked()
{
    QModelIndex index = ui->animal_tableView->selectionModel()->currentIndex();
    QVariant id = index.sibling(index.row(), 0).data();         // gather ID  of the selected row
    QVariant tempName = index.sibling(index.row(), 1).data();   // gather NOM of the selected row
    if (A.supprimer(id.toUInt()) && !id.isNull()) {
        A.afficher(ui->animal_tableView);
        ui->animal_Historic->addItem(A.historic("Deleted Animal '" + tempName.toString() + "' with success."));
    }
    else {
        ui->animal_Historic->addItem(A.historic("Failed to delete, nothing selected."));
    }
}

void MainWindow::on_animal_btn_Upload_clicked()
{
    QModelIndex index = ui->animal_tableView->selectionModel()->currentIndex();
    QVariant id = index.sibling(index.row(), 0).data();      // gather ID  of the selected row

    if (!id.isNull()) {
        QString imageFile = QFileDialog::getOpenFileName(0, "Select Image", "C:\\", "Image Files (*.jpg *.jpeg *.png)");

        QFileInfo info(imageFile);
        QString filepath = info.absoluteFilePath();
        A.updateImage(id.toUInt(), filepath);
        A.afficher(ui->animal_tableView);
    }
    else {
        QMessageBox::information(this, "Upload", "Please select an animal before uploading");
    }
}

void MainWindow::on_animal_btn_Sort_clicked()
{
    if (ui->animal_check_Name->isChecked()) {
        ui->animal_tableView->setModel(A.sortData("", 1));
        ui->animal_tableView->horizontalHeader()->setSortIndicator(1, Qt::AscendingOrder);
    }
    else if (ui->animal_check_Date->isChecked()) {
        ui->animal_tableView->setModel(A.sortData("", 6, Qt::DescendingOrder));
        ui->animal_tableView->horizontalHeader()->setSortIndicator(6, Qt::DescendingOrder);
    }
    else {
        ui->animal_tableView->setModel(A.sortData());
    }
    A.setWidgets(ui->animal_tableView);
}

void MainWindow::on_animal_btn_PDF_clicked()
{
    A.generatePdf(ui->animal_tableView);
}


void MainWindow::on_animal_le_Search_textChanged()
{
    QString research = ui->animal_le_Search->text();
    ui->animal_tableView->setModel(A.sortData("nom LIKE '"+research+"%' OR race LIKE '"+research+"%' OR espece LIKE '"+research+"%' OR IDA LIKE '"+research+"%' OR age LIKE '"+research+"%'"));
    A.setWidgets(ui->animal_tableView);
}

void MainWindow::header_headerClicked()
{
    A.setWidgets(ui->animal_tableView);
}

// Some test and stuff
// Currently put the image to a label so it can be seen
void MainWindow::on_animal_tableView_clicked(const QModelIndex &index)
{

// Code below was used to set animage from the table in a label
//    QVariant value = index.sibling(index.row(), 7).data();
//    if (value.isNull()) {
//        QPixmap pixmap(":/res/noImage.png");
//        ui->animal_label_Image->setScaledContents(true);
//        ui->animal_label_Image->setPixmap(pixmap);
//    }
//    else {
//        QPixmap pixmap;
//        QByteArray Bytes = value.toByteArray();
//        pixmap.loadFromData(Bytes);

//        ui->animal_label_Image->setScaledContents(true);
//        ui->animal_label_Image->setPixmap(pixmap);
//    }

    if (index.sibling(index.row(), 5).data().toBool()) {
        ui->animal_checkbox_Status->setCheckState(Qt::Checked);
    }
    else {
        ui->animal_checkbox_Status->setCheckState(Qt::Unchecked);
    }
    ui->animal_checkbox_Status->setText(index.sibling(index.row(), 1).data().toString());
}


// Some Arduino functions

//void MainWindow::on_pushButton_clicked()
//{

//    Ar.write_to_arduino("1");

//    QString time = QDateTime::currentDateTime().toString("hh:mm:ss");
//    QString date = QDate::currentDate()
//            .toString();
//    QString ERH = date + " " + time;
//    // cut at the 16th char


//    Ar.tempDate =  QDateTime::currentDateTime().toTime_t() + 3600;
//    qDebug () << "Time in unix timestamp : "<< Ar.tempDate;
//    qDebug () << "Time normal i guess : "<< QDateTime::currentDateTime();

//    QString Unix = "T" + QString::number(Ar.tempDate);

//    qDebug () << Unix;
//    Ar.write_to_arduino(Unix.toUtf8());
//    Ar.write_to_arduino(Unix.toUtf8());

//}

//void MainWindow::on_pushButton_2_clicked()
//{

//    Ar.write_to_arduino("0");
//    Ar.write_to_arduino("0");

//    data = Ar.read_from_arduino();


//    QString E = QString(data);
//    int INT = data.toUInt();
//    qDebug () << "data from Arduino no : "<< E << " Potentially INT : " << INT;
//    qDebug () << Ar.tempDate;

//    QString newString = E.left(10);
//    qDebug () << "OK THIS IS SUPPOSEDF TO BE GOOD I SEAR S : " << newString;

//    int unixDate = newString.toUInt();


//    unixDate -= Ar.tempDate;
//    qDebug () << unixDate;

//    int days = unixDate / 86400;
//    if (days > 0)
//        unixDate -= days * 86400;
//    int hours = unixDate / 3600;
//    if (hours > 0)
//        unixDate -= hours * 3600;
//    int minutes = unixDate / 60;
//    if (minutes > 0)
//        unixDate -= minutes * 60;
//    int seconds = unixDate;
//    qDebug () << "Time elapsed : ";
//    qDebug() << "Days: " << days << " Hours: " << hours << " Minutes: " << minutes << " Seconds: " << seconds;
//}
