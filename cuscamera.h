#ifndef CUSCAMERA_H
#define CUSCAMERA_H
#include "imageproc.h"
#include <QThread>
#include <QTimer>
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
    void timeOut();
signals:
    void capRdy();
public:
    ImageProc *imageproc;
private:
    QTimer *timer;

};

#endif // CUSCAMERA_H
