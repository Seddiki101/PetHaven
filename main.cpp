#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>
#include <QFile>
#include "adoption.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;
        bool test=c.createconnect();
MainWindow w;

    //open qss file
          QFile file("B:/project/QT/p1/gestion_Adoptions/Cypher.qss");
          file.open(QFile::ReadOnly);

          QString styleSheet { QString(file.readAll()) };

          //setup stylesheet
          a.setStyleSheet(styleSheet);



    //w.show();
    //return a.exec();
          if(test)
              { //here if bd starts
              w.show();
              QMessageBox::information(nullptr, QObject::tr("database is open"),
                          QObject::tr("connection success.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
                    }
              else
                  QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                              QObject::tr("connection failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);



              return a.exec();

}
