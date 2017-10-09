#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <algorithm/match_util.h>
#include "util.h"
#include "patternfile.h"
#include "thsettingdialog.h"

static void getRgbAndGray(QImage image,int depth,int &r,int &g,int &b,int &gray)
{
    uint tempR = 0;
    uint tempG = 0;
    uint tempB = 0;
    uint cnt =0;
    for (int ii = 0; ii < image.height(); ii++) {
        uchar* scan = image.scanLine(ii);
        for (int jj = 0; jj < image.width(); jj++) {
            QRgb* rgbpixel = reinterpret_cast<QRgb*>(scan + jj*depth);
            int red =qRed(*rgbpixel);
            int green =qGreen(*rgbpixel);
            int blue =qBlue(*rgbpixel);
            if(red>60 || green>60 || blue>60)
            {
                tempR +=red;
                tempB +=blue;
                tempG +=green;
                cnt++;
            }
        }
    }

    if(cnt > 20)
    {
        r =tempR / cnt;
        b =tempB / cnt;
        g =tempG / cnt;
        gray = (r*299 + g*587 + b*114 + 500) / 1000;
    }else{
        r =0;
        b =0;
        g =0;
        gray = 0;
    }

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("FCTDEMO");
    dialog.setWindowTitle("Threshold setting");

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
    ui->calibrationButton->setCheckable(true);
    ui->camButton->setChecked(true);

    group.addButton(ui->camButton,CAM_CAP);
    group.addButton(ui->picButton,PIC_CAP);
    group.addButton(ui->calibrationButton,CALI_CAP);

    capID = CAM_CAP;

    ui->addButton->setCheckable(true);
    ui->addTransButton->setCheckable(true);
    initNet();
    vect.clear();
    tcpworker = new TCPRWWorker();
    tcpworker->isthreadstopped = 0;
    tcpworker->doprocessimage  = 0;
    tcpworker->listenSocket = new QTcpServer;
    tcpworker->listenSocket->listen(QHostAddress::AnyIPv4, 15555);
    tcpworker->start();

    cuscamera = new CusCamera();

    connect(ui->label_2, SIGNAL(ListChanged(QMap<int, CusRect>,QMap<int, QString>)), this, SLOT(CusRectListChanged(QMap<int, CusRect>,QMap<int, QString>)));
    connect(ui->addButton, SIGNAL(toggled(bool)), this, SLOT(AddClick(bool)));
    connect(ui->addTransButton, SIGNAL(toggled(bool)), this, SLOT(AddTransClick(bool)));
    connect(ui->matchButton, SIGNAL(clicked()), this, SLOT(MatchClick()));
    connect(ui->recButton, SIGNAL(clicked()), this, SLOT(RecogClick()));
    connect(ui->delButton, SIGNAL(clicked()), this, SLOT(DelClick()));
    connect(ui->captureButton,SIGNAL(clicked()), this, SLOT(detectClick()));
    connect(cuscamera, SIGNAL(capRdy()), this, SLOT(capimg()));
    connect(cuscamera, SIGNAL(camInitRdy(int)), this, SLOT(camInitRdy(int)));
    connect(tcpworker, SIGNAL(processImg(int)), this, SLOT(proecssBlock(int)));
    connect(tcpworker,SIGNAL(loadPatternFile(int)),this,SLOT(loadPatternFile(int)));
    connect(tcpworker,SIGNAL(selectImageSrc(int)),this,SLOT(selectImageSrc(int)));
    connect(tcpworker,SIGNAL(changeImage(int)),this,SLOT(changeImage(int)));
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveimg()));
    connect(&group,SIGNAL(buttonClicked(int)),this,SLOT(camSelect(int)));
    connect(ui->comboBox, SIGNAL(activated(int)), this, SLOT(changeMode()));
    connect(&dialog, SIGNAL(finished(int)), this, SLOT(dialogdone(int)));

    cuscamera->start();
    statusBar()->addWidget( statusLabel = new QLabel("正在打开摄像机 "));
    statusBar()->addWidget( statusLabel_ = new QLabel("流程文件：未选择"));
    statusBar()->setContentsMargins(6,0,0,0);
    statusLabel_->setContentsMargins(6,0,0,0);
    ui->camButton->setEnabled(false);
    ui->picButton->setEnabled(false);
    ui->calibrationButton->setEnabled(false);

