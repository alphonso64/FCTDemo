#include "cuslabel.h"

CusLabel::CusLabel(QWidget *parent):QLabel(parent)
{

    startflag = false;
    drawflag = false;
    regular = new Regular();
}

CusLabel::CusLabel()
{
    startflag = false;
    drawflag = false;
    regular = new Regular();
}

void CusLabel::enableRect()
{
    drawflag = true;
}

void CusLabel::disableRect()
{
    drawflag = false;
}


void CusLabel::paintEvent(QPaintEvent *e)
{
    QLabel::paintEvent(e);
    QPainter p(this);
    p.setPen(QPen(Qt::red, 1));
    QMapIterator<int, CusRect> iter(regular->recMap);
    if (startflag)
    {
        if (startPoint != endPoint)
        {
            p.drawRect(QRect(startPoint, endPoint));
        }
    }
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

void CusLabel::mousePressEvent(QMouseEvent *event)
{
    if(drawflag)
    {
        startflag = true;
        startPoint.setX(event->x());
        startPoint.setY(event->y());
        endPoint.setX(event->x());
        endPoint.setY(event->y());
    }
}

void CusLabel::mouseReleaseEvent(QMouseEvent *event)
{
    if (startflag)
    {
        startflag = false;
        endPoint.setX(event->x());
        endPoint.setY(event->y());
        if (startPoint != endPoint)
        {
            regular->recMap.insert(regular->mapIndex, CusRect(startPoint, endPoint, this->width(), this->height()));
            regular->tempsMap.insert(regular->mapIndex, PatternFile());
            regular->actionMap.insert(regular->mapIndex++, " ");
            emit ListChanged(regular->recMap,regular->actionMap);
            update();
        }
    }
}

void CusLabel::mouseMoveEvent(QMouseEvent *event){
    int x = event->x();
    int y = event->y();

    if(drawflag)
    {
        if (x<0 || x>this->width() || y<0 || y>this->height()){
            startflag = false;
        }
        else{
            if (startflag){
                endPoint.setX(x);
                endPoint.setY(y);
            }
            update();
        }
    }
}

Regular* CusLabel::getRegular()
{
    return regular;
}

