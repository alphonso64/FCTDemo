#include "util.h"
#include <QDebug>
#include "hasp_api.h"
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
#ifdef USBCHECK
int TUtil::checkUSBKEY()
{
    int val = 0;

    hasp_status_t status;
    char *info = 0;

    const char* scope =
    "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
    "<haspscope/>";

    const char* format =
    "<haspformat>"
    "<product>"
    "    <element name=\"id\"/>"
    "    <element name=\"name\"/>"
    "</product>"
    "</haspformat>";

    unsigned char vendor_code[] =
    "mHWtElAogwzvkMYEzRveIA2cSeMx3PYhkdPk94tU7QMl31zLDW7X1f1fdeMdLBhOfyv8qonpVLLY3J/f"
    "tcPNogODqfNeXZ1y2nxtc+eClT4SCSK0G4i1fw2RfUklxFS0FwTSsENZP29sk+bJIpTZ4EryWWEC2kKn"
    "r1lOt7D9XHpKXsJBJ+WzlbmGPLfYtuhJ3Y04eZfdg5Upcxym82qTi7u7kQwi07jppobknIs0uEjUpsEQ"
    "3AX5Z779fz75kCH3ac1Uvj6W1Tmjb0JyjM/AYhenFz31WIRBigwqqCaCDcxyBDV9lraQrLBcnlbfdM90"
    "ag2BXZjDdhFC9SEU8UqbyY0o9yaVJambBjpURZS7vWhGCw6ZZBWHAOSaQsKFgPk2TzI8ChblznV1/o43"
    "DB4/2pug9KON8wlUf1auVLQaK/SwEkehUTvtYjImUfkEXMbJH4hkLNhMHEokfvMtiFckJUuho/0Fb8zV"
    "Ogh2/sv4xJxw5BYp4oeSBSW8y7kxSMjEgJs5AJj7ckwuMmZs9+2v1Q59MXS7h59X9CYEmj8MsYkHCzv8"
    "QQe92LepcIjwXOyjIkprYU/+pZfg3h+cTftC7tChsLC/rBXfP7qlYzn31bIpji0VKbGTWUwHLpTSthp7"
    "A5RfNy9/UKHlikUyxaXX2FyhHJJIXvJI1inXEc1jRLCi2VCW0l7JwoUXV5rWZICkZWkGstJB4g8eVSWO"
    "u0Iew8cFWernCeZrcl6LS6fq0yTxVNdEZUz6TqXE7L+DySJJ+O+cByUBWJdoRZXXvDFx84QDebeyZiT1"
    "uFIiQ2jpt0UGk3ZGQ5YFYL3nimoiRvf0mQHoYms661F3Kru7W/czf49sWoXggM4YD4P02MJp70B9FEfZ"
    "aDuypqXXd0g36fCr0Ds9xFCOKiHjVlWTwkzoToqBIP3mgVrQUqcoqJAkiSLNNoLhdE/ZnnAUa4US52Um"
    "TqDqiRqThkYuzyTR7TMHSw==";

    status = hasp_get_info(scope, format, vendor_code, &info);

    /* check if operation was successful */
    if (status != HASP_STATUS_OK)
    {
        val = -1;
    }

    qDebug()<<"status"<<status;
    /* use the information, free it afterwards */

    hasp_free(info);

    return val;

}
#endif
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
