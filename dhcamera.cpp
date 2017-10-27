#include "dhcamera.h"
#include <QDebug>
#include "const_define.h"



DHCamera::DHCamera(QObject *parent) : QObject(parent)
{

}

 void  DHCamera::CAM1_OnFrameCallbackFun(GX_FRAME_CALLBACK_PARAM* pFrame)
{
    if (pFrame->status == 0)
    {
        DHCamera *dhcam = (DHCamera *)pFrame->pUserParam;
        dhcam->mutex.lock();
        DxRaw8toRGB24((void *)pFrame->pImgBuf, dhcam->camdata[0]->m_pImgBuffer, dhcam->camdata[0]->width,
             dhcam->camdata[0]->height, RAW2RGB_NEIGHBOUR, BAYERBG, false);
        dhcam->mutex.unlock();
        //qDebug()<<"cam1"<<pFrame->nFrameID;
        if(dhcam->currentID == 0)
        {
            emit(dhcam->capRdy());
        }
    }
    return;
}

void  DHCamera::CAM2_OnFrameCallbackFun(GX_FRAME_CALLBACK_PARAM* pFrame)
{
    if (pFrame->status == 0)
    {
        DHCamera *dhcam = (DHCamera *)pFrame->pUserParam;
        DxRaw8toRGB24((void *)pFrame->pImgBuf, dhcam->camdata[1]->m_pImgBuffer, dhcam->camdata[1]->width,
           dhcam->camdata[1]->height, RAW2RGB_NEIGHBOUR, BAYERBG, false);
        //qDebug()<<"cam2"<<pFrame->nFrameID;
        if(dhcam->currentID == 1)
        {
            emit(dhcam->capRdy());
        }
    }
    return;
}

static int SetPixelFormat8bit()
{
//    GX_STATUS emStatus    = GX_STATUS_SUCCESS;
//    int64_t   nPixelSize  = 0;
//    uint32_t  nEnmuEntry  = 0;
//    size_t    nBufferSize = 0;

//    GX_ENUM_DESCRIPTION  *pEnumDescription = NULL;

//    emStatus = GXGetEnum(m_hDevice, GX_ENUM_PIXEL_SIZE, &nPixelSize);
//    VERIFY_STATUS_RET(emStatus);

//    if (nPixelSize == GX_PIXEL_SIZE_BPP8)
//    {
//        qDebug()<<"GX_PIXEL_SIZE_BPP8";
//        return GX_STATUS_SUCCESS;
//    }
//    else
//    {
//        emStatus = GXGetEnumEntryNums(m_hDevice, GX_ENUM_PIXEL_FORMAT, &nEnmuEntry);
//        VERIFY_STATUS_RET(emStatus);

//        nBufferSize      = nEnmuEntry * sizeof(GX_ENUM_DESCRIPTION);
//        pEnumDescription = new GX_ENUM_DESCRIPTION[nEnmuEntry];

//        emStatus         = GXGetEnumDescription(m_hDevice, GX_ENUM_PIXEL_FORMAT, pEnumDescription, &nBufferSize);
//        if (emStatus != GX_STATUS_SUCCESS)
//        {
//            if (pEnumDescription != NULL)
//            {
//                delete []pEnumDescription;
//                pEnumDescription = NULL;
//            }

//            return emStatus;
//        }

//        for (uint32_t i = 0; i<nEnmuEntry; i++)
//        {
//            if ((pEnumDescription[i].nValue & GX_PIXEL_8BIT) == GX_PIXEL_8BIT)
//            {
//                emStatus = GXSetEnum(m_hDevice, GX_ENUM_PIXEL_FORMAT, pEnumDescription[i].nValue);
//                break;
//            }
//        }

//        if(pEnumDescription != NULL)
//        {
//            delete []pEnumDescription;
//            pEnumDescription = NULL;
//        }
//    }

    return 0;
}

int DHCamera::init()
{
    GX_STATUS status = GX_STATUS_SUCCESS;
    status = GXInitLib();
    //qDebug()<<"dhcamera init\n";
    if(status != GX_STATUS_SUCCESS)
    {
        return FAIL;
    }

    currentID = 0;

    return SUCCESS;
}

