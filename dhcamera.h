#ifndef DHCAMERA_H
#define DHCAMERA_H

#include <QObject>
#include "DxImageProc.h"
#include "GxIAPI.h"
#include <QMutex>
#include <QImage>
class CamData
{
public:
    GX_DEV_HANDLE m_device;
    int64_t width,height;
    int camID;
    BYTE *m_pImgBuffer;
};

class DHCamera : public QObject
{
    Q_OBJECT
public:
    explicit DHCamera(QObject *parent = 0);
    int init();
    int deinit();
    int openDevice();
    QImage getImage();
    QImage getImage(int camID);
    static void CAM1_OnFrameCallbackFun(GX_FRAME_CALLBACK_PARAM* pFrame);
    static void CAM2_OnFrameCallbackFun(GX_FRAME_CALLBACK_PARAM* pFrame);
    uint cam_num;
    QMutex mutex;
    int currentID;
    CamData **camdata;
signals:
    void capRdy();
public slots:
};

#endif // DHCAMERA_H
