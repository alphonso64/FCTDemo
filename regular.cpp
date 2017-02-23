#include "regular.h"
#include "qDebug.h"
#include "imageproc.h"
#include "algorithm/match_util.h"
#include <QFile>
#define PARAM_ARRAY "recParam"
Regular::Regular()
{
    recMap.clear();
    actionMap.clear();
    tempsMap.clear();
    mapIndex = 1;
}

void Regular::setActionMapContent(int key, QString value)
{
    if(actionMap.contains(key))
    {
        actionMap.remove(key);
        actionMap.insert(key,value);
    }
}

void Regular::update(QString path)
{
    pattenPath = path;
    recMap.clear();
    actionMap.clear();
    tempsMap.clear();
    int temp = 0;
    QSettings *settings = new QSettings(path+"/config", QSettings::IniFormat);
    float x1 = settings->value("trans_x1").toFloat();
    float x2 = settings->value("trans_x2").toFloat();
    float y1 = settings->value("trans_y1").toFloat();
    float y2 = settings->value("trans_y2").toFloat();
    transRec = CusRect(x1,y1,x2,y2);
    int size = settings->beginReadArray(PARAM_ARRAY);
    qDebug()<<"update"<<size;
    for (int i = 0; i < size; ++i) {
        settings->setArrayIndex(i);
        int id = settings->value("id").toInt();
        float x1 = settings->value("x1").toFloat();
        float x2 = settings->value("x2").toFloat();
        float y1 = settings->value("y1").toFloat();
        float y2 = settings->value("y2").toFloat();
        QString action = settings->value("action").toString();
        temp = temp>id?temp:id;
        PatternFile pattern;
        if(action.compare(MATCH_PROC) == 0){
            QString name = settings->value("temp").toString();
            pattern.name = name;
            pattern.path = path;
            QImage tempImg(path+"/"+name);
            Pic<uchar> pimg;
            pimg.createToGray(tempImg,4);
            pattern.temps = make_temps(pimg);
        }
        recMap.insert(id,CusRect(x1,y1,x2,y2));
        actionMap.insert(id,action);
        tempsMap.insert(id,pattern);
    }
    mapIndex = temp+1;
    settings->endArray();
}

void Regular::setTempsMapContent(int key, PatternFile value)
{
    if(tempsMap.contains(key))
    {
        tempsMap.remove(key);
        tempsMap.insert(key,value);
    }
}

void Regular::removeRectMapContent(int key)
{
    if(actionMap.contains(key))
    {
        actionMap.remove(key);
    }
    if(recMap.contains(key))
    {
        recMap.remove(key);
    }
    if(tempsMap.contains(key))
    {
        tempsMap.remove(key);
    }
}

void Regular::savePatam2File(QString path)
{
    QString filePath(path+"/config");
    QFile mFile(filePath);
    if(mFile.exists())
    {
        mFile.remove();
    }
    QSettings *settings = new QSettings(path+"/config", QSettings::IniFormat);
    settings->setValue("trans_x1",  QString("%1").arg(transRec.x1));
    settings->setValue("trans_x2",  QString("%1").arg(transRec.x2));
    settings->setValue("trans_y1",  QString("%1").arg(transRec.y1));
    settings->setValue("trans_y2",  QString("%1").arg(transRec.y2));
    settings->beginWriteArray(PARAM_ARRAY);
    QMapIterator<int, CusRect> iter(recMap);
    int i=0;
    while (iter.hasNext()){
        iter.next();
        settings->setArrayIndex(i++);
        CusRect cusrect= iter.value();
        settings->setValue("id",  QString::number(iter.key()));
        settings->setValue("x1",  QString("%1").arg(cusrect.x1));
        settings->setValue("x2",  QString("%1").arg(cusrect.x2));
        settings->setValue("y1",  QString("%1").arg(cusrect.y1));
        settings->setValue("y2",  QString("%1").arg(cusrect.y2));
        if(actionMap.contains(iter.key())){
            QString action = actionMap.value(iter.key());
            settings->setValue("action",  action);
            if(action.compare(MATCH_PROC)==0){
                PatternFile pattern = tempsMap.value(iter.key());
                QImage image(pattern.path+"/"+pattern.name);
                qDebug()<<path+"/"+pattern.name<<image.width()<<pattern.path;
                image.save(path+"/"+pattern.name);
                settings->setValue("temp",  pattern.name);
            }
        }
    }
    settings->endArray();
}
