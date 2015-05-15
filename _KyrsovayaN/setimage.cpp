#include "setimage.h"
#include <QGraphicsTextItem>
#include <QFont>
#include <QBrush>
#include <QIcon>

setimage::setimage(QGraphicsItem *parent): QGraphicsRectItem(parent)
{
  QPixmap set_image;
  set_image.load(":/new/prefix1/settings_image.png");
        setRect(10,15,100,90);
        QBrush brush(set_image);
        setBrush(brush);

	// allow responding to hover events
	setAcceptHoverEvents(true);

}

setimage::~setimage()
{

}

void setimage::mousePressEvent(QGraphicsSceneMouseEvent *event){
        emit clicked();
}

void setimage::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
        // change color to cyan
  setRect(10,15,115,100);
//        QBrush brush;
//        brush.setStyle(Qt::SolidPattern);
//        brush.setColor(Qt::cyan);
//        setBrush(brush);
}

void setimage::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
        // change color to dark cyan
  setRect(10,15,100,90);
//        QBrush brush;
//        brush.setStyle(Qt::SolidPattern);
//        //brush.setColor(Qt::darkCyan);
//        brush.setColor(QColor(0,139,139,0));
//        setBrush(brush);
}