int DHCamera::deinit()
{
    GX_STATUS status = GX_STATUS_SUCCESS;

    //printf("deinit\n");

    for(int i=0;i<cam_num;i++)
    {
        //发送停采命令
        status = GXSendCommand(camdata[i]->m_device, GX_COMMAND_ACQUISITION_STOP);
        if(status != GX_STATUS_SUCCESS)
        {
            return FAIL;
        }

        status = GXCloseDevice(camdata[i]->m_device);
        if(status != GX_STATUS_SUCCESS)
        {
            return FAIL;
        }

        delete [] camdata[i]->m_pImgBuffer;

    }

    status = GXCloseLib();
    if(status != GX_STATUS_SUCCESS)
    {
        return FAIL;
    }

    return SUCCESS;
}

QImage DHCamera::getImage()
{
    mutex.lock();
    QImage img = QImage((const uchar*)camdata[currentID]->m_pImgBuffer,
                         (int) camdata[currentID]->width,(int)camdata[currentID]->height,QImage::Format_RGB888);
    mutex.unlock();
    return img;
}

QImage DHCamera::getImage(int cam)
{
    mutex.lock();
    QImage img = QImage((const uchar*)camdata[cam]->m_pImgBuffer,
                         (int) camdata[cam]->width,(int)camdata[cam]->height,QImage::Format_RGB888);
    mutex.unlock();
    return img;
}

int DHCamera::openDevice()
{
    GX_STATUS emStatus = GXUpdateDeviceList(&cam_num, 1000);

    //qDebug()<<"cam num"<<cam_num;
    if (cam_num <= 0)
    {
        return FAIL;
    }
    camdata = (CamData **) malloc(sizeof(CamData*)*cam_num);

    for(int i=0;i<cam_num;i++)
    {
        camdata[i] = new CamData;
    }

    for(int i=0;i<cam_num;i++)
    {
        char      index[10]    = {0};
        GX_OPEN_PARAM open_param;
        open_param.accessMode = GX_ACCESS_EXCLUSIVE;
        open_param.openMode   = GX_OPEN_INDEX;

        sprintf(index, "%d", (i+1));
        open_param.pszContent = index;

        emStatus = GXOpenDevice(&open_param, &camdata[i]->m_device);
        if(emStatus != GX_STATUS_SUCCESS)
        {
            return FAIL;
        }

        emStatus = GXSetEnum(camdata[i]->m_device,GX_ENUM_ACQUISITION_MODE, GX_ACQ_MODE_CONTINUOUS);
        if(emStatus != GX_STATUS_SUCCESS)
        {
            return FAIL;
        }
        //emStatus = SetPixelFormat8bit();

        //注册图像处理回调函数
        if(i==0)
        {
            emStatus = GXRegisterCaptureCallback(camdata[i]->m_device,
                                                 this, (GXCaptureCallBack)CAM1_OnFrameCallbackFun);
            if(emStatus != GX_STATUS_SUCCESS)
            {
                return FAIL;
            }
        }else if(i==1){
            emStatus = GXRegisterCaptureCallback(camdata[i]->m_device,
                                                 this, (GXCaptureCallBack)CAM2_OnFrameCallbackFun);
            if(emStatus != GX_STATUS_SUCCESS)
            {
                return FAIL;
            }
        }

        emStatus = GXGetInt(camdata[i]->m_device, GX_INT_WIDTH, &camdata[i]->width);
        if(emStatus != GX_STATUS_SUCCESS)
        {
            return FAIL;
        }

        emStatus = GXGetInt(camdata[i]->m_device, GX_INT_HEIGHT, &camdata[i]->height);
        if(emStatus != GX_STATUS_SUCCESS)
        {
            return FAIL;
        }

        emStatus = GXSendCommand(camdata[i]->m_device,GX_COMMAND_ACQUISITION_START);
        if(emStatus != GX_STATUS_SUCCESS)
        {
            return FAIL;
        }

        emStatus = GXSetEnum(camdata[i]->m_device,GX_ENUM_BALANCE_WHITE_AUTO,GX_BALANCE_WHITE_AUTO_CONTINUOUS);
        if(emStatus != GX_STATUS_SUCCESS)
        {
            return FAIL;
        }
        camdata[i]->m_pImgBuffer = new BYTE[(size_t)(camdata[i]->height * camdata[i]->width * 3)];

    }

    return SUCCESS;
}
