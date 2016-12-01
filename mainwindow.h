#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include "CusViewFinder.h"
#include "imageproc.h"
#include "CNN.h"
#include "Layer.h"
#include "util_liang.h"
#include <vector>

using namespace cv;
using namespace std;

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
    void ItemActivated( int row,int col);
    void captureImage();
    void saveImage(int,QImage);

private:
    void initNet();
    void initTemp();
    Ui::MainWindow *ui;
    QCamera *camera;
	CusViewFinder *viewfinder;
    QCameraImageCapture *imageCapture;
    CNN *cnn;
    vector<Mat> temps;
};

#endif // MAINWINDOW_H
