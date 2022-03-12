#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "adoption.h"
#include "popup.h"

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
    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_refresh_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_adopdf_clicked();

    void on_adocsv_clicked();


private:
    Ui::MainWindow *ui;
Adoption dope;
animal annie;
patient pato;
PopUp *popUp;
};
#endif // MAINWINDOW_H
