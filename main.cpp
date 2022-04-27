#include "mainwindow.h"
#include "connexion.h"
#include <QApplication>
#include <QMessageBox>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connexion c;
    bool test=c.createconnect();

    MainWindow w;

    //open qss file
    QFile file(":/ressources/DarkTheme.qss");
    file.open(QFile::ReadOnly | QFile::Text);

    //setup stylesheet
    a.setStyleSheet(QString(file.readAll()));
    a.setApplicationName("Cypher Gestion App");

    if(test)
    {
        w.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
            QObject::tr("connection successful.\n"
                "Click Ok to exit."), QMessageBox::Ok);
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
            QObject::tr("connection failed.\n"
                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    return a.exec();
}
