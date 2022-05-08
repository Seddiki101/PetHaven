#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

/*                      */
/*    Global Stuff      */
/*                      */
    // Very important don't remove everything will be brokey brokey i swear just don't this leave it at that
    ui->setupUi(this);

    // Creates the epic Switch button to switch some stuff left and right
    Switch* switchWidget = new Switch("", ui->switch_widget);
    switchWidget->setLayoutDirection(Qt::LeftToRight);
    switchWidget->setChecked(true);
    QObject::connect(switchWidget, SIGNAL(clicked()), this, SLOT(switch_switchClicked()));

    ui->stackedWidget->setCurrentIndex(0);

/*                      */
/*    Arduino Init      */
/*                      */
    Ar.connect_arduino();                                                           // Start the connexion with Arduino
    QObject::connect(Ar.getserial(),SIGNAL(readyRead()),this,SLOT(check()));        // FOR RFID LOGIN SYSTEM

/*                      */
/*    Adoptions Init    */
/*                      */
    ui->lineEdit_8->setValidator(new QIntValidator(0,999999,this));   // id modif animal
    ui->lineEdit_9->setValidator(new QIntValidator(0,999999,this));   // id modif beneficiaire

/*                      */
/*      Animal Init     */
/*                      */
    // Create new RegExp then make it into a validator
    QRegExp reg("^[a-zA-Z]{1,20}$");
    QValidator *validator = new QRegExpValidator(reg, this);

    // Set validators for some inputs
    ui->animal_le_Age->setValidator(new QIntValidator(0, 1000, this));
    ui->animal_le_Nom->setValidator(validator);
    ui->animal_le_Race->setValidator(validator);
    ui->animal_le_Espece->setValidator(validator);

    ui->animal_tableView->hideColumn(0);               // Hide the ID Column
    ui->animal_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->animal_tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QObject::connect(ui->animal_tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(header_headerClicked()));

/*                      */
/*   Beneficiaire Init  */
/*                      */
    ui->BENEFICIAIRE_stackedWidget->setCurrentIndex(0);
    notifstate=false;
    ui->BENEFICIAIRE_label_Notif_Indicator->setStyleSheet("");
    ui->BENEFICIAIRE_listWidget->hide();
    ui->BENEFICIAIRE_lineEdit_CIN_2->setEnabled(0);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(notifs2()));
    timer->start(5000);


/*                      */
/*    Donations Init    */
/*                      */
    connect(ui->Annuler_dons, SIGNAL(clicked()),this, SLOT(close()));
    connect(ui->envoyer_SMTP, SIGNAL(clicked()),this, SLOT(sendMail()));
    ui->le_server_SMTP->setText("smtp.gmail.com");
    ui->le_port_SMTP->setText("465");
    ui->le_mail_SMTP->setText("mmarrouki52@gmail.com");
    ui->le_passwd_SMTP->setText("Marmar21062001!");
    ui->le_objet_SMTP->setText("Donation success");

    QIntValidator ex;
    QRegExp reg1("^([a-zA-Z0-9_\\-\\.]+)@([a-zA-Z0-9_\\-\\.]+)\\.([a-zA-Z]{2,5})$ ");
    validator = new QRegExpValidator(reg1, this);
    ui->le_email_dons->setValidator(validator);
    ui->le_email_Modif_dons->setValidator(validator);
    ui->le_id_Supp_dons->setValidator(new QIntValidator(0, 99999999,this));
    ui->le_id_Modif_dons->setValidator(new QIntValidator(0, 99999999,this));
    ui->le_montant_dons->setValidator(new QIntValidator(0, 99999999,this));
    ui->le_montant_Modif_dons->setValidator(new QIntValidator(0, 99999999,this));
}


MainWindow::~MainWindow()
{
    delete ui;
}



//******************************************************************//
//                                                                  //
//                  SHARED FUNCTIONS                                //
//                                                                  //
//******************************************************************//

void MainWindow::on_Connect_Button_clicked()
{
    QString tempLogin=ui->Login_Text->text();
    QString password=ui->Password_Text->text();

    if( E.verifyLogin(tempLogin, E.Cryptage_Employe(password)) ) {
        QMessageBox::information(this,"login","Username and password are correct");
        login = tempLogin;
        ui->stackedWidget->setCurrentIndex(1);
        ui->Main_StackedWidget->setCurrentIndex(0);
        ui->Employee_tableView->setModel(E.afficher_Employe());
        string conv;
        const char*text;

        conv=login.toStdString();
        text=conv.c_str();
        //Arduino pointage
        Ar.write_to_arduino("1");
        Ar.write_to_arduino(text);
        QTime dieTime= QTime::currentTime().addSecs(3);
        while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

        QString time = QDateTime::currentDateTime().toString("hh:mm:ss");
        QString date = QDate::currentDate()
        .toString();
        QString ERH = date + " " + time;
        // cut at the 16th char

        Ar.tempDate =  QDateTime::currentDateTime().toTime_t() + 3600;

        QString Unix = "T" + QString::number(Ar.tempDate);
        Ar.write_to_arduino(Unix.toUtf8());
        Ar.write_to_arduino(Unix.toUtf8());
    }
    else {
        QMessageBox::warning(this,"login","Username or password is incorrect");
    }
}

