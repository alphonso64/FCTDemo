#include "cuslabel.h"

CusLabel::CusLabel(QWidget *parent):QLabel(parent)
{
    startflag = false;
    drawflag = false;
    trans_startflag = false;
    trans_drawflag = false;
    regular_list[0] = new Regular();
    regular_list[1] = new Regular();
    regular_list[2] = new Regular();
    regular = regular_list[0];
}

CusLabel::CusLabel()
{
    startflag = false;
    drawflag = false;
    trans_startflag = false;
    trans_drawflag = false;
    regular_list[0] = new Regular();
    regular_list[1] = new Regular();
    regular_list[2] = new Regular();
    regular = regular_list[0];
}

void CusLabel::enableRect()
{
    drawflag = true;
}

void CusLabel::disableRect()
{
    drawflag = false;
}

void CusLabel::enableTransRect()
{
    trans_drawflag = true;
}
void CusLabel::disableTransRect()
{
    trans_drawflag = false;
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
    if (trans_startflag)
    {
        p.setPen(QPen(Qt::yellow, 1));
        if (trans_startPoint != trans_endPoint)
        {
            p.drawRect(QRect(trans_startPoint, trans_endPoint));
        }
        p.setPen(QPen(Qt::red, 1));
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
    {
        p.setPen(QPen(Qt::yellow, 1));
        QRect rec = regular->transRec.getRect(this->width(), this->height());
        p.drawRect(rec);
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
    if(trans_drawflag)
    {
        trans_startflag = true;
        trans_startPoint.setX(event->x());
        trans_startPoint.setY(event->y());
        trans_endPoint.setX(event->x());
        trans_endPoint.setY(event->y());
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

    if (trans_startflag)
    {
        trans_startflag = false;
        trans_endPoint.setX(event->x());
        trans_endPoint.setY(event->y());
        if (trans_startPoint != trans_endPoint)
        {
            regular->transRec = CusRect(trans_startPoint, trans_endPoint, this->width(), this->height());
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

    if(trans_drawflag)
    {
        if (x<0 || x>this->width() || y<0 || y>this->height()){
            trans_startflag = false;
        }
        else{
            if (trans_startflag){
                trans_endPoint.setX(x);
                trans_endPoint.setY(y);
            }
            update();
        }
    }
}

Regular* CusLabel::getRegular()
{
    return regular;
}

Regular* CusLabel::getRegular(int index)
{
    return regular_list[index];
}

void CusLabel::changeRegular(int index)
{
    regular = regular_list[index];
    emit ListChanged(regular->recMap,regular->actionMap);
}


