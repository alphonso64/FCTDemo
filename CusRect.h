#pragma once
#include <QRect>
class CusRect
{
public:
	CusRect(float x1,float y1,float x2, float y2);
	CusRect(QPoint start, QPoint end, int width, int height);
	~CusRect();

    QRect getRect(int width, int height);

    bool validate;
private:
	float x1, x2, y1, y2;
};