void MainWindow::on_Disconnect_Button_clicked()
{
    string conv;
    const char*text;
    conv=login.toStdString();
    text=conv.c_str();

    //Arduino Pointage
    Ar.write_to_arduino("0");
    Ar.write_to_arduino("0");
    Ar.write_to_arduino(text);

    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    data = Ar.read_from_arduino();

    QString E = QString(data);
    int unixDate = E.toUInt();

    unixDate -= Ar.tempDate;
    qDebug () << unixDate;

    int days = unixDate / 86400;
    if (days > 0)
        unixDate -= days * 86400;
    int hours = unixDate / 3600;
    if (hours > 0)
        unixDate -= hours * 3600;
    int minutes = unixDate / 60;
    if (minutes > 0)
        unixDate -= minutes * 60;
    int seconds = unixDate;
    qDebug() << "Days: " << days << " Hours: " << hours << " Minutes: " << minutes << " Seconds: " << seconds;

    login.clear();
    ui->stackedWidget->setCurrentIndex(0);
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

void MainWindow::switch_switchClicked()
{
    Switch* switch1 = ui->switch_widget->findChild<Switch*>();
    if (switch1->checkState() == Qt::Unchecked) {
        toggle_stylesheet(":/ressources/LightTheme.qss");
    }
    else if (switch1->checkState() == Qt::Checked) {
        toggle_stylesheet(":/ressources/DarkTheme.qss");
    }
    else {
        qDebug() << "This is not supposed to happen";
    }
}

void MainWindow::on_Gestions_Employees_clicked()
{
    ui->Main_StackedWidget->setCurrentIndex(0);
    ui->Employee_tableView->setModel(E.afficher_Employe());
}

void MainWindow::on_Gestion_Adoptions_clicked()
{
    ui->Main_StackedWidget->setCurrentIndex(1);
    ui->tabAdo1->setModel(Ad.affichAdo());
}

void MainWindow::on_Gestion_Animals_clicked()
{
    ui->Main_StackedWidget->setCurrentIndex(2);
    A.afficher(ui->animal_tableView);
}

void MainWindow::on_Gestion_Beneficiaries_clicked()
{
    ui->Main_StackedWidget->setCurrentIndex(3);
    ui->BENEFICIAIRE_tableView->setModel(B.afficher("",0));
}

void MainWindow::on_Gestion_Deliveries_clicked()
{
    ui->Main_StackedWidget->setCurrentIndex(4);
    ui->adoptions_stackedWidget->setCurrentIndex(0);
    ui->Livraison_tableView->setModel(L.afficher());
}

void MainWindow::on_Gestion_Donations_clicked()
{
    ui->Main_StackedWidget->setCurrentIndex(5);
    ui->tableView_dons->setModel(Dtmp.afficher_dons());
}



//******************************************************************//
//                                                                  //
//                  EMPLOYEE FUNCTIONS                              //
//                                                                  //
//******************************************************************//

void MainWindow::on_Employee_Ajouter_clicked()
{
    int ID=ui->Employee_ID->text().toUInt();
    QString Nom=ui->Employee_Nom->text();
    QString Prenom=ui->Employee_Prenom->text();
    QString Email=ui->Employee_Email->text();
    QString Login=ui->Employee_Login->text();
    QString Mdp=ui->Employee_MDP->text();
    int Note=ui->Employee_Note->text().toUInt();
    Employe E(ID,Nom,Prenom,Email,Login,Mdp,Note, "");

    if(E.Verif_Email_Employe()) {
        ui->Employee_Email->clear();
    }

    bool test=E.ajouter_Employe();
    if(test) {
        ui->Employee_tableView->setModel(E.afficher_Employe());
    }
}

void MainWindow::on_Employee_Supprimer_clicked()
{
    int id;
    QModelIndex index=ui->Employee_tableView->selectionModel()->currentIndex();
    QVariant value=index.sibling(index.row(), 0).data();
    id=value.toUInt();

    bool test=E.supprimer_Employe(id);
    if(test)
    {
        ui->Employee_tableView->setModel(E.afficher_Employe());
    }
}

void MainWindow::on_Employee_Modifier_clicked()
{
    int id;
    QModelIndex index=ui->Employee_tableView->selectionModel()->currentIndex();
    QVariant value=index.sibling(index.row(), 0).data();
    id=value.toUInt();

    QString Nom=ui->Employee_Nom->text();
    QString Prenom=ui->Employee_Prenom->text();
    QString Email=ui->Employee_Email->text();
    QString Login=ui->Employee_Login->text();
    QString Mdp=ui->Employee_MDP->text();
    int Note=ui->Employee_Note->text().toUInt();
    Employe E(id,Nom,Prenom,Email,Login,Mdp,Note, "");

    bool test=E.modifier_Employe(id);
    if(test)
    {
        ui->Employee_tableView->setModel (E.afficher_Employe());
    }
}

void MainWindow::on_Employee_Sort_clicked()
{
    if(ui->Employee_Login_Sort) {
    ui->Employee_tableView->setModel(E.triNom_Employe());
    }
    if(ui->Employee_Nom_Sort) {
        ui->Employee_tableView->setModel(E.triLogin_Employe());
    }
}

void MainWindow::on_Employee_search_clicked()
{
    QString recherche = ui->Employee_Search_label->text();
    ui->Employee_tableView->setModel(E.chercherID_Employe(recherche));
}

void MainWindow::on_Employee_Search_label_textChanged()
{
    QString recherche = ui->Employee_Search_label->text();
    ui->Employee_tableView->setModel(E.chercherNom_Employe(recherche));
}

void MainWindow::on_Employee_PDF_clicked()
{
    E.pdf_Employe(ui->Employee_tableView);
}

void MainWindow::on_Employee_Appreciation_clicked()
{
    ui->Employee_Note1->clear();
    ui->Employee_Note2->clear();

    QList<QVariant> list = E.appreciation_Employe(5);
    for (int i = 0; i < list.size(); i+=2) {
        ui->Employee_Note1->addItem(list[i].toString() + " " + list[i+1].toString());
    }
    list = E.appreciation_Employe(4);
    for (int i = 0; i < list.size(); i+=2) {
        ui->Employee_Note2->addItem(list[i].toString() + " " + list[i+1].toString());
    }
}



//******************************************************************//
//                                                                  //
//                  ADOPTIONS FUNCTIONS                             //
//                                                                  //
//******************************************************************//

//--               Weird utility stuff for Qr codes and such                 -- //
//******************************************************************************//

using std::uint8_t;
using qrcodegen::QrCode;
using qrcodegen::QrSegment;


// Function prototypes
static void dosicDemo(char * text);

static std::string toSvgString(const QrCode &qr, int border);
static void printQr(const QrCode &qr);

static void dosicDemo(const char * text) {
    const QrCode::Ecc errCorLvl = QrCode::Ecc::LOW;  // Error correction level

    // Make and print the QR Code symbol
    const QrCode qr = QrCode::encodeText(text, errCorLvl);
    //Directory here
    QString file = "C:/Users/ilyes/Desktop/Pet_Haven/ressources/qr.svg";
        QFile outputFile(file);
        outputFile.open(QIODevice::WriteOnly);

        QString str = QString::fromStdString(toSvgString(qr, 4));


        if(!outputFile.isOpen())
        {
           std::cout << "alert that file did not open" ;
        }
        QTextStream outStream(&outputFile);

        outStream << str;
        outputFile.close();

}

// Returns a string of SVG code for an image depicting the given QR Code, with the given number
// of border modules. The string always uses Unix newlines (\n), regardless of the platform.
static std::string toSvgString(const QrCode &qr, int border) {
    if (border < 0)
        throw std::domain_error("Border must be non-negative");
    if (border > INT_MAX / 2 || border * 2 > INT_MAX - qr.getSize())
        throw std::overflow_error("Border too large");

    std::ostringstream sb;
    sb << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    sb << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
    sb << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" viewBox=\"0 0 ";
    sb << (qr.getSize() + border * 2) << " " << (qr.getSize() + border * 2) << "\" stroke=\"none\">\n";
    sb << "\t<rect width=\"100%\" height=\"100%\" fill=\"#FFFFFF\"/>\n";
    sb << "\t<path d=\"";
    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            if (qr.getModule(x, y)) {
                if (x != 0 || y != 0)
                    sb << " ";
                sb << "M" << (x + border) << "," << (y + border) << "h1v1h-1z";
            }
        }
    }
    sb << "\" fill=\"#000000\"/>\n";
    sb << "</svg>\n";
    return sb.str();
}


