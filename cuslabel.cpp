#include "cuslabel.h"

CusLabel::CusLabel(QWidget *parent):QLabel(parent)
{
    recMap.clear();
    actionMap.clear();
    tempMap.clear();
    mapIndex = 1;
    startflag = false;
    drawflag = false;
}

CusLabel::CusLabel()
{
    recMap.clear();
    actionMap.clear();
    tempMap.clear();
    mapIndex = 1;
    startflag = false;
    drawflag = false;
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
    QMapIterator<int, CusRect> iter(recMap);

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
            recMap.insert(mapIndex, CusRect(startPoint, endPoint, this->width(), this->height()));
            tempMap.insert(mapIndex," ");
            actionMap.insert(mapIndex++, " ");
            emit ListChanged(recMap,actionMap);
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
        }
    }
    update();
}

void CusLabel::setActionMapContent(int key, QString value)
{
    if(actionMap.contains(key))
    {
        actionMap.remove(key);
        actionMap.insert(key,value);
    }
}

void CusLabel::setTempsMapContent(int key, QString value)
{
    if(tempMap.contains(key))
    {
        tempMap.remove(key);
        tempMap.insert(key,value);
    }
}

void CusLabel::removeRectMapContent(int key)
{
    if(actionMap.contains(key))
    {
        actionMap.remove(key);
    }
    if(recMap.contains(key))
    {
        recMap.remove(key);
    }
    if(tempMap.contains(key))
    {
        tempMap.remove(key);
    }
    emit ListChanged(recMap,actionMap);
}

