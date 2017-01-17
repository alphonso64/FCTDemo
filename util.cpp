#include "util.h"

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

void TUtil::convertToRGBA(QImage image, uint *dst, int depth)
{
    int temp = 0;
    for (int ii = 0; ii < image.height(); ii++) {
        uchar* scan = image.scanLine(ii);
        for (int jj = 0; jj < image.width(); jj++) {
            QRgb* rgbpixel = reinterpret_cast<QRgb*>(scan + jj*depth);
            dst[temp++] = *rgbpixel;

        }
    }
}