// Prints the given QrCode object to the console.
static void printQr(const QrCode &qr) {
    int border = 4;
    for (int y = -border; y < qr.getSize() + border; y++) {
        for (int x = -border; x < qr.getSize() + border; x++) {
            std::cout << (qr.getModule(x, y) ? "##" : "  ");
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

//***************************************************************************//

void MainWindow::on_Back_clicked()
{
    ui->adoptions_stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_back2_clicked()
{
    ui->adoptions_stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_addopage_clicked()
{
    ui->adoptions_stackedWidget->setCurrentIndex(1);
    ui->tableView_2->setModel(Ad.affichBeneficiaires());
    ui->tableView_3->setModel(Ad.affichAnimals());
}

//ajouter
void MainWindow::on_addado_clicked()
{
    QModelIndex index=ui->tableView_2->selectionModel()->currentIndex();
    QVariant value=index.sibling(index.row(),0).data();
    int idp=value.toInt();

    QModelIndex index2=ui->tableView_3->selectionModel()->currentIndex();
    QVariant value2=index2.sibling(index2.row(),0).data();
    int ida=value2.toInt();

    Adoption Ad(0,ida,idp,QDate::currentDate());
    Ad.ajoutAdo();
    ui->tabAdo1->setModel(Ad.affichAdo());
    ui->adoptions_stackedWidget->setCurrentIndex(0);
}

//supprimer
void MainWindow::on_supado_clicked()
{
    QModelIndex index=ui->tabAdo1->selectionModel()->currentIndex();
    QVariant value=index.sibling(index.row(),index.column()).data(); //will get the value of the clicked cell.
    int id=value.toInt();
    int ida=index.sibling(index.row(),1).data().toUInt();
    int idp=index.sibling(index.row(),4).data().toUInt();

    Ad.supprimAdo(id, ida, idp);
    ui->tabAdo1->setModel(Ad.affichAdo());
}

void MainWindow::on_sortado_clicked()
{
    if (ui->radioButton) {
        ui->tabAdo1->setModel(Ad.triDatesAdo());}

    if (ui->radioButton_2) {
        ui->tabAdo1->setModel(Ad.triAlphAdo());}
}

void MainWindow::on_searchado_clicked()
{
    QString recherche = ui->LEsearch->text();
    ui->tabAdo1->setModel(Ad.chercherAdo(recherche));
}

void MainWindow::on_refresh_clicked()
{
    ui->tabAdo1->setModel(Ad.affichAdo());
    ui->tableView_2->setModel(Ad.affichBeneficiaires());
    ui->tableView_3->setModel(Ad.affichAnimals());
    ui->tabAdo2->setModel(Ad.affichAdo());
}

void MainWindow::on_upado_clicked()
{
    QModelIndex index=ui->tabAdo2->selectionModel()->currentIndex();
    QVariant value=index.sibling(index.row(),0).data(); //will get the value of the clicked cell.
    int ido=value.toInt();
    int idp=ui->lineEdit_8->text().toInt();
    int ida=ui->lineEdit_9->text().toInt();

    Ad.modifierAdo(ido,idp,ida);
    ui->adoptions_stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_updatePage_clicked()
{
    ui->adoptions_stackedWidget->setCurrentIndex(2);
    ui->tabAdo2->setModel(Ad.affichAdo());
}

void MainWindow::on_adocsv_clicked()
{
    Ad.genereExcel(ui->tabAdo1);
}

void MainWindow::on_adopdf_clicked()
{
    Ad.generatePdf(ui->tabAdo1);
}

void MainWindow::on_LEsearch_textChanged()
{
    QString recherche = ui->LEsearch->text();
    ui->tabAdo1->setModel(Ad.searchAdo(recherche));
}

void MainWindow::on_qr_clicked()
{
    //char *texto = "Hello, world!";
    QString ido;
    string conv;
    const char *texto;
    QModelIndex index=ui->tabAdo1->selectionModel()->currentIndex();
    QVariant value=index.sibling(index.row(),index.column()).data(); //will get the value of the clicked cell.
    ido=value.toString();
    conv = ido.toStdString();
    texto=conv.c_str();


    //texto= ido.toStdString().c_str(); str.toLocal8Bit().constData()
    dosicDemo(texto);

}

void MainWindow::on_Total_clicked()
{
    ui->tabAdo1->setModel(Ad.Totado());
    Ad.generatePdf(ui->tabAdo1);
}

void MainWindow::on_stat_clicked()
{
    statistique s;
    s.exec();
}



//******************************************************************//
//                                                                  //
//                   ANIMALS FUNCTIONS                              //
//                                                                  //
//******************************************************************//

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



//******************************************************************//
//                                                                  //
//                  BENEFICIARIES FUNCTIONS                         //
//                                                                  //
//******************************************************************//

//ajouter
void MainWindow::on_BENEFICIAIRE_pushButton_AddNew_clicked()
{   bool ok=true;
    QString errormsg="";
    int CIN,age,num;

    QString nom, prenom, adresse, type;

    if(ui->BENEFICIAIRE_lineEdit_CIN->text().toInt()>99999999 ||ui->BENEFICIAIRE_lineEdit_CIN->text().toInt()<10000000)
    {
        errormsg= errormsg.append("CIN not valid. ");
    }


    if(ui->BENEFICIAIRE_lineEdit_Age->text().isEmpty() || ui->BENEFICIAIRE_lineEdit_Age->text().toInt()<0 || ui->BENEFICIAIRE_lineEdit_Age->text().toInt()>130 || !B.is_number(ui->BENEFICIAIRE_lineEdit_Age->text().toStdString()))
    {

         errormsg= errormsg.append("Age not valid. ");
    }


    if(ui->BENEFICIAIRE_lineEdit_Name->text().isEmpty() || ui->BENEFICIAIRE_lineEdit_LastName->text().isEmpty() || B.has_any_digits(ui->BENEFICIAIRE_lineEdit_Name->text().toStdString()) || B.has_any_digits(ui->BENEFICIAIRE_lineEdit_LastName->text().toStdString()))
    {
        errormsg= errormsg.append("Name or last name not valid.");
    }


    if(ui->BENEFICIAIRE_lineEdit_Num->text().toInt()>99999999 || ui->BENEFICIAIRE_lineEdit_Num->text().toInt()<10000000)
    {
        errormsg= errormsg.append("Invalid phone number.");
    }

    if(errormsg!="")
        ok=false;


  CIN=ui->BENEFICIAIRE_lineEdit_CIN->text().toInt();
    age=ui->BENEFICIAIRE_lineEdit_Age->text().toInt();
    nom=ui->BENEFICIAIRE_lineEdit_Name->text();
   prenom=ui->BENEFICIAIRE_lineEdit_LastName->text();
    adresse=ui->BENEFICIAIRE_lineEdit_Adress->text();
   type=ui->BENEFICIAIRE_lineEdit_Type->text();
   num=ui->BENEFICIAIRE_lineEdit_Num->text().toInt();
   QDateTime date = QDateTime::currentDateTime();

ui->BENEFICIAIRE_label_Errors->setText(errormsg);
if(ok)
{
    Beneficiaire B(CIN,nom, prenom, age, adresse, type, num, date);
    B.ajouter();
    B.log(1,login);
    ui->BENEFICIAIRE_tableView->setModel(B.afficher("",0));
}


}

//supprimer
void MainWindow::on_BENEFICIAIRE_pushButton_Delete_clicked()
{
int v1;
    QModelIndex index=ui->BENEFICIAIRE_tableView->selectionModel()->currentIndex();
    QVariant value=index.sibling(index.row(),index.column()).data(); //will get the value of the clicked cell.
    v1=value.toInt();
    Beneficiaire B;
   B.supprimer(v1);
   B.log(-1,login);
    ui->BENEFICIAIRE_tableView->setModel(B.afficher("",0));


}

void MainWindow::on_BENEFICIAIRE_pushButton_ConfirmChanges_clicked()
{
// modifier
    bool ok=true;
        QString errormsg="";
    int CIN,age,num;
    QString nom, prenom, adress, type;


        QModelIndex index=ui->BENEFICIAIRE_tableView->selectionModel()->currentIndex();
        QVariant CIN_string=index.sibling(index.row(),index.column()).data(); //will get the value of the clicked cell.
        CIN=CIN_string.toInt();


        if(ui->BENEFICIAIRE_lineEdit_Age_2->text().isEmpty() || ui->BENEFICIAIRE_lineEdit_Age_2->text().toInt()<0 || ui->BENEFICIAIRE_lineEdit_Age_2->text().toInt()>130 )//|| B.is_number(ui->BENEFICIAIRE_lineEdit_Age_2->text().toStdString()))
        {

             errormsg= errormsg.append("Age not valid. ");
        }


        if(ui->BENEFICIAIRE_lineEdit_Name_2->text().isEmpty() || ui->BENEFICIAIRE_lineEdit_LastName_2->text().isEmpty() || B.has_any_digits(ui->BENEFICIAIRE_lineEdit_Name_2->text().toStdString()) || B.has_any_digits(ui->BENEFICIAIRE_lineEdit_LastName_2->text().toStdString()))
        {
            errormsg= errormsg.append("Name or last name not valid.");
        }


        if(ui->BENEFICIAIRE_lineEdit_Num_2->text().toInt()>99999999 || ui->BENEFICIAIRE_lineEdit_Num_2->text().toInt()<10000000)
        {
            errormsg= errormsg.append("Invalid phone number.");
        }

        if(errormsg!="")
            ok=false;

        ui->BENEFICIAIRE_label_Errors_2->setText(errormsg);

    age=ui->BENEFICIAIRE_lineEdit_Age_2->text().toInt();
    nom=ui->BENEFICIAIRE_lineEdit_Name_2->text();
   prenom=ui->BENEFICIAIRE_lineEdit_LastName_2->text();
    adress=ui->BENEFICIAIRE_lineEdit_Adress_2->text();
   type=ui->BENEFICIAIRE_lineEdit_Type_2->text();
   num=ui->BENEFICIAIRE_lineEdit_Num_2->text().toInt();
   QDateTime date=date.currentDateTime();

if(ok)
{
    //Beneficiaire B(CIN,nom, prenom, age, adress, type, num, date);
    B.modifier(CIN,nom, prenom, age, adress, type, num);
    B.log(1,login);

    //int nextIndex = ui->BENEFICIAIRE_stackedWidget->currentIndex() - 1;
   //if( nextIndex < ui->BENEFICIAIRE_stackedWidget->count())
           ui->BENEFICIAIRE_stackedWidget->setCurrentIndex(0);
}




}
//go to modifier
void MainWindow::on_BENEFICIAIRE_pushButton_GotoEdit_clicked()
{
    QModelIndex index=ui->BENEFICIAIRE_tableView->selectionModel()->currentIndex();

    QVariant CIN_string=index.sibling(index.row(),index.column()).data(); //will get the value of the clicked cell
    if(!CIN_string.isNull())
    {
                //int nextIndex = ui->BENEFICIAIRE_stackedWidget->currentIndex() + 1;
                //if( nextIndex < ui->BENEFICIAIRE_stackedWidget->count())
        ui->BENEFICIAIRE_lineEdit_CIN_2->setText(CIN_string.toString());
                       ui->BENEFICIAIRE_stackedWidget->setCurrentIndex(1);
    }
}

//search
void MainWindow::on_BENEFICIAIRE_lineEdit_Search_textChanged()
{
    Beneficiaire B;

    QString search = ui->BENEFICIAIRE_lineEdit_Search->text();
     ui->BENEFICIAIRE_tableView->setModel(B.afficher(search,0));
}
//tri
void MainWindow::on_BENEFICIAIRE_pushButton_Sort_clicked()
{
    if (ui->BENEFICIAIRE_radioButton_Sort_ByName) {
    ui->BENEFICIAIRE_tableView->setModel(B.afficher("",1));}


    if (ui->BENEFICIAIRE_radioButton_Sort_ByAge) {
    ui->BENEFICIAIRE_tableView->setModel(B.afficher("",2));}


}
//export pdf
void MainWindow::on_BENEFICIAIRE_pushButton_ExportPDF_clicked()
{
    Beneficiaire B;
    B.exportPDF(ui->BENEFICIAIRE_tableView);
}

void MainWindow::on_BENEFICIAIRE_pushButton_Statistics_clicked()
{
    statistique_beneficiaires s;
    s.setModal(true);
    s.exec();
}
//notifs
void MainWindow::notifs()
{
    QString c1,c2,c3;

        while(ui->BENEFICIAIRE_listWidget->count()>0)
        {
          ui->BENEFICIAIRE_listWidget->takeItem(0);//handle the item if you don't
                                  //have a pointer to it elsewhere
        }
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
        c1.append(" an entry.");

        ui->BENEFICIAIRE_listWidget->addItem(c1);
        }

}

void MainWindow::saveLastnotif()
{
 QDateTime datetime = QDateTime::currentDateTime();

 QDate date = datetime.date();
 QTime time = datetime.time();

 QString date_str= date.toString("yyyy-MM-dd");
 QString time_str=time.toString("hh:mm:ss");

 QString str = date_str.append(" ");
 str = str.append(time_str);

  QFile file("C:/Users/ilyes/Desktop/Pet_Haven/lastnotif.txt");
 if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate ))
 {
      qDebug()<< "Could not open file! File not written.";
      return;
  }

file.write(str.toUtf8());

  file.close();


}

QString MainWindow::LoadLastnotif()
{
    QFile file("C:/Users/ilyes/Desktop/Pet_Haven/lastnotif.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<< "Could not open file! File not read.";

    }
    file.seek(0);
QString array=file.readAll();
file.close();
     return array;


}

void MainWindow::notifs2()
{
    QString c1,c2,c3,c3b;

QString val=LoadLastnotif(),str="select * from LOGS WHERE DATEOP > to_date( '",str2="select * from LOGS WHERE DATEOP < to_date( '";
        QSqlQuery query;
        //CREATE QUERY FOR NEW NOTIFS
        str.append(val);
        str.append("' , 'YYYY-MM-DD HH24:mi:ss')");
query.prepare(str);
        //EXECUTE
        query.exec();

        //EMPTY LISTWIDGET
        while(ui->BENEFICIAIRE_listWidget->count()>0)
        {
          ui->BENEFICIAIRE_listWidget->takeItem(0);
        }
        ui->BENEFICIAIRE_listWidget->addItem("[NEW]");

int count=0;
        //CHECK IF QUERY RESP. ISNT EMPTY
        while(query.next())
        {
            ui->BENEFICIAIRE_label_Notif_Indicator->setStyleSheet("background-color:red;");
           count++;
        c1 = query.value(0).toString();
        c2 = query.value(1).toString();
        c3 = query.value(2).toString();


        c2.append(" has ");
        if(c3=="1")
            c2.append("added");
        else if(c3=="-1")
            c2.append("deleted");
        else
           c2.append("modified");
        c2.append(" an entry.");

        ui->BENEFICIAIRE_listWidget->addItem(c2);
        }
        //HIGHLIGHT NEW NOTIF
        for (int i = 0; i < count+1 ; i++) {
          ui->BENEFICIAIRE_listWidget->item(i)->setSelected(true);
        }
        ui->BENEFICIAIRE_listWidget->setFocus();
        //CREATE QUERY FOR OLD NOTIFS
        str2.append(val);
        str2.append("' , 'YYYY-MM-DD HH24:mi:ss')");
        query.prepare(str2);
        //qDebug() << "OLD NOTIF QUERY: " <<query.lastQuery();
        query.exec();
        ui->BENEFICIAIRE_listWidget->addItem("[SEEN]");

        //CHECK IF QUERY RESP. ISNT EMPTY
        while(query.next())
        {
        c1 = query.value(0).toString();
        c2 = query.value(1).toString();
        c3 = query.value(2).toString();
        c2.append(" has ");
        if(c3=="1")
            c2.append("added");
        else if(c3=="-1")
            c2.append("deleted");
        else
           c2.append("modified");
        c2.append(" an entry.");

        ui->BENEFICIAIRE_listWidget->addItem(c2);
        }

}

void MainWindow::on_BENEFICIAIRE_pushButton_Notifications_clicked()
{
    if(notifstate)
    {
        ui->BENEFICIAIRE_listWidget->hide();
        ui->BENEFICIAIRE_label_Notif_Indicator->setStyleSheet("");
        notifstate=false;
    }

    else
    {
        ui->BENEFICIAIRE_listWidget->show();
        notifstate=true;
    }


    saveLastnotif();

}


//******************************************************************//
//                                                                  //
//                   DELIVERIES FUNCTIONS                           //
//                                                                  //
//******************************************************************//

void MainWindow::on_Livraison_btn_Refresh_clicked()
{
    Livraison L;
    ui->Livraison_tableView->setModel(L.afficher());
}


void MainWindow::on_Livraison_btn_Add_clicked()
{
    QDateTime DateTime=ui->Livraison_le_Date->dateTime();
    QString Adresse=ui->Livraison_le_Arrive->text();
    QString Adresse_dep=ui->Livraison_le_Depart->text();

    Livraison L(DateTime,Adresse,Adresse_dep);
    if (L.controlA() || L.controlAD())
    {
        if (L.controlA())
        {
            ui->Livraison_err2->clear();
            ui->Livraison_err2->setText("Champ Obligatoire");
            ui->Livraison_le_Arrive->clear();
        }

        if (L.controlAD())
        {
            ui->Livraison_err1->clear();
            ui->Livraison_err1->setText("Champ Obligatoire");
            ui->Livraison_le_Depart->clear();
        }

    }
    bool test=L.ajouter();
    QMessageBox msgBox;
    if(test)
    { msgBox.setText("Ajout avec succes.");
        ui->Livraison_tableView->setModel(L.afficher());
    }

    QRegularExpression reg("^([0-9]{1,5}\\s[a-zA-Z0-9\\s]{1,99})$");
    QRegularExpressionValidator validator(reg, 0);

    int pos = 0;
    QString temp = ui->Livraison_le_Depart->text();
    validator.validate (temp, pos);
}

void MainWindow::on_Livraison_btn_Update_clicked()
{
    int id;
    QModelIndex index=ui->Livraison_tableView->selectionModel()->currentIndex();
    QVariant value=index.sibling(index.row(),index.column()).data();
    id=value.toUInt();

    QDateTime DateTime=ui->Livraison_le_Date->dateTime();
    QString Adresse=ui->Livraison_le_Arrive->text();
    QString Adresse_dep=ui->Livraison_le_Depart->text();

    Livraison L(DateTime,Adresse,Adresse_dep);
    bool test=L.modifier(id);
    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText ("Modification avec succes.");
        ui->Livraison_tableView->setModel (L.afficher());
    }
}

void MainWindow::on_Livraison_btn_Delete_clicked()
{
    Livraison L1;

    int id;
    QModelIndex index=ui->Livraison_tableView->selectionModel()->currentIndex();
    QVariant value=index.sibling(index.row(),index.column()).data();
    id=value.toUInt();

    bool test = L1.supprimer(id);
    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText("suppression avec succes.");
        ui->Livraison_tableView->setModel(L.afficher());
    }
}

void MainWindow::on_Livraison_btn_Sort_clicked()
{
    Livraison L;
    if (ui->Livraison_sort_name->isChecked())
    {
        ui->Livraison_tableView->setModel(L.triAlpha());
    }

    if (ui->Livraison_sort_date->isChecked())
    {
        ui->Livraison_tableView->setModel(L.triDate());
    }
}

void MainWindow::on_Livraison_btn_PDF_clicked()
{
    Livraison L;
    L.generatePdf(ui->Livraison_tableView);
}

void MainWindow::on_Livraison_btn_Search_clicked()
{
    Livraison L;
    QString recherche=ui->Livraison_le_Search->text();
    ui->Livraison_tableView->setModel(L.chercher(recherche));
}

void MainWindow::on_Livraison_le_Search_textChanged()
{
    Livraison L;
    QString recherche=ui->Livraison_le_Search->text();
    ui->Livraison_tableView->setModel(L.search(recherche));
}

void MainWindow::on_Livraison_Loca_clicked()
{
    QString program = "C:/Users/ilyes/Desktop/Pet_Haven/ressources/MapData/debug/MapTest.exe";
    QStringList arguments;
    QProcess *chromeProcess = new QProcess(this);
    chromeProcess->start(program);
}


//******************************************************************//
//                                                                  //
//                   DONATIONS FUNCTIONS                            //
//                                                                  //
//******************************************************************//

void MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("mmarrouki52@gmail.com","Marmar21062001!","smtp.gmail.com",465);
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail("mmarrouki52@gmail.com",ui->le_email_dons->text(),"Donation success","Thank you for your support");
}
void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

