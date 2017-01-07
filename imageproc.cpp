#include "imageproc.h"
#include <QDebug>

#define  GX_VERIFY(emStatus) \
                            if (emStatus != GX_STATUS_SUCCESS)\
                            {\
                                return emStatus;\
                            }

#define  VERIFY_STATUS_RET(emStatus) \
                            if (emStatus != GX_STATUS_SUCCESS)\
                            {\
                                return emStatus;\
                            }

ImageProc::ImageProc()
{

}

int ImageProc::initCamera()
{
    GX_STATUS      emStatus    = GX_STATUS_SUCCESS;
    GX_OPEN_PARAM  stOpenParam;
    uint32_t       nDevNum  = 0;
    bool           bRet;

    emStatus = GXInitLib();
    qDebug()<<"init lib";
    GX_VERIFY(emStatus);

    emStatus = GXUpdateDeviceList(&nDevNum, 1000);
    qDebug()<<"GXUpdateDeviceList";
    GX_VERIFY(emStatus);

    qDebug()<<nDevNum;
    if (nDevNum <= 0)
    {  
        return -1;
    }

    if (m_hDevice != NULL)
    {
        emStatus = GXCloseDevice(m_hDevice);
        GX_VERIFY(emStatus);
        m_hDevice = NULL;
    }

    emStatus = OpenDevice();
    qDebug()<<"open";
    GX_VERIFY(emStatus);

    emStatus = InitDevice();
    qDebug()<<"init";
    GX_VERIFY(emStatus);

    emStatus = GetDeviceInitParam();
    qDebug()<<"initpara";
    GX_VERIFY(emStatus);

    qDebug()<<"PrepareForShowImg";
    bRet = PrepareForShowImg();
    if (!bRet)
    {
        return -1;
    }

    m_bIsOpen = true;

    emStatus = GXSendCommand(m_hDevice,GX_COMMAND_ACQUISITION_START);
    GX_VERIFY(emStatus);

        // 更新开采标识
    m_bIsSnap = true;

    emStatus = GXSetEnum(m_hDevice,GX_ENUM_BALANCE_WHITE_AUTO,GX_BALANCE_WHITE_AUTO_CONTINUOUS);


    return 0;

}

int ImageProc::startCapture()
{
    return 0;
}

void ImageProc::closeCamera()
{

}

GX_STATUS ImageProc::OpenDevice()
{
    GX_STATUS      emStatus    = GX_STATUS_SUCCESS;
    GX_OPEN_PARAM  stOpenParam;

    stOpenParam.accessMode = GX_ACCESS_EXCLUSIVE;
    stOpenParam.openMode   = GX_OPEN_INDEX;
    char a = '1';
    stOpenParam.pszContent = &a;

    emStatus = GXOpenDevice(&stOpenParam, &m_hDevice);
    return emStatus;
}

GX_STATUS ImageProc::InitDevice()
{
    GX_STATUS emStatus = GX_STATUS_SUCCESS;

    emStatus = GXSetEnum(m_hDevice,GX_ENUM_ACQUISITION_MODE, GX_ACQ_MODE_CONTINUOUS);
    GX_VERIFY(emStatus);

    emStatus = GXSetEnum(m_hDevice,GX_ENUM_TRIGGER_MODE, GX_TRIGGER_MODE_ON);
    GX_VERIFY(emStatus);

    emStatus = SetPixelFormat8bit();
    GX_VERIFY(emStatus);

    emStatus = GXSetEnum(m_hDevice,GX_ENUM_TRIGGER_SOURCE, GX_TRIGGER_SOURCE_SOFTWARE);

    return emStatus;
}

GX_STATUS ImageProc::GetDeviceInitParam()
{
    GX_STATUS emStatus       = GX_STATUS_ERROR;
    bool      bIsImplemented = false;

    emStatus = GXIsImplemented(m_hDevice, GX_ENUM_PIXEL_COLOR_FILTER, &bIsImplemented);
    VERIFY_STATUS_RET(emStatus);
    m_bIsColorFilter = bIsImplemented;

    if(bIsImplemented)
    {
        emStatus = GXGetEnum(m_hDevice, GX_ENUM_PIXEL_COLOR_FILTER, &m_nPixelColorFilter);
        VERIFY_STATUS_RET(emStatus);
    }

    emStatus = GXGetInt(m_hDevice, GX_INT_WIDTH, &m_nImageWidth);
    VERIFY_STATUS_RET(emStatus);

    emStatus = GXGetInt(m_hDevice, GX_INT_HEIGHT, &m_nImageHeight);
    VERIFY_STATUS_RET(emStatus);

    emStatus = GXGetInt(m_hDevice,GX_INT_PAYLOAD_SIZE,&m_nPayLoadSize);

    return emStatus;
}

bool  ImageProc::PrepareForShowImg()
{
    bool bRet = false;

    m_stFrameData.pImgBuf     = new BYTE[(size_t)m_nPayLoadSize];
    if (m_stFrameData.pImgBuf == NULL)
    {
        bRet = false;
    }

    if (m_bIsColorFilter)
    {
        bRet = PrepareForShowColorImg();
    }

    return bRet;
}

