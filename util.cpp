#include "util.h"
#include <QDebug>
TUtil::TUtil()
{

}

void TUtil::imageFormat(QImage *image, QColor color)
{
    for(int i=0;i<image->height();i++){
        for(int j=0;j<image->width();j++){
            image->setPixel(j,i,255);
        }
    }
}

void TUtil::bmpconvertToRGBA(QImage image, uint *dst)
{
    int temp = 0;
    for (int ii = 0; ii < image.height(); ii++) {
        uchar* scan = image.scanLine(ii);
        for (int jj = 0; jj < image.width(); jj++) {
            QRgb* rgbpixel = reinterpret_cast<QRgb*>(scan + jj*4);
            dst[temp++] = * rgbpixel ;//*rgbpixel;

        }
    }
}

void TUtil::camconvertToRGBA(QImage image, uint *dst)
{
    int temp = 0;
    for (int ii = 0; ii < image.height(); ii++) {
        uchar* scan = image.scanLine(ii);
        for (int jj = 0; jj < image.width(); jj++) {
            int offset = jj *3;
            uint blue = *(scan+offset);
            uint green = *(scan+offset+1);
            uint red = *(scan+offset+2);
            dst[temp++] = (blue<<16) + (green << 8) +(red) ;//*rgbpixel;
        }
    }
}