void MainWindow::on_Confirmer_dons_clicked()
{

    //int id=ui->le_id->text().toInt();
   // Smtp* smtp = new Smtp("mmarrouki52@gmail.com","Marrouki21062001!","smtp.gmail.com",465);
    //connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));
    QString nom=ui->le_nom_don->text();
    QString adresse=ui->le_adresse_dons->text();
    QString email=ui->le_email_dons->text();
    int montant=ui->le_montant_dons->text().toInt();
    QDate date=ui->de_dons->date();
    Dons Dtmp(nom,adresse,email,date,montant);
    if ((Dtmp.Verif_email()) || (Dtmp.Verif_nom()) || (Dtmp.Verif_adresse()) || (Dtmp.Verif_montant_z()))
{        if(Dtmp.Verif_email())
           { ui->email_verif_dons->clear();
        ui->email_verif_dons->setText("Email doit être valide : @exemple.ex");
        ui->le_email_dons->clear();}
        if(Dtmp.Verif_nom())
           { ui->email_verif_dons->clear();
        ui->email_verif_dons->setText("Le nom doit être non vide");
        ui->le_nom_don->clear();}
        if(Dtmp.Verif_adresse())
         {   ui->email_verif_dons->clear();
        ui->email_verif_dons->setText("L'adresse doit être non vide");
        ui->le_adresse_dons->clear();}
        if(Dtmp.Verif_montant_z())
        {ui->email_verif_dons->clear();
        ui->email_verif_dons->setText("Le montant doit être different de 0");
        ui->le_montant_dons->clear();}
        /*if(Dtmp.Verif_id())
        {ui->email_verif->clear();
            ui->email_verif->setText("L'ID doit être different de 0");
        ui->le_id->clear();}*/

}
   else{
       QString s=ui->le_email_dons->text();
        ui->le_rcpt_SMTP->setText(s);

ui->email_verif_dons->clear();
    Dtmp.ajouter_dons();
    //ui->le_id->clear();
    ui->le_email_dons->clear();
    ui->le_adresse_dons->clear();
    ui->le_montant_dons->clear();
    ui->le_nom_don->clear();
    ui->de_dons->clear();
}
    ui->tableView_dons->setModel(Dtmp.afficher_dons());
    /*QString n=ui->le_nom_don->text();
    QByteArray b=b.append(n);
    A.write_to_arduino(b);*/

}

