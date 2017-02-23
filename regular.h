#ifndef REGULAR_H
#define REGULAR_H
#include "CusRect.h"
#include "QString"
#include <QMap>
#include <QObject>
#include <vector>
#include "algorithm/pic.h"
#include "patternfile.h"
#include <QSettings>
using namespace std;
class Regular
{
public:
    Regular();
    QMap<int, CusRect> recMap;
    QMap<int, QString> actionMap;
    QMap<int, PatternFile> tempsMap;
    CusRect transRec;
    void savePatam2File(QString path);
    void update(QString path);
    int mapIndex;
    QString pattenPath;
public:
    void setActionMapContent(int key,QString value);
    void setTempsMapContent(int key, PatternFile value);
    void removeRectMapContent(int key);
    void addRect(CusRect cusRect);

};

#endif // REGULAR_H
