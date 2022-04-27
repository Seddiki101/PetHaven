#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "animal.h"
#include "arduino.h"

#include <QMainWindow>
#include <QMessageBox>
#include <QValidator>



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
    void on_animal_btn_Refresh_clicked();

    void on_animal_btn_Add_clicked();

    void on_animal_btn_Update_clicked();

    void on_animal_btn_Delete_clicked();

    void on_animal_btn_Sort_clicked();

    void on_animal_btn_PDF_clicked();

    void on_animal_le_Search_textChanged();

    void Animal_Blackmode();

    void Animal_Whitemode();

    void on_animal_btn_Upload_clicked();

    void on_animal_tableView_clicked(const QModelIndex &);

    void header_headerClicked();

    void switch_switchClicked();

    void toggle_stylesheet(QString);

private:
    Ui::MainWindow *ui;
    Animal A;
};


#endif // MAINWINDOW_H
