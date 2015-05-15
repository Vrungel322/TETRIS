#ifndef ELEMENT_H
#define ELEMENT_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class element : public QObject, public QGraphicsRectItem
{
	Q_OBJECT
public:
	element(QGraphicsItem *parent = NULL);

	int size, activ,color;
	void paint_element(int , int, int);
	void paint_n_element(int, int, int);

	~element();
};

#endif // ELEMENT_H
