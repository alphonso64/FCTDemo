#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imageproc.h"
#include "tcprwworker.h"
#include <vector>
#include <QtNetwork>
#include "cuscamera.h"
#include "algorithm/CNN.h"
#include "vector"
#include "CusRect.h"
using namespace std;

#pragma execution_character_set("utf-8")

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void CusRectListChanged(QMap<int, CusRect> map,QMap<int, QString> actionMap);
    void AddClick(bool flag);
    void DelClick();
    void MatchClick();
    void RecogClick();
    void detectClick();
    void ItemActivated( int row,int col);
    void proecssBlock(int n);
    void capimg();
    void saveimg();
    //void processConnection();
    //void processText();

private:
    void initNet();
    void initTemp();
    void send2Client();
    void tcpstartrw();
    void replytoclient();
    Ui::MainWindow *ui;

    CNN *cnn;
    QMap<QString,vector<Pic<uchar>>> temps;
    TCPRWWorker * tcpworker;
    QVector<CusReplyData> vect;
    CusCamera *cuscamera;
    QImage image;
    QImage detetcImage;
    //QTcpServer * listenSocket;
    //QTcpSocket * readWriteSocket;
//    vector<Mat> temps;
public:

};

#endif // MAINWINDOW_H
