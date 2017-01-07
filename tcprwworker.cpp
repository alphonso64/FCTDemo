#include "tcprwworker.h"
#include <QDebug>

void TCPRWWorker::run()
{

    //listenSocket->listen(QHostAddress::AnyIPv4, 8888);

    connect(listenSocket, SIGNAL(newConnection()), this, SLOT(processConnection()));

    qDebug() << "waiting...";
    this->exec();
    //qDebug() << "start...";
    //this->exec();

//    QString theqstring;

//    while(!isthreadstopped)
//    {
//        theqstring.clear();
//        theqstring = readWriteSocket->readAll();
//        if(theqstring.size() != 0)
//        {
//            qDebug() << theqstring;
//            readWriteSocket->write("ok");
//        }
//        //msleep(50);
//    }
}

void  TCPRWWorker::processConnection()
{
    readWriteSocket = listenSocket->nextPendingConnection();
    connect(readWriteSocket, SIGNAL(readyRead()), this, SLOT(processText()));
    qDebug() << readWriteSocket->peerAddress();
    qDebug() << "start...";
    //exit();
}

void  TCPRWWorker::sendCmd(char * buf, int len)
{
    readWriteSocket->write(buf, len);
}

void  TCPRWWorker::processText()
{
    QByteArray bytearray;
    bytearray = readWriteSocket->readAll();
    processCmd(&bytearray);
    //readWriteSocket->write("ok");
}

void TCPRWWorker::processCmd(QByteArray * array)
{
    QByteArray header = "S84C";
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
    }
}
