#include <QWidget>
#include <QDebug>
#include <QApplication>
#include <QMediaPlayer>

#include "singleton.h"
#include "gamewidget.h"


singleton::singleton() {}

singleton& singleton::instance() {
  static singleton instance;
  return instance;
}

int singleton::run() {

  view.show();
  view.Loading();
}
