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
    qDebug()<<"sned msg";
    readWriteSocket->write(buf, len);
}

void  TCPRWWorker::processText()
{
    qDebug() << "processText";
    QByteArray bytearray;
    bytearray = readWriteSocket->readAll();
    processCmd(&bytearray);
}

void TCPRWWorker::processCmd(QByteArray * array)
{
    uchar  len;
    int i;
    int blockid;

    qDebug()<<array->data();

    blockidlist.clear();
    if(array->at(0) == 'S' && array->at(1) == '8' && array->at(2) == '4' && array->at(3) == 'C')
    {
        len = array->at(4);
        qDebug() << "len =" << len;

        for(i = 0; i < (int)len; i ++)
        {
            blockid = (int)(array->at(5 + i));
            blockidlist.append(blockid);
            qDebug() << i << blockid;
        }
        doprocessimage = 1;
        emit processImg(blockid);
    }else if(array->at(0) == 'S' && array->at(1) == '8' && array->at(2) == '4' && array->at(3) == 'D')
    {
        int  code= array->at(4) + (array->at(5) << 8) + (array->at(6) << 16) + (array->at(7) << 24) ;
        emit loadPatternFile(code);
    }else if(array->at(0) == 'S' && array->at(1) == '8' && array->at(2) == '4' && array->at(3) == 'E')
    {
        int  code= array->at(4) + (array->at(5) << 8) + (array->at(6) << 16) + (array->at(7) << 24) ;
        emit selectImageSrc(code);
    }else if(array->at(0) == 'S' && array->at(1) == '8' && array->at(2) == '4' && array->at(3) == 'F')
    {
        int  code= array->at(4) + (array->at(5) << 8) + (array->at(6) << 16) + (array->at(7) << 24) ;
        emit changeImage(code);
    }
}