void MainWindow::on_supprimer_dons_clicked()
{
    int id=ui->le_id_Supp_dons->text().toInt();
    Dtmp.supprimer_dons(id);
    ui->tableView_dons->setModel(Dtmp.afficher_dons());
    ui->le_id_Supp_dons->clear();
}


void MainWindow::on_Refresh_dons_clicked()
{
    ui->tableView_dons->setModel(Dtmp.afficher_dons());
}

void MainWindow::on_Modifier_dons_clicked()
{

   int id = ui->le_id_Modif_dons->text().toInt();
    int montant=ui->le_montant_Modif_dons->text().toInt();
    // QString cin_string= QString::number(cin);
     QString nom=ui->le_nom_Modif_dons->text();
     QString adresse = ui->le_adresse_Modif_dons->text();
     QString email = ui->le_email_Modif_dons->text();
     QDate date_don = ui->de_Modif_dons->date();
     Dons Dtmp(nom,adresse,email,date_don,montant);
     if ((Dtmp.Verif_email()) || (Dtmp.Verif_nom()) || (Dtmp.Verif_adresse()) || (Dtmp.Verif_montant_z()) || (Dtmp.Verif_id()))
 {        if(Dtmp.Verif_email())
            { ui->email_verif_Modif_dons->clear();
         ui->email_verif_Modif_dons->setText("Email doit être valide : @exemple.ex");
          ui->le_email_Modif_dons->clear();}
         if(Dtmp.Verif_nom())
            { ui->email_verif_Modif_dons->clear();
         ui->email_verif_Modif_dons->setText("Le nom doit être non vide");
         ui->le_nom_Modif_dons->clear();}
         if(Dtmp.Verif_adresse())
          {   ui->email_verif_Modif_dons->clear();
         ui->email_verif_Modif_dons->setText("L'adresse doit être non vide");
         ui->le_adresse_Modif_dons->clear();}
         if(Dtmp.Verif_montant_z())
         {ui->email_verif_Modif_dons->clear();
         ui->email_verif_Modif_dons->setText("Le montant doit être different de 0");
          ui->le_montant_Modif_dons->clear();}
         if(Dtmp.Verif_id())
         {ui->email_verif_Modif_dons->clear();
             ui->email_verif_Modif_dons->setText("L'ID doit être different de 0");
              ui->le_id_Modif_dons->clear();}
 }
    else{
 ui->email_verif_Modif_dons->clear();
    Dtmp.modifier_dons(id);
    ui->le_id_Modif_dons->clear();
    ui->le_email_Modif_dons->clear();
    ui->le_adresse_Modif_dons->clear();
    ui->le_montant_Modif_dons->clear();
    ui->le_nom_Modif_dons->clear();
    ui->de_Modif_dons->clear();

     }
     ui->tableView_dons->setModel(Dtmp.afficher_dons());
}



