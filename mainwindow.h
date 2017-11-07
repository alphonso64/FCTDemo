#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "const_define.h"
#include "tcprwworker.h"
#include <vector>
#include <QtNetwork>
#include "cuscamera.h"
#include "algorithm/CNN.h"
#include "CusRect.h"
#include <QButtonGroup>
#include <QLabel>
#include <QPainter>
#include "thsettingdialog.h"
#include <dhcamera.h>
#include "usbkeychecker.h"
#include "rotatesettingdialog.h"
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
    void AddTransClick(bool flag);
    void DelClick();
    void MatchClick();
    void RecogClick();
    void detectClick();
    void ItemActivated( int row,int col);
    void proecssBlock_cam1(int n);
    void proecssBlock_cam2(int n);
    void proecssBlock_pic(int n);
    void capimg();
    void saveimg();
    void camInitRdy(int);
    void camSelect(int);
    void selectImageSrc(int);
    void changeImage(QString);
    void loadPatternFile(int,QString);
    void on_savePicButton_clicked();
    void on_saveFileButton_clicked();
    void on_loadFileButton_clicked();
    void changeMode();
    void dialogdone(int);
    void rotatedialogdone(int);
#ifdef  USBCHECK
    void usbkeyCheck();
#endif
private:
    void initNet();
    void send2Client();
    void tcpstartrw();
    void updateStatusBar(int state);
    void updateStatusBar();
    void addOp(QPainter::CompositionMode mode, const QString &name);
#ifdef  USBCHECK
    bool nativeEvent(const QByteArray & eventType, void * message, long *result);
    void usbDetectInit();
#endif


    Ui::MainWindow *ui;
    int capID;
    bool caliFlag;
    QPixmap caliImage;
    QButtonGroup group;
    CNN *cnn;
    TCPRWWorker * tcpworker;
    QVector<CusReplyData> vect;
    CusCamera *cuscamera;
    DHCamera *dhcamera;
    QImage image;
    QLabel *statusLabel;
    QLabel *statusLabel_;
    QLabel *statusLabel_key;
    QPainter::CompositionMode mode;
    ThSettingDialog dialog;
    RotateSettingDialog rotateDialpg;
    USBKEYChecker usbkeyChecker;
    QTimer *keyTimer;
    QImage picImg;
    bool picFlag;
public:

};

#endif // MAINWINDOW_H
