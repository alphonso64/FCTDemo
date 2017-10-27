#ifndef TUTIL_H
#define TUTIL_H
#include <QImage>

class TUtil
{
public:
    TUtil();
    static void imageFormat(QImage *image,QColor color);
    static void bmpconvertToRGBA(QImage image,uint *dst);
    static void camconvertToRGBA(QImage image,uint *dst);
    static int  checkUSBKEY();
};

#endif // UTIL_H
