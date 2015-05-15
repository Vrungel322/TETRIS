#ifndef SETIMAGE
#define SETIMAGE

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class setimage:public QObject, public QGraphicsRectItem
{
	Q_OBJECT
public:
	setimage(QGraphicsItem* parent=NULL);

	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

	~setimage();
signals:
	void clicked();
};

#endif // SETIMAGE

