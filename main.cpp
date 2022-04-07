#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QFile>
#include <QMessageBox>
#include <QTranslator>
#include <QInputDialog>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QTranslator t;
    QStringList languages;
    languages << "EN" << "FR";
    QString lang = QInputDialog::getItem(NULL,"Select Language", "Language",languages);
    if(lang=="FR")
    {
    t.load(":/translations/application_fr_FR.qm");
    }

    if(lang!="EN")
    a.installTranslator(&t);
    //open qss file
          QFile file("C:/Users/Hassène/Desktop/Unnamed/academics/2ème/S2/Qt/Gestion_Beneficiaire/Cypher.qss");
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

                    QTranslator translator;
                        const QStringList uiLanguages = QLocale::system().uiLanguages();
                        for (const QString &locale : uiLanguages) {
                            const QString baseName = "tuto_" + QLocale(locale).name();
                            if (translator.load(":/i18n/" + baseName)) {
                                a.installTranslator(&translator);
                                break;
                            }
                        }
                        MainWindow w;
w.show();

                        return a.exec();
}
