#ifndef STATISTIQUE_DONS_H_INCLUDED
#define STATISTIQUE_DONS_H_INCLUDED

#include <QDialog>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QPainter>
#include <QSqlQuery>

using namespace std;

namespace Ui {class statistique_dons;}

class statistique_dons : public QDialog
{
    Q_OBJECT

public:
    explicit statistique_dons(QWidget *parent = nullptr);

    int Statistique_dons_partie2() ;
    int Statistique_dons_partie3() ;

    void paintEvent(QPaintEvent *) ;

    ~statistique_dons();

private:
    Ui::statistique_dons *ui;
private slots :
};

#endif // STATISTIQUE_DONS_H_INCLUDED
