#include "pausebutton.h"
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QBrush>

pausebutton::pausebutton( QGraphicsItem *parent): QGraphicsRectItem(parent)
{
//  setRect(10,10,200,50);
//  setBrush((QBrush(QImage(":/new/prefix1//pause.png"))));




	// allow responding to hover events
	setAcceptHoverEvents(true);

}

pausebutton::~pausebutton()
{

}

void pausebutton::mousePressEvent(QGraphicsSceneMouseEvent *event){
	emit clicked();
}

void pausebutton::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
	// change color to cyan
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::cyan);
	setBrush(brush);
}

void pausebutton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
	// change color to dark cyan
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	brush.setColor(Qt::darkCyan);
	setBrush(brush);
}

