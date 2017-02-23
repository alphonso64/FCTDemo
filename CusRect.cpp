#include "CusRect.h"
CusRect::CusRect()
{
    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;
}

CusRect::CusRect(float x1, float y1, float x2, float y2)
{
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
    validate = true;
}

CusRect::CusRect(QPoint start, QPoint end, int width, int height)
{
	int temp1, temp2;
	temp1 = qMin(start.x(),end.x());
	temp2 = qMax(start.x(), end.x());
	x1 = (float)temp1 / width;
	x2 = (float)temp2 / width;

	temp1 = qMin(start.y(), end.y());
	temp2 = qMax(start.y(), end.y());
	y1 = (float)temp1 / height;
	y2 = (float)temp2 / height;
    validate = true;
}



CusRect::~CusRect()
{

}

QRect CusRect::getRect(int width, int height)
{
	QPoint start(x1*width, y1*height);
	QPoint end(x2*width, y2*height);
	return QRect(start, end);
}

CusReplyData::~CusReplyData()
{

}

CusReplyData::CusReplyData()
{

}