void MainWindow::on_Annuler_dons_clicked()
{
    //ui->le_id->clear();
    ui->le_email_dons->clear();
    ui->le_adresse_dons->clear();
    ui->le_montant_dons->clear();
    ui->le_nom_don->clear();
    ui->de_dons->clear();
    ui->email_verif_dons->clear();
}

void MainWindow::on_Annuler_Modif_dons_clicked()
{
    ui->le_id_Modif_dons->clear();
    ui->le_email_Modif_dons->clear();
    ui->le_adresse_Modif_dons->clear();
    ui->le_montant_Modif_dons->clear();
    ui->le_nom_Modif_dons->clear();
    ui->de_Modif_dons->clear();
    ui->email_verif_Modif_dons->clear();
}

void MainWindow::on_Total_dons_clicked()
{
    //ui->label_total->clear();
    //QString ch="la somme des dons est ";

    //QString chT= ch + ch1;

    ui->tableView_T_dons->setModel(Dtmp.Total_don());
}

void MainWindow::on_le_chercher_dons_textChanged()
{
    QString recherche = ui->le_chercher_dons->text();
    if(recherche.length()!=0)
       ui->tableView_dons->setModel(Dtmp.rechercher_dons(recherche));
    else
    {
       ui->tableView_dons->setModel(Dtmp.afficher_dons());
    }
}

