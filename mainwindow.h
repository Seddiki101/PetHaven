#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "animal.h"
#include <QMainWindow>
#include <QCheckBox>
#include <QMessageBox>
#include <QIntValidator>
#include <QtDebug>

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
    void on_btn_Refresh_clicked();

    void on_btn_Search_clicked();

    void on_btn_Add_clicked();

    void on_btn_Update_clicked();

    void on_btn_Delete_clicked();

    void on_btn_Sort_clicked();

    void on_btn_PDF_clicked();

private:
    Ui::MainWindow *ui;
    Animal A;
};
#endif // MAINWINDOW_H
