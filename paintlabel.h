#ifndef PAINTLABEL_H
#define PAINTLABEL_H
#include <QLabel>
#include "CusRect.h"
#include <QMap>

class PaintLabel:public QLabel
{
    Q_OBJECT
public:
    explicit PaintLabel(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);

    QMap<int, CusRect> recMap;
};
#endif // PAINTLABEL_H
