#include "cuscamera.h"
#include <QDebug>
#include "const_define.h"

void CusCamera::run()
{
    imageproc = new ImageProc();
    imageproc->m_bIsColorFilter = false;
    imageproc->m_bIsOpen = false;
    imageproc->m_bIsSnap = false;
    imageproc->m_nPayLoadSize = 0;
    imageproc->m_nPixelColorFilter = GX_COLOR_FILTER_NONE;
    imageproc->m_nImageWidth = 0;
    imageproc->m_nImageHeight = 0;
    imageproc->m_pBmpInfo = NULL;
    imageproc->m_hDevice = NULL;
    imageproc->m_pImgBuffer = NULL;
    int ret = imageproc->initCamera();
    emit(camInitRdy(ret));
    if(ret == SUCCESS){
        while(true){
            imageproc->SendCaptureCommand();
            emit(capRdy());
        }
    }
//    timer = new QTimer();
//    connect(timer,SIGNAL(timeout()),this,SLOT(timeOut()),Qt::DirectConnection);
//    timer->start(30);
//    exec();
}

void CusCamera::timeOut()
{
    imageproc->SendCaptureCommand();
    emit(capRdy());
}
