#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "beneficiaire.h"
#include <QTimer>
#include <QStringListModel>
#include <QStandardItemModel>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
void on_pushButton_3_clicked();
void on_pushButton_4_clicked();
void on_pushButton_7_clicked();


void on_pushButton_5_clicked();

void on_lineEdit_search_textChanged(const QString &arg1);

void on_pushButton_clicked();

void on_pushButton_6_clicked();

void on_pushButton_8_clicked();

void notifs();



void on_pushButton_16_clicked();

private:
    Ui::MainWindow *ui;
    Beneficiaire B;
    QTimer * timer;
};
#endif // MAINWINDOW_H
