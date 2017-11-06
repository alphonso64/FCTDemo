#include "usbkeychecker.h"
#include "util.h"
#include "const_define.h"
#include <windows.h>

USBKEYChecker::USBKEYChecker()
{
    validate = false;
    try_cnt = 0;
    checkable = true;
}

bool USBKEYChecker::isValidate()
{
    return validate;
}

#ifdef USBCHECK
void USBKEYChecker::check()
{
    if(checkable != false)
    {
        if(TUtil::checkUSBKEY() != 0)
        {
            if(try_cnt == USB_CHECK_MAX_CNT)
            {
                validate = false;
                checkable = false;
            }else
            {
                try_cnt++;
            }
        }else
        {
            validate = true;
            checkable = false;
            try_cnt = 0;
        }
    }

}
#endif




