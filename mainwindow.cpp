#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    camera=new QCamera(this);
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

    QHeaderView* headerView = ui->tableWidget->verticalHeader();
    headerView->setHidden(true);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    QStringList header;
    header<<"序号"<<"动作";
    ui->tableWidget->setHorizontalHeaderLabels(header);
	ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->addButton->setCheckable(true);

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
            item  = new QTableWidgetItem(MATCH_PROC_TEXT);
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
        QTableWidgetItem *item  = new QTableWidgetItem(MATCH_PROC_TEXT);
        item->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(row, 1, item);

        int key = ui->tableWidget->item(row,0)->text().toInt();
        viewfinder->setActionMapContent(key,MATCH_PROC);
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
    QMapIterator<int, CusRect> iter(viewfinder->recMap);
    while (iter.hasNext())
    {
        iter.next();
        CusRect rect = iter.value();
        QString action = viewfinder->actionMap.value(iter.key());
//        qDebug()<<iter.key()<<action;
        if(action.compare(MATCH_PROC) == 0){
            QRect rec = rect.getRect(image.width(), image.height());
            QImage temp = image.copy(rec);
            QString pre = QString::number(iter.key());
            temp.save("D:\\test\\"+pre+" "+MATCH_PROC_TEXT+".jpg");
        }else if(action.compare(RECOG_PROC) == 0){
            QRect rec = rect.getRect(image.width(), image.height());
            QImage temp = image.copy(rec);
            QString pre = QString::number(iter.key());
            temp.save("D:\\test\\"+pre+" "+RECOG_PROC_TEXT+".jpg");
        }

    }
//    image.save("D:\\test\\raw.jpg");
}


