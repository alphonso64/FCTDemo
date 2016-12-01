#include "paintlabel.h"
#include <QPainter>
#include <QDebug>

PaintLabel::PaintLabel(QWidget *parent):QLabel(parent)
{
}
void PaintLabel::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);
    QPainter p(this);
    p.setPen(QPen(Qt::red, 1));
    QMapIterator<int, CusRect> iter(recMap);

    while (iter.hasNext())
    {
        iter.next();
        CusRect rect = iter.value();
        QRect rec = rect.getRect(this->width(), this->height());
        p.drawRect(rec);
        p.setPen(QPen(Qt::blue, 1));
        p.drawText(rec.topLeft(), QString::number(iter.key()));
        p.setPen(QPen(Qt::red, 1));
    }
}
