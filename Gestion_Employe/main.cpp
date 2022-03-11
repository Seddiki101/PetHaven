#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connexion.h"
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connexion c;
        bool test=c.createconnect();
         MainWindow w;
         //open qss file
                  QFile file("C:/Users/zaibi/OneDrive/Bureau/C++/Gestion_Employe/Cypher.qss");
                  file.open(QFile::ReadOnly);

                  QString styleSheet { QString(file.readAll()) };

                  //setup stylesheet
                  a.setStyleSheet(styleSheet);
        if(test)
        {
            w.show();
            QMessageBox::information(nullptr, QObject::tr("database is open"),
                        QObject::tr("connection successful.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

    }
        else
            QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                        QObject::tr("connection failed.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);


    return a.exec();
}