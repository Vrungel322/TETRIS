#ifndef RECORDS_H
#define RECORDS_H

#include <QObject>
#include <QWidget>
//#include <stdio.h>
//#include <conio.h>
//#include <stdlib.h>
//#include <string.h>

class records
{
public:
  records();

  QString name;
  QString score;
  QString nomer;
 //  FILE *f;;
   //char *txt = NULL;
  // char* fn;


  void read(int i);
  QString buffer[10];
   void write();
   void Remove();
  ~records();
};

#endif // RECORDS_H