void MainWindow::on_PDF_dons_clicked()
{
    QString strStream;
                       QTextStream out(&strStream);

                       const int rowCount = ui->tableView_dons->model()->rowCount();
                       const int columnCount = ui->tableView_dons->model()->columnCount();
                       QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                       out <<"<html>\n"
                             "<head>\n"
                              "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                           << "<title> LISTE DES PRODUITS<title>\n "
                           << "</head>\n"
                           "<body bgcolor=#ffffff link=#5000A0>\n"
                           "<h1 style=\"text-align: center;\"><strong> **LISTE DES DONS ** "+TT+"</strong></h1>"
                           "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                             "</br> </br>";
                       // headers
                       out << "<thead><tr bgcolor=#d6e5ff>";
                       for (int column = 0; column < columnCount; column++)
                           if (!ui->tableView_dons->isColumnHidden(column))
                               out << QString("<th>%1</th>").arg(ui->tableView_dons->model()->headerData(column, Qt::Horizontal).toString());
                       out << "</tr></thead>\n";

                       // data table
                       for (int row = 0; row < rowCount; row++) {
                           out << "<tr>";
                           for (int column = 0; column < columnCount; column++) {
                               if (!ui->tableView_dons->isColumnHidden(column)) {
                                   QString data =ui->tableView_dons->model()->data(ui->tableView_dons->model()->index(row, column)).toString().simplified();
                                   out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                               }
                           }
                           out << "</tr>\n";
                       }
                       out <<  "</table>\n"
                           "</body>\n"
                           "</html>\n";

                       QTextDocument *document = new QTextDocument();
                       document->setHtml(strStream);

                       QPrinter printer;

                       QPrintDialog *test = new QPrintDialog(&printer, NULL);
                       if (test->exec() == QDialog::Accepted) {
                           document->print(&printer);
                       }

                       delete document;
}

