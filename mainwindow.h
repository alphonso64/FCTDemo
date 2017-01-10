#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imageproc.h"
#include "const_define.h"
#include "tcprwworker.h"
#include <vector>
#include <QtNetwork>
#include "cuscamera.h"
#include "algorithm/CNN.h"
#include "CusRect.h"
#include <QButtonGroup>
#include <QLabel>
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
    void camInitRdy(int);
    void camSelect(int);
    void on_savePicButton_clicked();

    void on_saveFileButton_clicked();

    void on_loadFileButton_clicked();

private:
    void initNet();
    void send2Client();
    void tcpstartrw();
    void replytoclient();
    void updateStatusBar(int state);
    void updateStatusBar();

    Ui::MainWindow *ui;
    int capID;
    QButtonGroup group;
    CNN *cnn;
    TCPRWWorker * tcpworker;
    QVector<CusReplyData> vect;
    CusCamera *cuscamera;
    QImage image;
    QImage detetcImage;
    QLabel *statusLabel;
    QLabel *statusLabel_;
public:

};

#endif // MAINWINDOW_H
