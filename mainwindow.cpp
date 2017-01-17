#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <algorithm/match_util.h>
#include "util.h"
#include "patternfile.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("FCTDEMO");

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    ui->tableWidget->setRowCount(0);    
    ui->tableWidget->setColumnCount(3);


    QHeaderView* headerView = ui->tableWidget->verticalHeader();
    headerView->setHidden(true);
    QStringList header;
    header<<"序号"<<"动作"<<"结果";
    ui->tableWidget->setHorizontalHeaderLabels(header);
	ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
//    ui->tableWidget->resizeColumnsToContents();
    ui->tableWidget->setEditTriggers (QAbstractItemView::NoEditTriggers);

    ui->camButton->setCheckable(true);
    ui->picButton->setCheckable(true);
    ui->camButton->setChecked(true);
    group.addButton(ui->camButton,CAM_CAP);
    group.addButton(ui->picButton,PIC_CAP);
    capID = CAM_CAP;

    ui->addButton->setCheckable(true);
    initNet();
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
    connect(cuscamera, SIGNAL(camInitRdy(int)), this, SLOT(camInitRdy(int)));
    connect(tcpworker, SIGNAL(processImg(int)), this, SLOT(proecssBlock(int)));
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveimg()));
    connect(&group,SIGNAL(buttonClicked(int)),this,SLOT(camSelect(int)));
    cuscamera->start();
    statusBar()->addWidget( statusLabel = new QLabel("正在打开摄像机 "));
    statusBar()->addWidget( statusLabel_ = new QLabel("流程文件：未选择"));
    statusBar()->setContentsMargins(6,0,0,0);
    statusLabel_->setContentsMargins(6,0,0,0);
    ui->camButton->setEnabled(false);
    ui->picButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateStatusBar(int res)
{
    QString val ;
    if(capID == CAM_CAP){
        if(res == FAIL){
            val.append("打开摄像机失败 ");
        }else{
            val.append("图像来源：摄像机 分辨率："+QString::number(cuscamera->imageproc->m_nImageWidth)+"x"+QString::number(cuscamera->imageproc->m_nImageHeight));
        }
    }else{
        if(res == FAIL){
            val.append("未选择本地图片 ");
        }else{
            val.append("图像来源：本地图片 分辨率："+QString::number(image.width())+"x"+QString::number(image.height()));
        }
    }
    statusLabel->setText(val);
}

void MainWindow::updateStatusBar()
{
    QString val  ;
    QString  path = ui->label_2->getRegular()->pattenPath;
    if(path.length() == 0){
        val.append("流程文件：未选择");
    }else{
        val.append("流程文件:"+path);
    }
    statusLabel_->setText(val);
}

void MainWindow::camSelect(int id)
{
    if(id == CAM_CAP){
        capID = CAM_CAP;
        if(cuscamera->isFinished()){
            statusLabel->setText("正在打开摄像机");
            ui->camButton->setEnabled(false);
            ui->picButton->setEnabled(false);
            cuscamera->start();
        }else{
            updateStatusBar(SUCCESS);
        }
    }else if(id == PIC_CAP){
        capID = PIC_CAP;
        QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), TEMPSPATH, tr("Image Files(*.bmp)"));
        if(path.length() == 0) {
            updateStatusBar(FAIL);
            ui->label_2->setPixmap(QPixmap(ui->label_2->width(),ui->label_2->height()));
        }else{
            image = QImage(path);
            ui->label_2->setPixmap(QPixmap::fromImage(image.scaled(ui->label_2->width(),ui->label_2->height())));
            updateStatusBar(SUCCESS);
        }
    }
}

void MainWindow::camInitRdy(int val)
{
    updateStatusBar(val);
    ui->camButton->setEnabled(true);
    ui->picButton->setEnabled(true);
}

