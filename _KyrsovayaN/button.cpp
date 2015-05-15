#include "button.h"

#include <QGraphicsTextItem>
#include <QFont>
#include <QBrush>

button::button(QString name, QGraphicsItem *parent): QGraphicsRectItem(parent)
{
        setRect(0,0,200,50);
        /*
  test=new QGraphicsRectItem(0);
          test->setPos(0,0);
          QPen pointpen(Qt::black);
          test->setPen(pointpen);*/
        QBrush brush;
        brush.setStyle(Qt::Dense4Pattern);
        //brush.setColor(Qt::/*darkCyan*/green);
        brush.setColor(QColor(255,255,255,177));
	setBrush(brush);

	// draw the text
	text = new QGraphicsTextItem(name,this);
	text->setFont(QFont ("comic sans ms", 28 ));
	int xPos = rect().width()/2 - text->boundingRect().width()/2;
	int yPos = rect().height()/2 - text->boundingRect().height()/2;
	text->setPos(xPos,yPos);

	// allow responding to hover events
	setAcceptHoverEvents(true);

}

button::~button()
{

}

void button::mousePressEvent(QGraphicsSceneMouseEvent *event){
	emit clicked();
}

void button::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
	// change color to cyan
  setRect(-18,0,236,50);
        QBrush brush;
        brush.setStyle(Qt::Dense4Pattern);
        brush.setColor(Qt::cyan);
        setBrush(brush);

}

void button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
	// change color to dark cyan
  setRect(0,0,200,50);
        QBrush brush;
        brush.setStyle(Qt::Dense4Pattern);
        //brush.setColor(Qt::darkCyan);
        brush.setColor(QColor(255,255,255,177));
        setBrush(brush);
}
