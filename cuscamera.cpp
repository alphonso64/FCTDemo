#include "cuscamera.h"
#include <QDebug>
#include "const_define.h"

void CusCamera::run()
{
    flag = false;

    int ret = dhcamera->init();
    if(ret != SUCCESS)
    {
        camInitRdy(ret);
        return;
    }
    ret = dhcamera->openDevice();
    if(ret != SUCCESS)
    {
        camInitRdy(ret);
        return;
    }
    flag = true;
    emit(camInitRdy(ret));
}



