#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"livraison.h"
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
    void on_Livraison_btn_Refresh_clicked();

    void on_Livraison_btn_Search_clicked();

    void on_Livraison_btn_Add_clicked();

    void on_Livraison_btn_Update_clicked();

    void on_Livraison_btn_Delete_clicked();

    void on_Livraison_btn_Sort_clicked();

    void on_Livraison_btn_PDF_clicked();

    void on_Livraison_le_Search_textChanged(const QString &arg1);

    void on_Livraison_tableView_activated(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Livraison L;
};
#endif // MAINWINDOW_H
