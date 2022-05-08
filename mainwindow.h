#ifndef MAINWINDOW_H
#define MAINWINDOW_H


//---SHARED---//
#include "headers/SwitchButton.h"
#include "headers/arduino.h"
//------------//

//---EMPLOYEES---//
#include "headers/employe.h"
//---------------//

//---ADOPTIONS---//
#include "headers/adoption.h"
#include "headers/statistique_adoptions.h"
#include <cstdlib>
#include <climits>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
//-------------//

//---ANIMALS---//
#include "headers/animal.h"
//-------------//

//---BENEFICIARIES--//
#include "headers/beneficiaire.h"
#include "headers/statistique_beneficiaires.h"
//-----------------//

//---DELIVERIES---//
#include "headers/livraison.h"
//---------------//

//---DONS---//
#include "headers/dons.h"
#include "headers/smtp.h"
#include "headers/statistique_dons.h"
//----------//


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
    bool notifstate=false; // FOR METIER BENEFICIAIRER

private slots:
    // SHARED FUNCTIONS
    void toggle_stylesheet(QString path);       // Switch to a given Theme given its filepath
    void switch_switchClicked();                // Manage the Black/White themes
    void on_Connect_Button_clicked();           // Belongs to Employee but is technically global
    void on_Disconnect_Button_clicked();        // Send the user to the first page and clear "login" variable
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
    void on_addopage_clicked();
    void on_supado_clicked();
    void on_sortado_clicked();
    void on_searchado_clicked();
    void on_refresh_clicked();
    void on_updatePage_clicked();
    void on_adopdf_clicked();
    void on_adocsv_clicked();
    void on_Back_clicked();
    void on_back2_clicked();
    void on_upado_clicked();
    void on_addado_clicked();
    void on_LEsearch_textChanged();
    void on_qr_clicked();
    void on_Total_clicked();
    void on_stat_clicked();

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
    void on_BENEFICIAIRE_pushButton_AddNew_clicked();
    void on_BENEFICIAIRE_pushButton_Delete_clicked();
    void on_BENEFICIAIRE_pushButton_ConfirmChanges_clicked();
    void on_BENEFICIAIRE_pushButton_GotoEdit_clicked();
    void on_BENEFICIAIRE_lineEdit_Search_textChanged();
    void on_BENEFICIAIRE_pushButton_Sort_clicked();
    void on_BENEFICIAIRE_pushButton_ExportPDF_clicked();
    void on_BENEFICIAIRE_pushButton_Statistics_clicked();
    void notifs();
    QString LoadLastnotif();
    void saveLastnotif();
    void notifs2();
    void on_BENEFICIAIRE_pushButton_Notifications_clicked();

    // GESTION DELIVERIES FUNCTIONS
    void on_Livraison_btn_Refresh_clicked();
    void on_Livraison_btn_Search_clicked();
    void on_Livraison_btn_Add_clicked();
    void on_Livraison_btn_Update_clicked();
    void on_Livraison_btn_Delete_clicked();
    void on_Livraison_btn_Sort_clicked();
    void on_Livraison_btn_PDF_clicked();
    void on_Livraison_le_Search_textChanged();
    void on_Livraison_Loca_clicked();

    // GESTION DONATIONS FUNCTIONS
    void sendMail();
    void mailSent(QString);
    void on_Confirmer_dons_clicked();
    void on_supprimer_dons_clicked();
    void on_Refresh_dons_clicked();
    void on_Modifier_dons_clicked();
    void on_Annuler_dons_clicked();
    void on_Annuler_Modif_dons_clicked();
    void on_Total_dons_clicked();
    void on_le_chercher_dons_textChanged();
    void on_PDF_dons_clicked();
    void on_stats_dons_clicked();
    void on_envoyer_SMTP_clicked();

    // Arduino functions
    void on_Arduino_dons_clicked();
    void update_dons_label();
    bool check();

private:
    Ui::MainWindow *ui;

// Definition of the GESTION classes
    Employe E;
    Adoption Ad;
    Animal A;
    Beneficiaire B;
    Livraison L;
    Dons Dtmp;

// Some important global variables
    QString login;      // Keep the login just in case
    QTimer * timer;     //FOR NOTIFICATION BENEFICIAIRE
    QString c1="";      //FOR ARDUINO RFID LOGIN SYSTEM

// Some Arduino thingies
    Arduino Ar;
    QByteArray data;
};


#endif // MAINWINDOW_H
