#pragma once
#include <QRect>

typedef struct replybuf
{
    uint id;
    uint grayscale;
    uint r;
    uint g;

    uint b;
    uint number;
    uint state;
    uint rev;

    uint  similarity;

    uint  left;
    uint  up;
    uint  width;
    uint  height;

    uint  pimg;
}REPLYBUF;

class CusRect
{
public:
    CusRect();
	CusRect(float x1,float y1,float x2, float y2);
	CusRect(QPoint start, QPoint end, int width, int height);
	~CusRect();

    QRect getRect(int width, int height);

    bool validate;
	float x1, x2, y1, y2;
};

class CusReplyData
{
public:
    CusReplyData();
    ~CusReplyData();
public:
    REPLYBUF replybuffer;
};
