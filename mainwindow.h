#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"dons.h"
#include "smtp.h"
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
    void on_Confirmer_clicked();

    void on_supprimer_clicked();

    void on_Refresh_clicked();

    void on_Modifier_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_Annuler_clicked();

    void on_Trier_clicked();

    void on_Chercher_clicked();

    void on_Total_clicked();

    void on_comboBox_activated(const QString &arg1);

    void on_le_chercher_textChanged(const QString &arg1);

    void on_PDF_clicked();

    void on_stats_clicked();

    void on_sendBtn_clicked();

private:
    Ui::MainWindow *ui;
    Dons Dtmp;

};
#endif // MAINWINDOW_H
