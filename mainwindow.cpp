#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDate>
#include <cstdlib>
#include "adoption.h"
#include "stat.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ctrl de saisi

    ui->lineEdit_8->setValidator(new QIntValidator(0,999999,this));   // id modif animal
    ui->lineEdit_9->setValidator(new QIntValidator(0,999999,this));   // id modif beneficiaire


    ui->tableView_2->setModel(pato.afficher());
    ui->tableView_3->setModel(annie.afficher());
    ui->tableView->setModel(dope.afficher());
    ui->tableView_4->setModel(dope.afficher());

}

MainWindow::~MainWindow()
{
    delete ui;
}



///////////////////////////////////////////////////////////////////////////////////////
#include <climits>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include "qrcodegen.hpp"
#include "adoption.h"


using std::uint8_t;
using qrcodegen::QrCode;
using qrcodegen::QrSegment;


// Function prototypes
static void dosicDemo(char * text);

static std::string toSvgString(const QrCode &qr, int border);
static void printQr(const QrCode &qr);


// The main application program.
/*
int main() {
    char *texto = "Hello, world!";
    dosicDemo(texto);
    return EXIT_SUCCESS;
}
*/


/*---- Demo suite ----*/



static void dosicDemo(const char * text) {
    const QrCode::Ecc errCorLvl = QrCode::Ecc::LOW;  // Error correction level

    // Make and print the QR Code symbol
    const QrCode qr = QrCode::encodeText(text, errCorLvl);
	//Directory here
    QString file = "C:/Users/k/Desktop/cpp/qr.svg";
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










/*---- Utilities ----*/

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











////////////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushButton_clicked()
{
      ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_addopage_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

//ajouter
void MainWindow::on_addado_clicked()
{
    int idp,ida,ido;
    QDate d=QDate::currentDate();
    ido = 1+ (rand() % 1000);  // this is removed when auto increment is fixed


    QModelIndex index=ui->tableView_2->selectionModel()->currentIndex();
    QVariant value=index.sibling(index.row(),index.column()).data(); //will get the value of the clicked cell.
    idp=value.toInt();

    QModelIndex index2=ui->tableView_3->selectionModel()->currentIndex();
    QVariant value2=index2.sibling(index2.row(),index2.column()).data(); //will get the value of the clicked cell.
    ida=value2.toInt();


    Adoption A(ido,ida,idp,d);
    A.ajouter();
     ui->tableView->setModel(dope.afficher());

 ui->stackedWidget->setCurrentIndex(1);

}

//supprimer
void MainWindow::on_supado_clicked()
{

    int id;
        QModelIndex index=ui->tableView->selectionModel()->currentIndex();
        QVariant value=index.sibling(index.row(),index.column()).data(); //will get the value of the clicked cell.
        id=value.toInt();

    Adoption A;

   A.supprimer(id);
    ui->tableView->setModel(dope.afficher());


}

void MainWindow::on_sortado_clicked()
{
    if (ui->radioButton) {
    ui->tableView->setModel(dope.triDates());}


    if (ui->radioButton_2) {
    ui->tableView->setModel(dope.triAlpha());}
}


void MainWindow::on_searchado_clicked()
{
Adoption A;

QString recherche = ui->LEsearch->text();
 ui->tableView->setModel(A.chercher(recherche));

}

void MainWindow::on_refresh_clicked()
{
    ui->tableView->setModel(dope.afficher());
    ui->tableView_2->setModel(dope.afficher());
    ui->tableView_3->setModel(dope.afficher());
    ui->tableView_4->setModel(dope.afficher());
}

void MainWindow::on_upado_clicked()
{
// modifier
    Adoption A;
    int ida,idp,ido;
    QModelIndex index=ui->tableView_4->selectionModel()->currentIndex();
    QVariant value=index.sibling(index.row(),index.column()).data(); //will get the value of the clicked cell.
    ido=value.toInt();

    idp=ui->lineEdit_8->text().toInt();
    ida=ui->lineEdit_9->text().toInt();

bool test=A.modifier(ido,idp,ida);

ui->stackedWidget->setCurrentIndex(1);
//if(test)
}

void MainWindow::on_updatePage_clicked()
{
ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_adocsv_clicked()
{
    Adoption A;
    A.genereExcel(ui->tableView);
}

void MainWindow::on_adopdf_clicked()
{
 Adoption A;
 A.generatePdf(ui->tableView);
}

void MainWindow::on_Back_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_back2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}



void MainWindow::on_LEsearch_textChanged(const QString &arg1)
{
    Adoption A;

    QString recherche = ui->LEsearch->text();
     ui->tableView->setModel(A.search(recherche));

}

void MainWindow::on_qr_clicked()
{
    //char *texto = "Hello, world!";
    QString ido;
    string conv;
    const char *texto;
    QModelIndex index=ui->tableView->selectionModel()->currentIndex();
    QVariant value=index.sibling(index.row(),index.column()).data(); //will get the value of the clicked cell.
    ido=value.toString();
    conv = ido.toStdString();
    texto=conv.c_str();


    //texto= ido.toStdString().c_str(); str.toLocal8Bit().constData()
    dosicDemo(texto);

//
    // Create the QR Code object
    /*
    QString text="yes";
    QrCode qr = QrCode::encodeText( text.toUtf8().data(), QrCode::Ecc::MEDIUM );
              qint32 sz = qr.getSize();
              QImage im(sz,sz, QImage::Format_RGB32);
                QRgb black = qRgb(  0,  0,  0);
                QRgb white = qRgb(255,255,255);
              for (int y = 0; y < sz; y++)
                for (int x = 0; x < sz; x++)
                  im.setPixel(x,y,qr.getModule(x, y) ? black : white );
              ui->qrCode->setPixmap( QPixmap::fromImage(im.scaled(256,256,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );
  */

//

}



void MainWindow::on_Total_clicked()
{
    Adoption A;
    ui->tableView->setModel(dope.Totado());
A.generatePdf(ui->tableView);
}

void MainWindow::on_stat_clicked()
{
    statistique s;
        s.exec();
}
