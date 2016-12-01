#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>
#include <QCameraInfo>
#include "util.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    foreach (const QCameraInfo &cameraInfo, QCameraInfo::availableCameras()) {
        if(cameraInfo.description().compare("H264 USB Camera")==0)
        {
            camera=new QCamera(cameraInfo);
        }
    }

    viewfinder=new CusViewFinder();
    viewfinder->setAspectRatioMode(Qt::IgnoreAspectRatio);
    QCameraViewfinderSettings settings;
    settings.setResolution(640,480);
    camera->setViewfinderSettings(settings);
    ui->viewfinderLayout->addWidget(viewfinder);
    camera->setViewfinder(viewfinder);   
    imageCapture=new QCameraImageCapture(camera);
    camera->start();

    ui->tableWidget->setRowCount(0);    
    ui->tableWidget->setColumnCount(2);  
    ui->tableWidget_2->setRowCount(0);
    ui->tableWidget_2->setColumnCount(2);

    QHeaderView* headerView = ui->tableWidget->verticalHeader();
    headerView->setHidden(true);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    headerView = ui->tableWidget_2->verticalHeader();
    headerView->setHidden(true);
    ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true);

    QStringList header;
    header<<"序号"<<"动作";
    ui->tableWidget->setHorizontalHeaderLabels(header);
	ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    QStringList header_;
    header_<<"序号"<<"结果";
    ui->tableWidget_2->setHorizontalHeaderLabels(header_);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->addButton->setCheckable(true);

    initNet();
    initTemp();

    connect(viewfinder, SIGNAL(ListChanged(QMap<int, CusRect>,QMap<int, QString>)), this, SLOT(CusRectListChanged(QMap<int, CusRect>,QMap<int, QString>)));
    connect(ui->addButton, SIGNAL(toggled(bool)), this, SLOT(AddClick(bool)));
    connect(ui->matchButton, SIGNAL(clicked()), this, SLOT(MatchClick()));
    connect(ui->recButton, SIGNAL(clicked()), this, SLOT(RecogClick()));
    connect(ui->delButton, SIGNAL(clicked()), this, SLOT(DelClick()));
    connect(ui->captureButton, SIGNAL(clicked()), this, SLOT(captureImage()));
    connect(imageCapture, SIGNAL(imageCaptured(int,QImage)), this,SLOT(saveImage(int,QImage)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void  MainWindow::CusRectListChanged(QMap<int, CusRect> map,QMap<int, QString> actionMap)
{
	ui->tableWidget->clearContents();
    QMapIterator<int, CusRect> iter(map);
	ui->tableWidget->setRowCount(map.size());
    int cnt = 0;
	while (iter.hasNext())
	{
		iter.next();
        QTableWidgetItem *item  = new QTableWidgetItem(QString::number(iter.key()));
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(cnt, 0, item);

        QString action = actionMap.value(iter.key());
        if(action.compare(MATCH_PROC)==0)
        {
            QString temp = viewfinder->tempMap.value(iter.key());
            QTableWidgetItem *item  = new QTableWidgetItem(MATCH_PROC_TEXT+"("+temp+")");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(cnt++, 1, item);
        }else if(action.compare(RECOG_PROC)==0)
        {
            item  = new QTableWidgetItem(RECOG_PROC_TEXT);
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(cnt++, 1, item);
        }else{
            cnt++;
        }

	}
}

void MainWindow::AddClick(bool flag)
{
    if(flag)
        viewfinder->enableRect();
    else
        viewfinder->disableRect();
}

void MainWindow::ItemActivated(int row,int col)
{
    qDebug()<<row;
}

void MainWindow::DelClick()
{
    int row = ui->tableWidget->currentRow();
    if(row > -1)
    {
        QTableWidgetItem *item  = new QTableWidgetItem(MATCH_PROC_TEXT);
        int key = ui->tableWidget->item(row,0)->text().toInt();
        viewfinder->removeRectMapContent(key);
    }
}

void MainWindow::MatchClick()
{
    int row = ui->tableWidget->currentRow();
    if(row > -1)
    {
        QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), "D://test//temps", tr("Image Files(*.jpg)"));
        if(path.length() == 0) {
            return;
        }else{
            QFileInfo fileInfo(path);

            if(temps.contains(fileInfo.fileName()))
            {
                QTableWidgetItem *item  = new QTableWidgetItem(MATCH_PROC_TEXT+"("+fileInfo.fileName()+")");
                item->setTextAlignment(Qt::AlignCenter);
                ui->tableWidget->setItem(row, 1, item);

                int key = ui->tableWidget->item(row,0)->text().toInt();
                viewfinder->setActionMapContent(key,MATCH_PROC);
                viewfinder->setTempsMapContent(key,fileInfo.fileName());
            }
        }
    }
}

