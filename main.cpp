#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QFile>
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    //open qss file
          QFile file("C:/Users/Hassène/Desktop/Gestion_Beneficiaire/Cypher.qss");
          file.open(QFile::ReadOnly);

          QString styleSheet { QString(file.readAll()) };

          //setup stylesheet
          a.setStyleSheet(styleSheet);



          Connection c;
                  bool test=c.createconnect();

                    if(test)
                        { //here if bd starts

                        QMessageBox::information(nullptr, QObject::tr("database is open"),
                                    QObject::tr("connection success.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
                              }
                        else
                            QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                                        QObject::tr("connection failed.\n"
                                                    "Click Cancel to exit."), QMessageBox::Cancel);

 MainWindow w;
w.show();
                        return a.exec();
}