//    addOp(QPainter::CompositionMode_SourceOver, tr("SourceOver"));
//    addOp(QPainter::CompositionMode_DestinationOver, tr("DestinationOver"));
//    addOp(QPainter::CompositionMode_Clear, tr("Clear"));
//    addOp(QPainter::CompositionMode_Source, tr("Source"));
//    addOp(QPainter::CompositionMode_Destination, tr("Destination"));
//    addOp(QPainter::CompositionMode_SourceIn, tr("SourceIn"));
//    addOp(QPainter::CompositionMode_DestinationIn, tr("DestinationIn"));
//    addOp(QPainter::CompositionMode_SourceOut, tr("SourceOut"));
//    addOp(QPainter::CompositionMode_DestinationOut, tr("DestinationOut"));
//    addOp(QPainter::CompositionMode_SourceAtop, tr("SourceAtop"));
//    addOp(QPainter::CompositionMode_DestinationAtop, tr("DestinationAtop"));
//    addOp(QPainter::CompositionMode_Xor, tr("Xor"));
//    addOp(QPainter::CompositionMode_Plus, tr("Plus"));
//    addOp(QPainter::CompositionMode_Multiply, tr("Multiply"));
//    addOp(QPainter::CompositionMode_Screen, tr("Screen"));
//    addOp(QPainter::CompositionMode_Overlay, tr("Overlay"));
//    addOp(QPainter::CompositionMode_Darken, tr("Darken"));
//    addOp(QPainter::CompositionMode_Lighten, tr("Lighten"));
//    addOp(QPainter::CompositionMode_ColorDodge, tr("ColorDodge"));
//    addOp(QPainter::CompositionMode_ColorBurn, tr("ColorBurn"));
//    addOp(QPainter::CompositionMode_HardLight, tr("HardLight"));
//    addOp(QPainter::CompositionMode_SoftLight, tr("SoftLight"));
//    addOp(QPainter::CompositionMode_Difference, tr("Difference"));
//    addOp(QPainter::CompositionMode_Exclusion, tr("Exclusion"));
    ui->comboBox->setVisible(false);

    mode = QPainter::CompositionMode_Difference;

}

void MainWindow::dialogdone(int value)
{
    QFileInfo fileInfo(dialog.filePath);
    int row = ui->tableWidget->currentRow();
    QTableWidgetItem *item  = new QTableWidgetItem(MATCH_PROC_TEXT+"("+fileInfo.fileName()+")"+"("+QString::number(value)+")");
    item->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->setItem(row, 1, item);
    PatternFile pattern;
    pattern.name = fileInfo.fileName();
    pattern.path = fileInfo.path();
    pattern.th = value;
    QImage tempImg(fileInfo.filePath());
    Pic<uchar> pimg;
    pimg.createToGray(tempImg,4);
    pattern.temps = make_temps(pimg,pattern.th);
    pimg.release();

//    for(int i=0;i<pattern.temps.size();i++){
//        if(pattern.temps[i].data!=NULL)
//        {
//            qDebug()<<"pattern.temps"<<pattern.temps[i].data;
//        }
//    }

    ui->label_2->getRegular()->setActionMapContent(dialog.key,MATCH_PROC);
    ui->label_2->getRegular()->setTempsMapContent(dialog.key,pattern);
}