void MainWindow::saveimg()
{
    int row = ui->tableWidget->currentRow();
    if(row > -1)
    {
        int key = ui->tableWidget->item(row,0)->text().toInt();
        CusRect rect = ui->label_2->getRegular()->recMap.value(key);
        QRect rec = rect.getRect(image.width(), image.height());
        QImage temp = image.copy(rec);
        QString path = QFileDialog::getSaveFileName(this, tr("保存模板文件"), TEMPSPATH, tr("Image Files(*.bmp)"));
        QPixmap pixmap = QPixmap::fromImage(temp);
        pixmap.save(path,"bmp",100);
    }else{
        QMessageBox::about(NULL, "error", "未选择要保存的区域");
    }
}

void  MainWindow::CusRectListChanged(QMap<int, CusRect> map,QMap<int, QString> actionMap)
{
    qDebug()<<"CusRectListChanged";
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
            QString temp = ui->label_2->getRegular()->tempsMap.value(iter.key()).name;
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
        ui->label_2->getRegular()->removeRectMapContent(key);
        CusRectListChanged(ui->label_2->getRegular()->recMap,ui->label_2->getRegular()->actionMap);
    }
}

void MainWindow::MatchClick()
{
    int row = ui->tableWidget->currentRow();
    if(row > -1)
    {
        QString path = QFileDialog::getOpenFileName(this, tr("选择模板文件"), TEMPSPATH, tr("Image Files(*.bmp)"));
        if(path.length() == 0) {
            return;
        }else{
            QFileInfo fileInfo(path);


            QTableWidgetItem *item  = new QTableWidgetItem(MATCH_PROC_TEXT+"("+fileInfo.fileName()+")");
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(row, 1, item);

            PatternFile pattern;
            pattern.name = fileInfo.fileName();
            pattern.path = fileInfo.path();
            QImage tempImg(fileInfo.filePath());
            Pic<uchar> pimg;
            pimg.createToGray(tempImg,4);
            pattern.temps = make_temps(pimg);

            int key = ui->tableWidget->item(row,0)->text().toInt();
            ui->label_2->getRegular()->setActionMapContent(key,MATCH_PROC);
            ui->label_2->getRegular()->setTempsMapContent(key,pattern);

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
        ui->label_2->getRegular()->setActionMapContent(key,RECOG_PROC);
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
    QMapIterator<int, CusRect> iter(ui->label_2->getRegular()->recMap);
    int cnt = 0;

    ui->label->recMap = ui->label_2->getRegular()->recMap;
    ui->label->setPixmap(QPixmap::fromImage(image.scaled(ui->label->width(),ui->label->height())));

    while (iter.hasNext())
    {

        iter.next();
        CusRect rect = iter.value();
        QRect rec = rect.getRect(image.width(), image.height());
        QImage temp = image.copy(rec);
        temp.save("D:/test1/"+QString::number(iter.key())+".jpg","jpg",100);
        QString action = ui->label_2->getRegular()->actionMap.value(iter.key());
        if(action.compare(MATCH_PROC) == 0)
        {
            QTableWidgetItem *item  = new QTableWidgetItem(QString::number(iter.key()));
            item->setTextAlignment(Qt::AlignCenter);
            Pic<uchar> pimg;
            if(capID == CAM_CAP){
                pimg.createToGray(temp,3);
            }else if(capID == PIC_CAP){
                pimg.createToGray(temp,4);
            }
            double res = mul_tempRoi(pimg,ui->label_2->getRegular()->tempsMap.value(iter.key()).temps,1);
            if(res <-0.1f)
            {
                item  = new QTableWidgetItem("error");
            }else{
                int val = (1-res)*100;
                item  = new QTableWidgetItem(QString::number(val)+"%");
            }
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(cnt++, 2, item);

        }else if(action.compare(RECOG_PROC) == 0)
        {
            QTableWidgetItem *item  = new QTableWidgetItem(QString::number(iter.key()));
            item->setTextAlignment(Qt::AlignCenter);
            Pic<uchar> pimg;
            if(capID == CAM_CAP){
                pimg.createToGray(temp,3);
            }else if(capID == PIC_CAP){
                pimg.createToGray(temp,4);
            }
            int predict = cnn->test_Pic(pimg);
            if(predict >= 0){
                item  = new QTableWidgetItem(QString::number(predict));
            }else{
                item  = new QTableWidgetItem("error");
            }

            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(cnt++, 2, item);
        }else{
            cnt++;
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
    vect.clear();
    array.append((char *)&totallen, sizeof(totallen));
    array.append((char *)&totallen, sizeof(totallen));

    while(viter.hasNext())
    {
        blockid = viter.next();

        if(ui->label_2->getRegular()->recMap.contains(blockid))
        {
            CusRect rect = ui->label_2->getRegular()->recMap.value(blockid);
            QRect rec = rect.getRect(image.width(), image.height());
            QImage temp = image.copy(rec);
            QString action = ui->label_2->getRegular()->actionMap.value(blockid);

            if(action.compare(MATCH_PROC) == 0)
            {
                Pic<uchar> pimg;
                if(capID == CAM_CAP){
                    pimg.createToGray(temp,3);
                }else if(capID == PIC_CAP){
                    pimg.createToGray(temp,4);
                }
                double res = mul_tempRoi(pimg,ui->label_2->getRegular()->tempsMap.value(blockid).temps,1);
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
                custdata.replybuffer.similarity = 100 - static_cast<int>(res * 100.0f + .5f);
                qDebug() << res << res * 100.0f << custdata.replybuffer.similarity;

            }
            else if(action.compare(RECOG_PROC) == 0)
            {
                Pic<uchar> pimg;
                if(capID == CAM_CAP){
                    pimg.createToGray(temp,3);
                }else if(capID == PIC_CAP){
                    pimg.createToGray(temp,4);
                }
                int predict = cnn->test_Pic(pimg);
                custdata.replybuffer.number = predict;
            }
            custdata.replybuffer.similarity = custdata.replybuffer.similarity % 101;
            custdata.replybuffer.id = blockid;
            custdata.replybuffer.width  = temp.width();
            custdata.replybuffer.height = temp.height();
            custdata.replybuffer.left   = rec.left();
            custdata.replybuffer.up     = rec.top();

            array.append((char *)(&(custdata.replybuffer)), sizeof(custdata.replybuffer));
            totalblock++;
            qDebug() << "totalblock:" << totalblock;
        }
    }

    uint *src = new uint[image.width()*image.height()];
    if(capID == CAM_CAP){
        TUtil::convertToRGBA(image,src,3);
    }else if(capID == PIC_CAP){
        TUtil::convertToRGBA(image,src,4);
    }

    array.append((char *)src);
    totallen = array.size();

    *(UINT32 *)(array.data()) = totallen;
    *(UINT32 *)(array.data()+4) = totalblock;

    qDebug() << "array:" << (int)array.at(0) << (int)array.at(1) << (int)array.at(2) << (int)array.at(3) ;
    qDebug() << "array:" << (int)array.at(4) << (int)array.at(5) << (int)array.at(6) << (int)array.at(7) ;
    tcpworker->doprocessimage = 0;
    tcpworker->sendCmd(array.data(), array.size());
    delete []src;
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


void MainWindow::tcpstartrw()
{
    tcpworker->exit();
}

void MainWindow::capimg()
{
    if(capID == CAM_CAP){
        image = cuscamera->imageproc->getImg();
        ui->label_2->setPixmap(QPixmap::fromImage(image.scaled(ui->label_2->width(),ui->label_2->height())));
    }
}

void MainWindow::on_savePicButton_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, tr("保存图片"), QDir::homePath(), tr("Image Files(*.bmp)"));
    QPixmap pixmap = QPixmap::fromImage(image);
    pixmap.save(path,"bmp",100);
}

void MainWindow::on_saveFileButton_clicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("保存流程文件"), QDir::homePath(),
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(path.length()!=0)
    {
        ui->label_2->getRegular()->savePatam2File(path);
        QMessageBox::about(NULL, "", "保存流程文件成功");
    }

}

void MainWindow::on_loadFileButton_clicked()
{
    QFileDialog::Options options = QFileDialog::ShowDirsOnly;
    QString path = QFileDialog::getExistingDirectory(this, tr("载入流程文件"), QDir::homePath(),
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(path.length()!=0)
    {
        ui->label_2->getRegular()->update(path);
        CusRectListChanged(ui->label_2->getRegular()->recMap,ui->label_2->getRegular()->actionMap);
        updateStatusBar();
    }
}
