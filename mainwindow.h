#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"dons.h"
#include "smtp.h"
#include "arduino.h"
#include <QMainWindow>

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

    void sendMail();
    void mailSent(QString);
    void on_Confirmer_dons_clicked();

    void on_supprimer_dons_clicked();

    void on_Refresh_clicked();

    void on_Modifier_dons_clicked();

    void on_pushButton_clicked();

    void on_Annuler_dons_clicked();

    void on_Annuler_Modif_dons_clicked();

    void on_Trier_clicked();

    void on_Chercher_clicked();

    void on_Total_dons_clicked();

    void on_comboBox_dons_activated(const QString &arg1);

    void on_le_chercher_dons_textChanged(const QString &arg1);

    void on_PDF_dons_clicked();

    void on_stats_dons_clicked();

    void on_envoyer_SMTP_clicked();

    void on_Arduino_dons_clicked();
    void update_label();

private:
    Ui::MainWindow *ui;
    Dons Dtmp;
    QByteArray data;
    Arduino A;

};
#endif // MAINWINDOW_H
