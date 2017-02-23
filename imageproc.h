#ifndef IMAGEPROC_H
#define IMAGEPROC_H
#include <QString>
#include "DxImageProc.h"
#include "GxIAPI.h"
#include <QMutex>
#include <QImage>

#define MATCH_PROC QString("match")
#define RECOG_PROC QString("recog")
#define MATCH_PROC_TEXT QString("匹配")
#define RECOG_PROC_TEXT QString("识别")
class ImageProc
{
public:
    ImageProc();
    ~ImageProc();
    int initCamera();
    int startCapture();
    void closeCamera();

public:
    GX_DEV_HANDLE  m_hDevice;
    bool           m_bIsOpen;
    bool           m_bIsSnap;
    BITMAPINFO    *m_pBmpInfo;
    char           m_chBmpBuf[2048];
    int64_t        m_nImageWidth;
    int64_t        m_nImageHeight;
    int64_t        m_nPixelColorFilter;
    int64_t        m_nPayLoadSize;
    bool           m_bIsColorFilter;
    BYTE          *m_pImgBuffer;
    GX_FRAME_DATA  m_stFrameData;
//private:
    GX_STATUS      OpenDevice();
    GX_STATUS      CloseDevice();
    GX_STATUS      InitDevice();
    GX_STATUS      GetDeviceInitParam();
    bool           PrepareForShowImg();
    bool           PrepareForShowColorImg();
    GX_STATUS      SetPixelFormat8bit();
    void           SendCaptureCommand();

    QMutex mutex;
    QImage getImg();
};

#endif // IMAGEPROC_H
