#include "../headers/livraison.h"
#include "../headers/newcalendarwidget.h"


NewCalendarWidget::NewCalendarWidget(QWidget *parent)
   : QCalendarWidget(parent)
{
    m_currentDate.clear();
    Livraison L;
    QList<QVariant> list = L.fetchDates();
    for (int i = 0; i < list.size(); i++) {
       m_currentDate.append( list[i].toDate() );
    }

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

   for (int i = 0; i < m_currentDate.size(); i++) {
       if (date == m_currentDate[i]) {
           painter->setPen(m_outlinePen);
           painter->setBrush(m_transparentBrush);
           painter->drawRect(rect.adjusted(0, 0, -1, -1));
       }
   }

//   if (date == m_currentDate)
//   {
//       painter->setPen(m_outlinePen);
//       painter->setBrush(m_transparentBrush);
//       painter->drawRect(rect.adjusted(0, 0, -1, -1));
//   }
}
