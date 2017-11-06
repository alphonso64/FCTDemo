#ifndef TUTIL_H
#define TUTIL_H
#include <QImage>

#include "const_define.h"
class TUtil
{
public:
    TUtil();
    static void imageFormat(QImage *image,QColor color);
    static void bmpconvertToRGBA(QImage image,uint *dst);
    static void camconvertToRGBA(QImage image,uint *dst);
#ifdef USBCHECK
    static int  checkUSBKEY();
#endif
};

#endif // UTIL_H
