#ifndef USBKEYCHECKER_H
#define USBKEYCHECKER_H


class USBKEYChecker
{
public:
    USBKEYChecker();
    void check();
    bool isValidate();
    bool checkable;
private:
    int try_cnt;
    bool validate;

};

#endif // USBKEYCHECKER_H
