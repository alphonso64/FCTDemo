#ifndef TCPRWWORKER_H
#define TCPRWWORKER_H

#include <QThread>
#include <QMutex>
#include <QtNetwork>

class TCPRWWorker : public QThread
{
    Q_OBJECT
public:
    TCPRWWorker(QObject *parent = 0)
        : QThread(parent)
    {

    }

    void sendCmd(char * buf, int len);
protected:
    void run();
private slots:
    void processConnection();
    void processText();
public:
    QByteArray   senddata;
    QMutex m_lock;
    QTcpServer * listenSocket;
    QTcpSocket * readWriteSocket;
    volatile int isthreadstopped;
    volatile int doprocessimage;
    volatile int isnewrequest;
    QVector<int>  blockidlist_cam1;
    QVector<int>  blockidlist_cam2;
private:
    void processCmd(QByteArray * array);
signals:
    void processImg_cam1(int id);
    void processImg_cam2(int id);
    void loadPatternFile(int code);
    void selectImageSrc(int code);
    void changeImage(int code);
};

#endif // TCPRWWORKER_H
