#include "mainwindow.h"
#include "connexion.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connexion c;
    c.createconnect();

    MainWindow w;

    //open qss file
    QFile file(":/ressources/DarkTheme.qss");
    file.open(QFile::ReadOnly);

    QString styleSheet { QString(file.readAll()) };

    //setup stylesheet
    a.setStyleSheet(styleSheet);

    w.show();

    // Prompt if the connexion to the database has been successfull
//    bool test=c.createconnect();
//    if(test)
//    {
//        w.show();
//        QMessageBox::information(nullptr, QObject::tr("database is open"),
//            QObject::tr("connection successful.\n"
//                "Click Ok to exit."), QMessageBox::Ok);
//    }
//    else
//    {
//        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
//            QObject::tr("connection failed.\n"
//                "Click Cancel to exit."), QMessageBox::Cancel);
//    }

    return a.exec();
}

