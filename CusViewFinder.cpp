#include "CusViewFinder.h"


CusViewFinder::CusViewFinder() :QCameraViewfinder()
{
    recMap.clear();
    actionMap.clear();
	mapIndex = 1;
	startflag = false;
    drawflag = false;
}

void CusViewFinder::enableRect()
{
    drawflag = true;
}

void CusViewFinder::disableRect()
{
    drawflag = false;
}


void CusViewFinder::paintEvent(QPaintEvent *e)
{
	QCameraViewfinder::paintEvent(e);
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

void CusViewFinder::mousePressEvent(QMouseEvent *event)
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

void CusViewFinder::mouseReleaseEvent(QMouseEvent *event)
{
	if (startflag)
	{
		startflag = false;
		endPoint.setX(event->x());
		endPoint.setY(event->y());
		if (startPoint != endPoint)
		{
            recMap.insert(mapIndex, CusRect(startPoint, endPoint, this->width(), this->height()));
            actionMap.insert(mapIndex++, " ");
            emit ListChanged(recMap,actionMap);
			update();
		}
	}
}

void CusViewFinder::mouseMoveEvent(QMouseEvent *event){
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
}

void CusViewFinder::setActionMapContent(int key, QString value)
{
    if(actionMap.contains(key))
    {
        actionMap.remove(key);
        actionMap.insert(key,value);
    }
}
