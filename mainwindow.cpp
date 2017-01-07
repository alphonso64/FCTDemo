#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <algorithm/match_util.h>
#define TEMPSPATH "./temps"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    int ret;
    ui->setupUi(this);
    this->setWindowTitle("FCTDEMO");

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    ui->tableWidget->setRowCount(0);    
    ui->tableWidget->setColumnCount(2);  
    ui->tableWidget_2->setRowCount(0);
    ui->tableWidget_2->setColumnCount(2);

//    ui->label->setScaledContents(true);

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

    //listenSocket = new QTcpServer;
    //listenSocket->listen(QHostAddress::AnyIPv4, 8888);

    initNet();
    initTemp();

    vect.clear();

    tcpworker = new TCPRWWorker();
    tcpworker->isthreadstopped = 0;
    tcpworker->doprocessimage  = 0;
    tcpworker->listenSocket = new QTcpServer;
    tcpworker->listenSocket->listen(QHostAddress::AnyIPv4, 8888);
    tcpworker->start();

    cuscamera = new CusCamera();

    connect(ui->label_2, SIGNAL(ListChanged(QMap<int, CusRect>,QMap<int, QString>)), this, SLOT(CusRectListChanged(QMap<int, CusRect>,QMap<int, QString>)));
    connect(ui->addButton, SIGNAL(toggled(bool)), this, SLOT(AddClick(bool)));
    connect(ui->matchButton, SIGNAL(clicked()), this, SLOT(MatchClick()));
    connect(ui->recButton, SIGNAL(clicked()), this, SLOT(RecogClick()));
    connect(ui->delButton, SIGNAL(clicked()), this, SLOT(DelClick()));
    connect(ui->captureButton,SIGNAL(clicked()), this, SLOT(detectClick()));
    connect(cuscamera, SIGNAL(capRdy()), this, SLOT(capimg()));
    connect(tcpworker, SIGNAL(processImg(int)), this, SLOT(proecssBlock(int)));
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveimg()));
    cuscamera->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveimg()
{
    int row = ui->tableWidget->currentRow();
    if(row > -1)
    {
        int key = ui->tableWidget->item(row,0)->text().toInt();
        CusRect rect = ui->label_2->recMap.value(key);
        QRect rec = rect.getRect(image.width(), image.height());
        QImage temp = image.copy(rec);
        QString path = QFileDialog::getSaveFileName(this, tr("Open Image"), TEMPSPATH, tr("Image Files(*.jpg)"));
        temp.save(path,"jpg",100);
    }else{
        QMessageBox::about(NULL, "error", "no item select");
    }
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
            QString temp = ui->label_2->tempMap.value(iter.key());
            QTableWidgetItem *item  = new QTableWidgetItem(MATCH_PROC_TEXT+"("+temp+")");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(cnt++, 1, item);
        }
        else if(action.compare(RECOG_PROC)==0)
        {
            item  = new QTableWidgetItem(RECOG_PROC_TEXT);
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(cnt++, 1, item);
        }
        else
        {
            cnt++;
        }

	}
}

void MainWindow::AddClick(bool flag)
{
    if(flag){
        ui->label_2->enableRect();
    }else{
        ui->label_2->disableRect();
    }
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
        ui->label_2->removeRectMapContent(key);
    }
}

void MainWindow::MatchClick()
{
    int row = ui->tableWidget->currentRow();
    if(row > -1)
    {
        QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), TEMPSPATH, tr("Image Files(*.jpg)"));
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
                ui->label_2->setActionMapContent(key,MATCH_PROC);
                ui->label_2->setTempsMapContent(key,fileInfo.fileName());
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
        ui->label_2->setActionMapContent(key,RECOG_PROC);
    }
}


void MainWindow::replytoclient()
{
    CusReplyData  temp;
    QByteArray array;
    QVectorIterator<CusReplyData> crditer(vect);
    while(crditer.hasNext())
    {
        temp = crditer.next();
        array.append((char *)(&(temp.replybuffer)), sizeof(temp.replybuffer));
        qDebug() << array.data();
        qDebug() << array.size();
    }
    tcpworker->sendCmd(array.data(), array.size());
}

