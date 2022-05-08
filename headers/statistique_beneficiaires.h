#ifndef STATISTIQUE_BENEFICIAIRES_H_INCLUDED
#define STATISTIQUE_BENEFICIAIRES_H_INCLUDED

#include <QDialog>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QPainter>
#include <QSqlQuery>

using namespace std;

namespace Ui {class statistique_beneficiaires;}

class statistique_beneficiaires : public QDialog
{
    Q_OBJECT

public:
    explicit statistique_beneficiaires(QWidget *parent = nullptr);

    int Statistique_beneficiaires_partie2();
    int Statistique_beneficiaires_partie3();
    int Statistique_partie4() ;
    int Statistique_partie5() ;

    void paintEvent(QPaintEvent *) ;

    ~statistique_beneficiaires();

private:
    Ui::statistique_beneficiaires *ui;
private slots :
};

#endif // STATISTIQUE_BENEFICIAIRES_H_INCLUDED
