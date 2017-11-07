#include "tcprwworker.h"
#include <QDebug>

void TCPRWWorker::run()
{
    qDebug() << "waiting...";
    connect(listenSocket, SIGNAL(newConnection()), this, SLOT(processConnection()));
    this->exec();
}

void  TCPRWWorker::processConnection()
{
    readWriteSocket = listenSocket->nextPendingConnection();
    connect(readWriteSocket, SIGNAL(readyRead()), this, SLOT(processText()));
    qDebug() << readWriteSocket->peerAddress();
    qDebug() << "new  Connection...";
}

void  TCPRWWorker::sendCmd(char * buf, int len)
{

    readWriteSocket->write(buf, len);
}

void  TCPRWWorker::processText()
{
    //qDebug() << "processText";
    QByteArray bytearray;
    bytearray = readWriteSocket->readAll();
    processCmd(&bytearray);
}

void TCPRWWorker::processCmd(QByteArray * array)
{
    uchar  len;
    int i;
    int blockid;

    //qDebug()<<array->data();


    if(array->at(0) == 'S' && array->at(1) == '8' && array->at(2) == '4' && array->at(3) == 'C')
    {
        blockidlist_cam1.clear();
        len = array->at(4);
        //qDebug() << "ca1 len =" << len;

        for(i = 0; i < (int)len; i ++)
        {
            blockid = (int)(array->at(5 + i));
            blockidlist_cam1.append(blockid);
            //qDebug() << i << blockid;
        }
        doprocessimage = 1;
        emit processImg_cam1(blockid);
    }else if(array->at(0) == 'S' && array->at(1) == '8' && array->at(2) == '4' && array->at(3) == 'B')
    {
        blockidlist_cam2.clear();
        len = array->at(4);
        //qDebug() << "ca2 len =" << len;

        for(i = 0; i < (int)len; i ++)
        {
            blockid = (int)(array->at(5 + i));
            blockidlist_cam2.append(blockid);
            //qDebug() << i << blockid;
        }
        doprocessimage = 1;
        emit processImg_cam2(blockid);
    }else if(array->at(0) == 'S' && array->at(1) == '8' && array->at(2) == '4' && array->at(3) == 'A')
    {
        blockidlist_pic.clear();
        len = array->at(4);
        //qDebug() << "ca2 len =" << len;

        for(i = 0; i < (int)len; i ++)
        {
            blockid = (int)(array->at(5 + i));
            blockidlist_pic.append(blockid);
            //qDebug() << i << blockid;
        }
        doprocessimage = 1;
        qDebug()<<"pic cam";
        emit processImg_pic(blockid);
    }
    else if(array->at(0) == 'S' && array->at(1) == '8' && array->at(2) == '4' && array->at(3) == 'D')
    {
        int  code= array->at(4) + (array->at(5) << 8) + (array->at(6) << 16) + (array->at(7) << 24) ;
        int  len = array->at(8) + (array->at(9) << 8) + (array->at(10) << 16) + (array->at(11) << 24) ;
        QString path = array->mid(12,len);
        emit loadPatternFile(code,path);
    }else if(array->at(0) == 'S' && array->at(1) == '8' && array->at(2) == '4' && array->at(3) == 'E')
    {
        int  code= array->at(4) + (array->at(5) << 8) + (array->at(6) << 16) + (array->at(7) << 24) ;
        emit selectImageSrc(code);
    }else if(array->at(0) == 'S' && array->at(1) == '8' && array->at(2) == '4' && array->at(3) == 'F')
    {
        int  code= array->at(4) + (array->at(5) << 8) + (array->at(6) << 16) + (array->at(7) << 24) ;
        QString path = array->mid(8,code);
        qDebug()<<path;
        emit changeImage(path);
    }
}
