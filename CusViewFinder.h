#pragma once
#include <QCameraViewfinder>
#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QMap>
#include "CusRect.h"

class CusViewFinder :public QCameraViewfinder
{
    Q_OBJECT

public:
	CusViewFinder();

    void enableRect();
    void disableRect();
    void setActionMapContent(int key,QString value);

signals:
    void ListChanged(QMap<int, CusRect> recMap,QMap<int, QString> actionMap);

protected:

    QMap<int, CusRect> recMap;
    QMap<int, QString> actionMap;
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

