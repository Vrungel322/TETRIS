
#include "singleton.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QPicture>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	singleton::instance().run();

	return a.exec();
}