void MainWindow::changeMode()
{
    mode =  (QPainter::CompositionMode) ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt();
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
    }else if(capID == PIC_CAP){
        if(res == FAIL){
            val.append("未选择本地图片 ");
        }else{
            val.append("图像来源：本地图片 分辨率："+QString::number(image.width())+"x"+QString::number(image.height()));
        }
    }else if(capID == CALI_CAP){
        if(res == FAIL){
            val.append("未选择校准图片 ");
        }else{
            val.append("摄像机校准中");
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
            ui->calibrationButton->setEnabled(false);
            cuscamera->start();
        }else{
            updateStatusBar(SUCCESS);
        }
    }else if(id == PIC_CAP){
        capID = PIC_CAP;
        QString path = QFileDialog::getOpenFileName(this, tr("选择图片"), TEMPSPATH, tr("Image Files(*.bmp)"));
        if(path.length() == 0) {
            updateStatusBar(FAIL);
            ui->label_2->setPixmap(QPixmap(ui->label_2->width(),ui->label_2->height()));
        }else{
            image = QImage(path);
            ui->label_2->setPixmap(QPixmap::fromImage(image.scaled(ui->label_2->width(),ui->label_2->height())));
            updateStatusBar(SUCCESS);
        }
    }else if(id == CALI_CAP){
        QString path = QFileDialog::getOpenFileName(this, tr("选择图片"), TEMPSPATH, tr("Image Files(*.bmp)"));
        if(path.length() == 0) {
            capID = CALI_CAP;
            caliFlag = false;
            updateStatusBar(FAIL);
        }else{
            caliImage = QPixmap(path);
            capID = CALI_CAP;
            caliFlag = true;
            updateStatusBar(SUCCESS);
        }
    }
}

void MainWindow::selectImageSrc(int code)
{
    int val = 1;
    if(code == 0)
    {
        capID = CAM_CAP;
        if(cuscamera->isFinished()){
            statusLabel->setText("正在打开摄像机");
            ui->camButton->setEnabled(false);
            ui->picButton->setEnabled(false);
            ui->calibrationButton->setEnabled(false);
            cuscamera->start();
        }else{
            updateStatusBar(SUCCESS);
        }
        ui->camButton->setChecked(true);
    }else if(code == 1)
    {
        capID = PIC_CAP;
        updateStatusBar(FAIL);
        ui->label_2->setPixmap(QPixmap(ui->label_2->width(),ui->label_2->height()));
        ui->picButton->setChecked(true);
    }else
    {
        val = 0;
    }
    tcpworker->sendCmd((char *)&val, 4);
}

void MainWindow::changeImage(int code)
{
    int val = 1;
    if(capID == CAM_CAP)
    {
        val = 0;
    }else
    {
        if(ui->label_2->getRegular()->pattenPath.length() == 0)
        {
            val = 0;
        }else
        {
            QString path;
            path.append(ui->label_2->getRegular()->pattenPath);
            path.append("/");
            path.append(QString::number(code));
            path.append(".bmp");
            qDebug()<<ui->label_2->getRegular()->pattenPath;
            qDebug()<<path;
            QFile file(path);
            if(file.exists())
            {
                image = QImage(path);
                ui->label_2->setPixmap(QPixmap::fromImage(image.scaled(ui->label_2->width(),ui->label_2->height())));
                updateStatusBar(SUCCESS);
            }else{
                val = 0;
            }
            file.close();
        }
    }
    tcpworker->sendCmd((char *)&val, 4);
}

void MainWindow::camInitRdy(int val)
{
    updateStatusBar(val);
    ui->camButton->setEnabled(true);
    ui->picButton->setEnabled(true);
    ui->calibrationButton->setEnabled(true);
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
            int th = ui->label_2->getRegular()->tempsMap.value(iter.key()).th;
            QTableWidgetItem *item  = new QTableWidgetItem(MATCH_PROC_TEXT+"("+temp+")"+"("+QString::number(th)+")");
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
        if(ui->addTransButton->isChecked())
        {
            ui->addTransButton->setChecked(false);
            ui->label_2->disableTransRect();
        }
    }else{
        ui->label_2->disableRect();
    }
}