bool  ImageProc::PrepareForShowColorImg()
{
    m_pBmpInfo								= (BITMAPINFO *)m_chBmpBuf;
    m_pBmpInfo->bmiHeader.biSize			= sizeof(BITMAPINFOHEADER);
    m_pBmpInfo->bmiHeader.biWidth			= (LONG)m_nImageWidth;
    m_pBmpInfo->bmiHeader.biHeight			= (LONG)m_nImageHeight;

    m_pBmpInfo->bmiHeader.biPlanes			= 1;
    m_pBmpInfo->bmiHeader.biBitCount		= 24;
    m_pBmpInfo->bmiHeader.biCompression		= BI_RGB;
    m_pBmpInfo->bmiHeader.biSizeImage		= 0;
    m_pBmpInfo->bmiHeader.biXPelsPerMeter	= 0;
    m_pBmpInfo->bmiHeader.biYPelsPerMeter	= 0;
    m_pBmpInfo->bmiHeader.biClrUsed			= 0;
    m_pBmpInfo->bmiHeader.biClrImportant	= 0;

    m_pImgBuffer = new BYTE[(size_t)(m_nImageWidth * m_nImageHeight * 3)];
    if (m_pImgBuffer == NULL)
    {
        return false;
    }

    return true;
}

GX_STATUS ImageProc::SetPixelFormat8bit()
{
    GX_STATUS emStatus    = GX_STATUS_SUCCESS;
    int64_t   nPixelSize  = 0;
    uint32_t  nEnmuEntry  = 0;
    size_t    nBufferSize = 0;
    BOOL      bIs8bit     = TRUE;

    GX_ENUM_DESCRIPTION  *pEnumDescription = NULL;
    GX_ENUM_DESCRIPTION  *pEnumTemp        = NULL;

    emStatus = GXGetEnum(m_hDevice, GX_ENUM_PIXEL_SIZE, &nPixelSize);
    VERIFY_STATUS_RET(emStatus);

    if (nPixelSize == GX_PIXEL_SIZE_BPP8)
    {
        return GX_STATUS_SUCCESS;
    }
    else
    {
        emStatus = GXGetEnumEntryNums(m_hDevice, GX_ENUM_PIXEL_FORMAT, &nEnmuEntry);
        VERIFY_STATUS_RET(emStatus);

        nBufferSize      = nEnmuEntry * sizeof(GX_ENUM_DESCRIPTION);
        pEnumDescription = new GX_ENUM_DESCRIPTION[nEnmuEntry];

        emStatus         = GXGetEnumDescription(m_hDevice, GX_ENUM_PIXEL_FORMAT, pEnumDescription, &nBufferSize);
        if (emStatus != GX_STATUS_SUCCESS)
        {
            if (pEnumDescription != NULL)
            {
                delete []pEnumDescription;
                pEnumDescription = NULL;
            }

            return emStatus;
        }

        for (uint32_t i = 0; i<nEnmuEntry; i++)
        {
            if ((pEnumDescription[i].nValue & GX_PIXEL_8BIT) == GX_PIXEL_8BIT)
            {
                emStatus = GXSetEnum(m_hDevice, GX_ENUM_PIXEL_FORMAT, pEnumDescription[i].nValue);
                break;
            }
        }

        if(pEnumDescription != NULL)
        {
            delete []pEnumDescription;
            pEnumDescription = NULL;
        }
    }

    return emStatus;
}

void ImageProc::SendCaptureCommand()
{
    unsigned m_nEditTimeOut;
    // TODO: Add your control notification handler code here
    m_nEditTimeOut = 500;

    GX_STATUS emStatus  = GX_STATUS_ERROR;

    emStatus = GXFlushQueue(m_hDevice);

    emStatus = GXSendCommand(m_hDevice,GX_COMMAND_TRIGGER_SOFTWARE);

    emStatus = GXGetImage(m_hDevice, &m_stFrameData, m_nEditTimeOut);

    //DxRaw8toRGB24((BYTE*)m_stFrameData.pImgBuf, m_pImgBuffer, (VxUint32)m_nImageWidth, (VxUint32)m_nImageHeight, RAW2RGB_NEIGHBOUR,
    //DX_PIXEL_COLOR_FILTER(m_nPixelColorFilter), TRUE);
    mutex.lock();
    DxRaw8toRGB24((BYTE*)m_stFrameData.pImgBuf, m_pImgBuffer, (VxUint32)m_nImageWidth, (VxUint32)m_nImageHeight, RAW2RGB_NEIGHBOUR,
        BAYERBG, false);
    mutex.unlock();
    //ShowImage(&m_stFrameData);
}

QImage ImageProc::getImg()
{
    mutex.lock();
    QImage img = QImage((const uchar*)m_pImgBuffer,(int)m_nImageWidth,(int)m_nImageHeight,QImage::Format_RGB888);
    mutex.unlock();
    return img;
}
