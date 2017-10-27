#ifndef CUSCAMERA_H
#define CUSCAMERA_H
#include <QThread>
#include <QTimer>
#include "dhcamera.h"
class CusCamera: public QThread
{
    Q_OBJECT
public:
    CusCamera(QObject *parent = 0)
        : QThread(parent)
    {

    }

protected:
    void run();
private slots:
signals:
    void camInitRdy(int);
public:
    DHCamera *dhcamera;
    bool flag;
private:

};

#endif // CUSCAMERA_H
