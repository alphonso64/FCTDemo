#include "util.h"

Util::Util()
{

}

void Util::imageFormat(QImage *image, QColor color)
{
    for(int i=0;i<image->height();i++){
        for(int j=0;j<image->width();j++){
            image->setPixel(j,i,255);
        }
    }
}
