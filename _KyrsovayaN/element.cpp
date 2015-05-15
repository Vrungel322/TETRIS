#include "element.h"

#include <QBrush>
#include <QPainter>

element::element( QGraphicsItem *parent): QGraphicsRectItem(parent){

	size=22;
	activ = 0;
}

element::~element(){

}

void element::paint_element(int i, int j, int n){

	if (activ!=-1) color = n;
	setRect(105+size*j,-20+size*i,size+3,size+3);
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	QColor  element_color[8];
	element_color[0] = QColor(255,255,255,127);
	element_color[1] = QColor(0,0,0,127);
		if (activ)
			brush.setColor(element_color[1]);
		else
			brush.setColor(element_color[0]);
	setBrush(brush);
}

void element::paint_n_element(int i, int j, int n){

	setRect(495+size*j,20+size*i,size+3,size+3);
	QBrush brush;
	brush.setStyle(Qt::SolidPattern);
	QColor  n_element_color[8];
	n_element_color[0] = QColor(255,255,255,127);
	n_element_color[1] = QColor(0,0,0,127);
		if (n)
			brush.setColor(n_element_color[1]);
		else
			brush.setColor(n_element_color[0]);
	setBrush(brush);
}


