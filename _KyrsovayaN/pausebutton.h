#ifndef PAUSEBUTTON
#define PAUSEBUTTON

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class pausebutton:public QObject, public QGraphicsRectItem
{
	Q_OBJECT
public:
	pausebutton(QGraphicsItem* parent=NULL);

	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

	~pausebutton();
signals:
	void clicked();
private:
};
#endif // PAUSEBUTTON

