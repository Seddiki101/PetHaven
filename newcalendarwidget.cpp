#include <QPainter>
#include <QDebug>
#include "livraison.h"
#include "newcalendarwidget.h"

NewCalendarWidget::NewCalendarWidget(QWidget *parent)
   : QCalendarWidget(parent)
{
   m_currentDate = QDate::currentDate().addDays(1);
   qDebug() << QDate::currentDate();
   m_outlinePen.setColor(Qt::red);
   m_transparentBrush.setColor(Qt::transparent);
}

NewCalendarWidget::~NewCalendarWidget()
{

}

void NewCalendarWidget::setColor(QColor& color)
{
   m_outlinePen.setColor(color);
}

QColor NewCalendarWidget::getColor()
{
   return (m_outlinePen.color());
}

void NewCalendarWidget::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
   QCalendarWidget::paintCell(painter, rect, date);

   if (date == m_currentDate)
   {
       painter->setPen(m_outlinePen);
       painter->setBrush(m_transparentBrush);
       painter->drawRect(rect.adjusted(0, 0, -1, -1));
   }
}
