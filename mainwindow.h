#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "adoption.h"

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

    void on_LEsearch_textChanged(const QString &arg1);

    void on_qr_clicked();

    void on_Total_clicked();

    void on_stat_clicked();

private:
    Ui::MainWindow *ui;
Adoption dope;
animal annie;
patient pato;
};
#endif // MAINWINDOW_H