void MainWindow::RecogClick()
{
    int row = ui->tableWidget->currentRow();
    if(row > -1)
    {
        QTableWidgetItem *item  = new QTableWidgetItem(RECOG_PROC_TEXT);
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 1, item);
        int key = ui->tableWidget->item(row,0)->text().toInt();
        viewfinder->setActionMapContent(key,RECOG_PROC);
    }
}

void MainWindow::captureImage()
{
    imageCapture->capture();
}

void MainWindow::saveImage(int index,QImage image )
{
    ui->tableWidget_2->clearContents();
    ui->tableWidget_2->setRowCount(0);

    QMapIterator<int, CusRect> iter(viewfinder->recMap);
    int cnt = 0;
    while (iter.hasNext())
    {
        iter.next();
        CusRect rect = iter.value();
        QString action = viewfinder->actionMap.value(iter.key());
        if(action.compare(MATCH_PROC) == 0){
            ui->tableWidget_2->setRowCount(ui->tableWidget_2->rowCount()+1);
            QTableWidgetItem *item  = new QTableWidgetItem(QString::number(iter.key()));
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_2->setItem(cnt, 0, item);

            item  = new QTableWidgetItem(action);
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_2->setItem(cnt++, 1, item);

        }else if(action.compare(RECOG_PROC) == 0){
            ui->tableWidget_2->setRowCount(ui->tableWidget_2->rowCount()+1);
            QTableWidgetItem *item  = new QTableWidgetItem(QString::number(iter.key()));
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_2->setItem(cnt, 0, item);

            item  = new QTableWidgetItem(action);
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_2->setItem(cnt++, 1, item);
        }

//        CusRect rect = iter.value();
//        QRect rec = rect.getRect(image.width(), image.height());
//        QImage temp = image.copy(rec);
//        cv::Mat mat = QImage2cvMat(temp);
//        cv::cvtColor(mat, mat, CV_RGBA2GRAY);
//        int predict = cnn->test_frame(mat);
//        qDebug()<<"out:"<<predict;

//            CusRect rect = iter.value();
//            QRect rec = rect.getRect(image.width(), image.height());
//            QImage temp = image.copy(rec);
//            cv::Mat mat = QImage2cvMat(temp);
//            cv::cvtColor(mat, mat, CV_RGBA2BGR);
//            imwrite("C:\\eco2.jpg",mat);
//            double res = mul_tempRoi(mat,temps,1);
//            qDebug()<<"out:"<<res;


    }
//    image.save("D:\\test\\raw.jpg");


}

void MainWindow::initNet()
{
    LayerBuilder builder;
    Layer layer;
    builder.addLayer(layer.buildInputLayer(size::size(Len,Len)));
    builder.addLayer(layer.buildConvLayer(6, size::size(5, 5)));
    builder.addLayer(layer.buildSampLayer( size::size(2, 2)));
    builder.addLayer(layer.buildConvLayer(12, size::size(5, 5)));
    builder.addLayer(layer.buildSampLayer( size::size(2, 2)));
    builder.addLayer(layer.buildOutputLayer(10));
    cnn = new CNN(builder, 10);// biuder batchsize
    cnn->load_weight();
}

void MainWindow::initTemp()
{
    QDir dir("D:\\test\\temps");
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();
        for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);

        vector<Mat> temp = make_temps(fileInfo.filePath().toStdString().c_str());
        temps.insert(fileInfo.fileName(),temp);
    }
    qDebug()<<temps.size();
}


