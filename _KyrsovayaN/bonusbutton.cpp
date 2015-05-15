#include "bonusbutton.h"

#include <QGraphicsTextItem>
#include <QFont>
#include <QBrush>

bonusbutton::bonusbutton(QString name, QGraphicsItem *parent): QGraphicsRectItem(parent)
{

  //animation=new QTimer();
  setRect(0,0,150,150);
  QBrush brush;
  brush.setStyle(Qt::SolidPattern);
  //brush.setColor(QColor(0,139,139,0));
  setBrush(brush);

  // draw the text
  text = new QGraphicsTextItem(name,this);
  text->setFont(QFont ("comic sans ms", 20 ,Qt::AlignCenter));
  int xPos = rect().width()/2 - text->boundingRect().width()/2;
  int yPos = rect().height()/2 - text->boundingRect().height()/2;
  text->setPos(xPos,yPos);

  // allow responding to hover events
  setAcceptHoverEvents(true);

}

bonusbutton::~bonusbutton()
{

}

void bonusbutton::mousePressEvent(QGraphicsSceneMouseEvent *event){
        emit clicked();
}

void bonusbutton::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
        // change color to cyan
//  setRect(-18,0,236,50);
//        QBrush brush;
//        brush.setStyle(Qt::Dense3Pattern);
//        brush.setColor(Qt::cyan);
//        setBrush(brush);
}

void bonusbutton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
        // change color to dark cyan
//  setRect(0,0,200,50);
//        QBrush brush;
//        brush.setStyle(Qt::SolidPattern);
//        //brush.setColor(Qt::darkCyan);
//        brush.setColor(QColor(0,139,139,0));
//        setBrush(brush);
}

void bonusbutton::activated()
{
  QRect rr;
  rr.setRect(-18,0,dx,dy);

        QBrush brush;
        brush.setStyle(Qt::Dense3Pattern);
        brush.setColor(Qt::red);
        setBrush(brush);
        nadpis=false;

}

