#include "records.h"
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>

#include <QDate>
#include <QCoreApplication>


#include <QDebug>
#include <QFile>

using namespace std;

records::records()
{

}

void records::read(int i)
{qDebug()<<i;
  //QFile file1(":/new/prefix1/scores.txt");
  QFile f(".//scores.txt");
       if (f.open(QIODevice::ReadOnly|QIODevice::Text))
       {
          // qDebug()<<"gggg";
          QTextStream s(&f);
          //buffer =s.readAll();
          for (int j=0; j<3*i; j++)
            s.readLine(0);
          nomer = s.readLine(3);
          name = s.readLine(100);
          score = s.readLine(7);

        }

      // f.flush();
       f.close();
}

void records::write()
{
  QFile f(".//scores.txt");
       if (f.open(QIODevice::Append|QIODevice::Text))
       {
           QTextStream s(&f);
           s << nomer<<endl;
           s << name<<endl;
           s << score<<endl;

         }
       f.close();

}

void records::Remove(){

  QFile f(".//scores.txt");
  if (f.open(QIODevice::WriteOnly|QIODevice::Text)){

  }
  f.close();
}


records::~records()
{
}