void MainWindow::AddTransClick(bool flag)
{
    if(flag)
    {
        if(ui->addButton->isChecked())
        {
            ui->addButton->setChecked(false);
            ui->label_2->disableRect();
        }
        ui->label_2->enableTransRect();
    }else
    {
        ui->label_2->disableTransRect();
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
            int key = ui->tableWidget->item(row,0)->text().toInt();
            dialog.filePath = path;
            dialog.key = key;
            dialog.show();

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
        QString action = ui->label_2->getRegular()->actionMap.value(iter.key());
        if(action.compare(MATCH_PROC) == 0)
        {
            QTableWidgetItem *item  = new QTableWidgetItem(QString::number(iter.key()));
            item->setTextAlignment(Qt::AlignCenter);
            Pic<uchar> pimg;
            int r,g,b,gray;
            if(capID == CAM_CAP){
                getRgbAndGray(temp,3,r,g,b,gray);
                pimg.createToGray(temp,3);
            }else if(capID == PIC_CAP){
                getRgbAndGray(temp,4,r,g,b,gray);
                pimg.createToGray(temp,4);
            }
            PatternFile pa = ui->label_2->getRegular()->tempsMap.value(iter.key());

            double res = mul_tempRoi(pimg,pa.temps,1,pa.th);
            if(res <-0.1f)
            {
                item  = new QTableWidgetItem("error");
            }else{
                int val = (1-res)*100;
                item  = new QTableWidgetItem(QString::number(val)+"%");
            }
            item->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(cnt++, 2, item);
            pimg.release();
        }else if(action.compare(RECOG_PROC) == 0)
        {
            QTableWidgetItem *item  = new QTableWidgetItem(QString::number(iter.key()));
            item->setTextAlignment(Qt::AlignCenter);
            Pic<uchar> pimg;
            int r,g,b,gray;
            if(capID == CAM_CAP){
                getRgbAndGray(temp,3,r,g,b,gray);
                pimg.createToGray(temp,3);
            }else if(capID == PIC_CAP){
                getRgbAndGray(temp,4,r,g,b,gray);
                pimg.createToGray(temp,4);
            }
            int predict = cnn->test_Pic(pimg);
            if(predict >= 0){
                item  = new QTableWidgetItem(QString::number(predict));
            }else{
                item  = new QTableWidgetItem("error");
            }
            pimg.release();

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

    UINT32 totallen = 0;
    vect.clear();
    array.append((char *)&totallen, sizeof(totallen));
    array.append((char *)&totallen, sizeof(totallen));
    array.append((char *)&totallen, sizeof(totallen));
    array.append((char *)&totallen, sizeof(totallen));

    CusRect cusrec = ui->label_2->getRegular()->transRec;
    QImage srcImage;
    if(cusrec.x1>0.001 && cusrec.x2>0.001 && cusrec.y1>0.001 && cusrec.y2>0.001)
    {
        QRect rec = cusrec.getRect(image.width(), image.height());
        srcImage = image.copy(rec);
        //qDebug()<<"cusrec into";
    }else{
        srcImage = image;
        //qDebug()<<"cusrec no into";
    }

    while(viter.hasNext())
    {
        blockid = viter.next();

        if(ui->label_2->getRegular()->recMap.contains(blockid))
        {
            CusReplyData  custdata;
            CusRect rect = ui->label_2->getRegular()->recMap.value(blockid);
            QRect rec = rect.getRect(image.width(), image.height());
            QImage temp = image.copy(rec);
            QString action = ui->label_2->getRegular()->actionMap.value(blockid);
            int r,g,b,gray;
            if(action.compare(MATCH_PROC) == 0)
            {
                Pic<uchar> pimg;
                if(capID == CAM_CAP){
                    getRgbAndGray(temp,3,r,g,b,gray);
                    pimg.createToGray(temp,3);
                }else if(capID == PIC_CAP){
                    getRgbAndGray(temp,4,r,g,b,gray);
                    pimg.createToGray(temp,4);
                }
                PatternFile pa = ui->label_2->getRegular()->tempsMap.value(blockid);

                double res = mul_tempRoi(pimg,pa.temps,1,pa.th);
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
                custdata.replybuffer.r = r;
                custdata.replybuffer.g = g;
                custdata.replybuffer.b = b;
                custdata.replybuffer.grayscale = gray;
                custdata.replybuffer.similarity = 100 - static_cast<int>(res * 100.0f + .5f); 
                pimg.release();

            }
            else if(action.compare(RECOG_PROC) == 0)
            {
                Pic<uchar> pimg;

                if(capID == CAM_CAP){
                    getRgbAndGray(temp,3,r,g,b,gray);
                    pimg.createToGray(temp,3);
                }else if(capID == PIC_CAP){
                    getRgbAndGray(temp,4,r,g,b,gray);
                    pimg.createToGray(temp,4);
                }
                int predict = cnn->test_Pic(pimg);
                //qDebug()<<"predict"<<predict;
                custdata.replybuffer.number = predict;
                pimg.release();
            }
            custdata.replybuffer.r = r;
            custdata.replybuffer.g = g;
            custdata.replybuffer.b = b;
            custdata.replybuffer.grayscale = gray;
            custdata.replybuffer.similarity = custdata.replybuffer.similarity % 101;
            custdata.replybuffer.id = blockid;
            custdata.replybuffer.width  = temp.width();
            custdata.replybuffer.height = temp.height();
            custdata.replybuffer.left   = rec.left();
            custdata.replybuffer.up     = rec.top();
            array.append((char *)(&(custdata.replybuffer)), sizeof(custdata.replybuffer));
            totalblock++;
        }
    }
    uint *src = new uint[srcImage.width()*srcImage.height()];
    if(capID == CAM_CAP){
        TUtil::camconvertToRGBA(srcImage,src);
    }else if(capID == PIC_CAP){
        TUtil::bmpconvertToRGBA(srcImage,src);
    }
    array.append((char *)src,srcImage.width()*srcImage.height()*4);
    totallen = array.size();
    *(UINT32 *)(array.data()) = totallen;
    *(UINT32 *)(array.data()+4) = totalblock;
    *(UINT32 *)(array.data()+8) = srcImage.width();
    *(UINT32 *)(array.data()+12) = srcImage.height();

    tcpworker->doprocessimage = 0;
    tcpworker->sendCmd(array.data(), array.size());
    delete []src;
}

void MainWindow::loadPatternFile(int code)
{
    int val = 0;
    QSettings *configIniRead = new QSettings(PATTERN_FILE_PATH, QSettings::IniFormat);
    QString key("/config/");
    key.append(QString::number(code));
    qDebug()<<PATTERN_FILE_PATH<<key;
    QString path = configIniRead->value(key).toString();
    qDebug()<<path;
    if(path.length() != 0)
    {
        val = 1;
        ui->label_2->getRegular()->update(path);
        CusRectListChanged(ui->label_2->getRegular()->recMap,ui->label_2->getRegular()->actionMap);
        updateStatusBar();
    }
    tcpworker->sendCmd((char *)&val, 4);
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
    }else if(capID == CALI_CAP)
    {
        if(caliFlag){
            image = cuscamera->imageproc->getImg();
            QPixmap input1 = caliImage.scaled(ui->label_2->width(),ui->label_2->height());
            QPixmap output1(input1.size());
            output1.fill(Qt::transparent);
            QPainter p(&output1);
            p.drawPixmap(0, 0, input1);
            p.end();

            QPixmap input2 = QPixmap::fromImage(image.scaled(ui->label_2->width(),ui->label_2->height()));
            QPixmap output2(input2.size());
            output2.fill(Qt::transparent);
            QPainter p1(&output2);
            p1.drawPixmap(0, 0, input2);
            p1.end();

            QPixmap baseImg(output2.size());
            QPainter painter(&baseImg);
            painter.setCompositionMode(QPainter::CompositionMode_Source);
            painter.fillRect(baseImg.rect(), Qt::transparent);
            painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
            painter.drawPixmap(0, 0, input1);
            painter.setCompositionMode(mode);
            painter.drawPixmap(0, 0, input2);
            painter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
            painter.end();
            ui->label_2->setPixmap(baseImg);
        }else{
            image = cuscamera->imageproc->getImg();
            ui->label_2->setPixmap(QPixmap::fromImage(image.scaled(ui->label_2->width(),ui->label_2->height())));
        }
    }
}

void MainWindow::addOp(QPainter::CompositionMode mode, const QString &name)
{
    ui->comboBox->addItem(name, mode);
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
    qDebug()<<path;

    if(path.length()!=0)
    {
        ui->label_2->getRegular()->update(path);
        CusRectListChanged(ui->label_2->getRegular()->recMap,ui->label_2->getRegular()->actionMap);
        updateStatusBar();
    }
}