void MainWindow::detectClick()
{
    ui->tableWidget_2->clearContents();
    ui->tableWidget_2->setRowCount(0);

    QMapIterator<int, CusRect> iter(ui->label_2->recMap);
    QVectorIterator<int> viter(tcpworker->blockidlist);

    int cnt = 0;

    ui->label->recMap = ui->label_2->recMap;
    ui->label->setPixmap(QPixmap::fromImage(image.scaled(ui->label->width(),ui->label->height())));

    while (iter.hasNext())
    {

        iter.next();
        CusRect rect = iter.value();
        QRect rec = rect.getRect(image.width(), image.height());
        QImage temp = image.copy(rec);

        QString action = ui->label_2->actionMap.value(iter.key());
        if(action.compare(MATCH_PROC) == 0)
        {
            ui->tableWidget_2->setRowCount(ui->tableWidget_2->rowCount()+1);
            QTableWidgetItem *item  = new QTableWidgetItem(QString::number(iter.key()));
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_2->setItem(cnt, 0, item);
            Pic<uchar> pimg;
            pimg.createToGray(temp,3);
            qDebug()<<temp.width()<<" "<<temp.height();
            double res = mul_tempRoi(pimg,temps.value(ui->label_2->tempMap.value(iter.key())),1);

            qDebug()<<"res"<<res;
            if(res > 0.5f)
            {
                item  = new QTableWidgetItem(QString("off"));
            }
            else if(res>-0.1f)
            {
                item  = new QTableWidgetItem("on");
            }
            else
            {
                item  = new QTableWidgetItem("error");
            }
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_2->setItem(cnt++, 1, item);

        }else if(action.compare(RECOG_PROC) == 0)
        {
            ui->tableWidget_2->setRowCount(ui->tableWidget_2->rowCount()+1);
            QTableWidgetItem *item  = new QTableWidgetItem(QString::number(iter.key()));
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_2->setItem(cnt, 0, item);

//            cv::cvtColor(mat, mat, CV_RGBA2GRAY);
//            int predict = cnn->test_frame(mat);

            Pic<uchar> pimg;
            pimg.createToGray(temp,3);
            int predict = cnn->test_Pic(pimg);
            if(predict >= 0){
                item  = new QTableWidgetItem(QString::number(predict));
            }else{
                item  = new QTableWidgetItem("error");
            }

            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget_2->setItem(cnt++, 1, item);
        }
    }
}

void MainWindow::proecssBlock(int n )
{
    QByteArray array;
    QVectorIterator<int> viter(tcpworker->blockidlist);

    uchar totalblock = 0;
    int blockid;
    CusReplyData  custdata;
    UINT32 totallen = 0;
    char number[64] = "";
    char filename[64];//  = "D:\\test\\temps\\temp";
    vect.clear();

    array.append((char *)&totallen, sizeof(totallen));
    array.append('\0');

    while(viter.hasNext())
    {
        blockid = viter.next();

        if(ui->label_2->recMap.contains(blockid))
        {
            CusRect rect = ui->label_2->recMap.value(blockid);
            QRect rec = rect.getRect(image.width(), image.height());
            QImage temp = image.copy(rec);

            QString action = ui->label_2->actionMap.value(blockid);

            //save imageblock
            strcpy_s(filename, "D:\\test\\data");
            //strcat(strcat(filename, itoa(blockid, number, 10)), ".jpg");
            //qDebug() << filename;
            //imwrite(filename, mat);

            if(action.compare(MATCH_PROC) == 0)
            {
                Pic<uchar> pimg;
                pimg.createToGray(temp,3);
                qDebug()<<temp.width()<<" "<<temp.height();

                double res = mul_tempRoi(pimg,temps.value(ui->label_2->tempMap.value(blockid)),1);
                if(res > 0.5f)
                {
                    custdata.replybuffer.state = 0;
                }
                else if(res > -0.1f)
                {
                    custdata.replybuffer.state = 1;
                }
                else
                {
                    custdata.replybuffer.state = 0xff;
                }
                custdata.replybuffer.similarity = static_cast<int>(res * 100.0f + .5f);
                qDebug() << res << res * 100.0f << custdata.replybuffer.similarity;

            }
            else if(action.compare(RECOG_PROC) == 0)
            {
                Pic<uchar> pimg;
                pimg.createToGray(temp,3);
                int predict = cnn->test_Pic(pimg);
                custdata.replybuffer.number = predict;
            }
            custdata.replybuffer.id = blockid;
            custdata.replybuffer.width = temp.width();
            custdata.replybuffer.height = temp.height();

            array.append((char *)(&(custdata.replybuffer)), sizeof(custdata.replybuffer));
            array.append((char *)(temp.bits()), temp.width() * temp.height() * 3);

            //vect.append(custdata);
            totalblock ++;
            qDebug() << "totalblock:" << totalblock;
            //FILE * fp;
            //strcat(strcat(filename, itoa(blockid, number, 10)), ".data");
            //fp = fopen(filename, "wb");
            //fwrite(temp.bits(), 1, temp.width() * temp.height() * 3, fp);
            //fclose(fp);
        }
    }

    *(array.data() + 4) = totalblock & 0xff;
    totallen = array.size();

    *(UINT32 *)(array.data()) = totallen;

    qDebug() << "array:" << (int)array.at(0) << (int)array.at(1) << (int)array.at(2) << (int)array.at(3) << (int)array.at(4);

    tcpworker->doprocessimage = 0;
    tcpworker->sendCmd(array.data(), array.size());
    qDebug() << "array:" << array.size();
    //replytoclient();

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
    QDir dir(TEMPSPATH);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        QImage tempImg(fileInfo.filePath());
        Pic<uchar> pimg;
        pimg.createToGray(tempImg,4);
        temps.insert(fileInfo.fileName(),make_temps(pimg));
    }
    qDebug()<<temps.size();
}

void MainWindow::send2Client()
{

}

void MainWindow::tcpstartrw()
{
    tcpworker->exit();
}

void MainWindow::capimg()
{
    image = cuscamera->imageproc->getImg();
    ui->label_2->setPixmap(QPixmap::fromImage(image.scaled(ui->label_2->width(),ui->label_2->height())));
//    ui->label->update();
}
