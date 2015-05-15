#ifndef SINGLETON
#define SINGLETON

#include <QWidget>
#include <QMainWindow>
#include "gamewidget.h"


class singleton {
    GameWidget view;

	singleton();
	singleton(const singleton& root);
	singleton& operator=(const singleton&);
public:
	int run();
	static singleton& instance();
};

#endif // SINGLETON

