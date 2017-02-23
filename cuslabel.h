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
#include "regular.h"

class CusLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CusLabel(QWidget *parent = 0);
    CusLabel();
    void enableRect();
    void disableRect();
    void enableTransRect();
    void disableTransRect();
    Regular* getRegular();

signals:
    void ListChanged(QMap<int, CusRect> recMap,QMap<int, QString> actionMap);

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    Regular *regular;
    bool startflag;
    bool drawflag;
    QPoint startPoint;
    QPoint endPoint;

    bool trans_startflag;
    bool trans_drawflag;
    QPoint trans_startPoint;
    QPoint trans_endPoint;
};

#endif // CUSLABEL_H
