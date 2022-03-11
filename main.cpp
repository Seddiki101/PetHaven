#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QMessageBox>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;
    bool test=c.createconnect();
        MainWindow w;
    //open qss file
              QFile file("C:/Users/mmarr/OneDrive/Bureau/Dons/interface/Cypher.qss");
              file.open(QFile::ReadOnly);

                  if(test)
                  {w.show();
                      QMessageBox::information(nullptr, QObject::tr("database is open"),
                                  QObject::tr("connection successful.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);

              }
                  else
                      QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                                  QObject::tr("connection failed.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);

                  QString styleSheet { QString(file.readAll()) };

                  //setup stylesheet
                  a.setStyleSheet(styleSheet);
        w.show();

                  return a.exec();
              }
