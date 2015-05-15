#ifndef TEST
#define TEST


#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class bonusbutton:public QObject, public QGraphicsRectItem
{
	Q_OBJECT
public:
	bonusbutton(QString name, QGraphicsItem* parent=NULL);
	QGraphicsRectItem* test;
	int dx=150;
	  int dy=150;
	  bool nadpis=true;

	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
	void activated();

signals:
	void clicked();
private:
	QGraphicsTextItem* text;


	~bonusbutton();
};


#endif // TEST

