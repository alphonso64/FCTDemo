#ifndef TUTIL_H
#define TUTIL_H
#include <QImage>

class TUtil
{
public:
    TUtil();
    static void imageFormat(QImage *image,QColor color);
    static void convertToRGBA(QImage image,uint *dst,int depth);
};

#endif // UTIL_H
