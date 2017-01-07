#ifndef CUSLABEL_H
#define CUSLABEL_H
#include <QLabel>
#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QMap>
#include "CusRect.h"
class CusLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CusLabel(QWidget *parent = 0);
    CusLabel();
    void enableRect();
    void disableRect();
    void setActionMapContent(int key,QString value);
    void setTempsMapContent(int key,QString value);
    void removeRectMapContent(int key);
    QMap<int, CusRect> recMap;
    QMap<int, QString> actionMap;
    QMap<int, QString> tempMap;
signals:
    void ListChanged(QMap<int, CusRect> recMap,QMap<int, QString> actionMap);

protected:
    int mapIndex;
    bool startflag;
    bool drawflag;
    QPoint startPoint;
    QPoint endPoint;

    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // CUSLABEL_H