void MainWindow::on_stats_dons_clicked()
{
    statistique_dons s;
    s.exec();
}

void MainWindow::on_envoyer_SMTP_clicked()
{
    Smtp* smtp = new Smtp(ui->le_mail_SMTP->text(), ui->le_passwd_SMTP->text(), ui->le_server_SMTP->text(), ui->le_port_SMTP->text().toInt());
       connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


       smtp->sendMail(ui->le_mail_SMTP->text(), ui->le_rcpt_SMTP->text() , ui->le_objet_SMTP->text(),"Thank you for your support");

       QMessageBox::information(nullptr, QObject::tr("Succès"),
                   QObject::tr("Le mail a été envoyé avec succès.\n"
                               "Cliquer sur Cancel to exit."), QMessageBox::Cancel);
}



//******************************************************************//
//                                                                  //
//                      ARDUINO STUFF                               //
//                                                                  //
//******************************************************************//

void MainWindow::on_Arduino_dons_clicked()
{
    QString ido;
        string conv;
        const char *texto;
        QModelIndex index=ui->tableView_dons->selectionModel()->currentIndex();
        QVariant value=index.sibling(index.row(),index.column()).data(); //will get the value of the clicked cell.
        ido=value.toString();
        conv = ido.toStdString();
        texto=conv.c_str();
    Ar.write_to_arduino(texto);
}

void MainWindow::update_dons_label()
{
data=Ar.read_from_arduino();

if(data=="1")
{
     ui->tableView_Ard_dons->setModel(Dtmp.afficher_capteur());
     QString strStream;
                        QTextStream out(&strStream);

                        const int rowCount = ui->tableView_Ard_dons->model()->rowCount();
                        const int columnCount = ui->tableView_Ard_dons->model()->columnCount();
                        QString TT = QDate::currentDate().toString("yyyy/MM/dd");
                        out <<"<html>\n"
                              "<head>\n"
                               "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                            << "<title> LISTE DES PRODUITS<title>\n "
                            << "</head>\n"
                            "<body bgcolor=#ffffff link=#5000A0>\n"
                            "<h1 style=\"text-align: center;\"><strong> **LISTE DES DONS ** "+TT+"</strong></h1>"
                            "<table style=\"text-align: center; font-size: 20px;\" border=1>\n "
                              "</br> </br>";
                        // headers
                        out << "<thead><tr bgcolor=#d6e5ff>";
                        for (int column = 0; column < columnCount; column++)
                            if (!ui->tableView_Ard_dons->isColumnHidden(column))
                                out << QString("<th>%1</th>").arg(ui->tableView_Ard_dons->model()->headerData(column, Qt::Horizontal).toString());
                        out << "</tr></thead>\n";

                        // data table
                        for (int row = 0; row < rowCount; row++) {
                            out << "<tr>";
                            for (int column = 0; column < columnCount; column++) {
                                if (!ui->tableView_Ard_dons->isColumnHidden(column)) {
                                    QString data =ui->tableView_Ard_dons->model()->data(ui->tableView_Ard_dons->model()->index(row, column)).toString().simplified();
                                    out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                }
                            }
                            out << "</tr>\n";
                        }
                        out <<  "</table>\n"
                            "</body>\n"
                            "</html>\n";

                        QTextDocument *document = new QTextDocument();
                        document->setHtml(strStream);

                        QPrinter printer;

                        QPrintDialog *test = new QPrintDialog(&printer, NULL);
                        if (test->exec() == QDialog::Accepted) {
                            document->print(&printer);
                        }

                        delete document;
}

else if (data=="0")
{
      ui->tableView_Ard_dons->setModel(Dtmp.afficher_capteur2());  // si les données reçues de arduino via la liaison série sont égales à 0
 //alors afficher ON
}
}

bool MainWindow::check()
{
    QString tmp="";
    data+=Ar.read_from_arduino();
    tmp+=QString::fromStdString(data.toStdString());
    if(tmp.size()==12)
    {
        QSqlQuery query;
        query.prepare("select * from employe WHERE keycard_token=:key_card");
        query.bindValue(":key_card",tmp);
        query.exec();

        while(query.next())
        {
            c1 = query.value(4).toString();
            c1.append(" welcome!");
            ui->label_RFID_STATUS->setText(c1);
            Ar.write_to_arduino("1");
            return true;
        }

        if(c1=="")
        {
            ui->label_RFID_STATUS->setText("Card unrecognized."); // si capteur detect
            Ar.write_to_arduino("0");
        }
    }
    return false;
}
