#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "headers/SwitchButton.h"
#include "headers/arduino.h"

#include "headers/employe.h"

#include "headers/animal.h"


#include <QMainWindow>
#include <QMessageBox>
#include <QValidator>
#include <QDebug>



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
    // SHARED FUNCTIONS
    void toggle_stylesheet(QString path);       // Switch to a given Theme given its filepath
    void switch_switchClicked();                // Manage the Black/White themes
    void on_Connect_Button_clicked();           // Belongs to Employee but is technically global
    void on_Gestions_Employees_clicked();       // Switch to Employees page
    void on_Gestion_Adoptions_clicked();        // Switch to Adoptions page
    void on_Gestion_Animals_clicked();          // Switch to Animals page
    void on_Gestion_Beneficiaries_clicked();    // You got the logic at this point
    void on_Gestion_Deliveries_clicked();
    void on_Gestion_Donations_clicked();

    // GESTION EMPLOYEE FUNCTIONS
    void on_Employee_Ajouter_clicked();
    void on_Employee_Supprimer_clicked();
    void on_Employee_Modifier_clicked();
    void on_Employee_Sort_clicked();
    void on_Employee_search_clicked();
    void on_Employee_Search_label_textChanged();
    void on_Employee_PDF_clicked();
    void on_Employee_Appreciation_clicked();

    // GESTION ADOPTIONS FUNCTIONS

    // GESTION ANIMALS FUNCTIONS
    void on_animal_btn_Refresh_clicked();
    void on_animal_btn_Add_clicked();
    void on_animal_btn_Update_clicked();
    void on_animal_btn_Delete_clicked();
    void on_animal_btn_Upload_clicked();
    void on_animal_btn_Sort_clicked();
    void on_animal_le_Search_textChanged();
    void on_animal_btn_PDF_clicked();
    void header_headerClicked();
    void on_animal_tableView_clicked(const QModelIndex &);

    // GESTION BENEFICIARIES FUNCTIONS

    // GESTION DELIVERIES FUNCTIONS

    // GESTION DONATIONS FUNCTIONS


    // Arduino functions


private:
    Ui::MainWindow *ui;

    // Definition of all GESTION classes
    Employe E;
    Animal A;

    // Some Arduino thingies
    Arduino Ar;
    QByteArray data;
};


#endif // MAINWINDOW_H
