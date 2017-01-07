#pragma once
#include <QRect>

typedef struct replybuf
{
    uchar id;
    uchar grayscale;
    uchar r;
    uchar g;

    uchar b;
    uchar number;
    uchar state;
    uchar rev;

    uint  similarity;

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
private:
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
