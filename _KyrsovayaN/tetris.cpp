#include "tetris.h"
#include <string.h>
#include <QDebug>
#include <QTimer>
#include <time.h>
#include "gamewidget.h"

tetris::tetris(QWidget *parent) : QWidget(parent)
{

  //выделение памяти под рабочее поле
          el=new element*[3+20+2];
          for (int i=0;i<3+20+2;i++)
                  el[i]=new element[2+10+2];

  //выделение памяти под поле следующей фигуры
          n_el=new element*[4];
          for (int i=0;i<4;i++)
                  n_el[i]=new element[4];

  //выделение памяти под столбики
          ob0=new int*[4];	n_ob0=new int*[4];
          ob11=new int*[4];	ob12=new int*[4];
          ob21=new int*[4];
          ob31=new int*[4];	ob32=new int*[4];	ob33=new int*[4];	ob34=new int*[4];
          ob41=new int*[4];	ob42=new int*[4];	ob43=new int*[4];	ob44=new int*[4];
          ob51=new int*[4];	ob52=new int*[4];
          ob61=new int*[4];	ob62=new int*[4];
          ob71=new int*[4];	ob72=new int*[4];	ob73=new int*[4];	ob74=new int*[4];
          for (int i=0;i<4;i++){//выделение памяти под строчки, обнуление матриц
                  ob0[i]=new int[4];	n_ob0[i]=new int[4];
                  ob11[i]=new int[4];	ob12[i]=new int[4];
                  ob21[i]=new int[4];
                  ob31[i]=new int[4];	ob32[i]=new int[4];	ob33[i]=new int[4];	ob34[i]=new int[4];
                  ob41[i]=new int[4];	ob42[i]=new int[4];	ob43[i]=new int[4];	ob44[i]=new int[4];
                  ob51[i]=new int[4];	ob52[i]=new int[4];
                  ob61[i]=new int[4];	ob62[i]=new int[4];
                  ob71[i]=new int[4];	ob72[i]=new int[4];	ob73[i]=new int[4];	ob74[i]=new int[4];
                  memset(ob11[i], 0, 4*sizeof(int));	memset(ob12[i], 0, 4*sizeof(int));
                  memset(ob21[i], 0, 4*sizeof(int));
                  memset(ob31[i], 0, 4*sizeof(int));	memset(ob32[i], 0, 4*sizeof(int));	memset(ob33[i], 0, 4*sizeof(int));	memset(ob34[i], 0, 4*sizeof(int));
                  memset(ob41[i], 0, 4*sizeof(int));	memset(ob42[i], 0, 4*sizeof(int));	memset(ob43[i], 0, 4*sizeof(int));	memset(ob44[i], 0, 4*sizeof(int));
                  memset(ob51[i], 0, 4*sizeof(int));	memset(ob52[i], 0, 4*sizeof(int));
                  memset(ob61[i], 0, 4*sizeof(int));	memset(ob62[i], 0, 4*sizeof(int));
                  memset(ob71[i], 0, 4*sizeof(int));	memset(ob72[i], 0, 4*sizeof(int));	memset(ob73[i], 0, 4*sizeof(int));	memset(ob74[i], 0, 4*sizeof(int));
          }
  //////////////////////////////////////////////////////////////////////////
          ob11[2][0]=1;	ob12[0][2]=1;
          ob11[2][1]=1;	ob12[1][2]=1;
          ob11[2][2]=1;	ob12[2][2]=1;
          ob11[2][3]=1;	ob12[3][2]=1;

          ob21[1][1]=1;
          ob21[1][2]=1;
          ob21[2][1]=1;
          ob21[2][2]=1;

          ob31[0][1]=1;	ob32[0][3]=1;	ob33[1][1]=1;	ob34[0][2]=1;
          ob31[1][1]=1;	ob32[0][2]=1;	ob33[1][2]=1;	ob34[1][2]=1;
          ob31[1][2]=1;	ob32[1][2]=1;	ob33[1][3]=1;	ob34[2][2]=1;
          ob31[1][3]=1;	ob32[2][2]=1;	ob33[2][3]=1;	ob34[2][1]=1;

          ob41[1][1]=1;	ob42[0][1]=1;	ob43[0][3]=1;	ob44[0][2]=1;
          ob41[1][2]=1;	ob42[0][2]=1;	ob43[1][1]=1;	ob44[1][2]=1;
          ob41[1][3]=1;	ob42[1][2]=1;	ob43[1][2]=1;	ob44[2][2]=1;
          ob41[2][1]=1;	ob42[2][2]=1;	ob43[1][3]=1;	ob44[2][3]=1;

          ob51[1][2]=1;	ob52[0][1]=1;
          ob51[1][3]=1;	ob52[1][1]=1;
          ob51[2][1]=1;	ob52[1][2]=1;
          ob51[2][2]=1;	ob52[2][2]=1;

          ob61[1][1]=1;	ob62[0][2]=1;
          ob61[1][2]=1;	ob62[1][2]=1;
          ob61[2][2]=1;	ob62[1][1]=1;
          ob61[2][3]=1;	ob62[2][1]=1;

          ob71[1][1]=1;	ob72[0][2]=1;	ob73[0][2]=1;	ob74[0][2]=1;
          ob71[1][2]=1;	ob72[1][1]=1;	ob73[1][1]=1;	ob74[1][2]=1;
          ob71[1][3]=1;	ob72[1][2]=1;	ob73[1][2]=1;	ob74[1][3]=1;
          ob71[2][2]=1;	ob72[2][2]=1;	ob73[1][3]=1;	ob74[2][2]=1;
  //////////////////////////////////////////////////////////////////////////
          for (int j=0; j<2+10+2; j++){//Прорисовка нижней границы
                  el[3+20+0][j].activ = -1;
                  el[3+20+1][j].activ = -1;
          }
          for (int i=0; i<3+20+2; i++){//Прорисовка левой и правой границ
                  el[i][0].activ = -1;
                  el[i][1].activ = -1;
                  el[i][2+10+0].activ = -1;
                  el[i][2+10+1].activ = -1;
          }
  //////////////////////////////////////////////////////////////////////////

	  srand( time(0) );
	y = 0; x = 0; speed = 1000; k = 1;

	n_temp = rand()%7+1;


	temp_speed=speed;
	next = true;

	StartGame();

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(Time()));

        scoreLcd = new QLCDNumber(3);
        scoreLcd->setSegmentStyle(QLCDNumber::Filled);
        scoreLcd->move(94,223);
        scoreLcd->setFixedSize(45,45);


        levelLcd = new QLCDNumber(3);
        levelLcd->setSegmentStyle(QLCDNumber::Filled);
        levelLcd->move(94,303);
        levelLcd->setFixedSize(45,45);

        //scoreLcd->display(cur_score);
}

tetris::~tetris()
{

}

void tetris::Time()
{
        timer->start(temp_speed);//////////////////////////////////////////////////////////////////////////
        qDebug()<<temp_speed;
        scoreLcd->display(cur_score);
        levelLcd->display(cur_lvl);
           // }
      Contact();
      y++;
      StartGame();
}

void tetris::StartGame()
{


  if (next) DeleteLine();
  if (next) NewFigure();
  if (next) NextFigure();
  PaintFigure();
  PaintMatrix();
  Delimitation();
  Contact();
  if (el[2][6].activ==-1 || el[2][7].activ==-1){
          qDebug()<< "Game over";
          g_o=true;
          next = true; rs = ls = false;
          timer->stop();
  }

  RemoveTrack();

}

void tetris::NewFigure()
{
 temp_speed=1000-((cur_score*2));
 if(temp_speed<250){temp_speed=249;}
 if(cur_score>128*m){m++;cur_lvl++;}
	y = 1; x = 0; k = 1;
	temp = n_temp;
	switch(temp){
	case 1: ob0 = ob11; break;
	case 2:	ob0 = ob21; break;
	case 3:	ob0 = ob31; break;
	case 4:	ob0 = ob41; break;
	case 5:	ob0 = ob51; break;
	case 6:	ob0 = ob61; break;
	case 7:	ob0 = ob71; break;
	}
}

void tetris::RotationFigure()
{

	k++; if (k>4) k = 1;
	switch(temp){
	case 1:
		if (ls>1 && rs>0 && (k==1 || k==3)) ob0 = ob11; else if (k==1 || k==3) k--;
		if (k==2 || k==4) ob0 = ob12;
	break;
	case 2:
		ob0 = ob21;
	break;
	case 3:
		if (rs>0 && k==1) ob0 = ob31; else if (k==1) k--;
		if (k==2) ob0 = ob32;
		if (ls>0 && k==3) ob0 = ob33; else if (k==3) k--;
		if (k==4) ob0 = ob34;
	break;
	case 4:
		if (ls>0 && k==1) ob0 = ob41; else if (k==1) k--;
		if (k==2) ob0 = ob42;
		if (rs>0 && k==3) ob0 = ob43; else if (k==3) k--;
		if (k==4) ob0 = ob44;
	break;
	case 5:
		if (rs>0 && (k==1 || k==3)) ob0 = ob51; else if (k==1 || k==3) k--;
		if (k==2 || k==4) ob0 = ob52;
	break;
	case 6:
		if (rs>0 && (k==1 || k==3)) ob0 = ob61; else if (k==1 || k==3) k--;
		if (k==2 || k==4) ob0 = ob62;
	break;
	case 7:
		if (ls>0 && k==1) ob0 = ob71; else if (k==1) k--;
		if (k==2) ob0 = ob72;
		if (rs>0 && k==3) ob0 = ob73; else if (k==3) k--;
		if (k==4) ob0 = ob74;
	break;
	}
}

void tetris::PaintFigure()
{

  for (int i=0; i<4; i++)
          for(int j=0; j<4; j++)
                  if ( ob0[i][j] )
                          el[i+y-1][j+x+5].activ = 1;
}

void tetris::PaintMatrix()
{

  for (int i=3; i<3+20; i++)
          for(int j=2; j<2+10; j++)
                  if (el[i][j].activ)
                          el[i][j].paint_element(i,j,temp);
                  else
                          el[i][j].paint_element(i,j,0);
}

void tetris::Delimitation()
{

  ls = 10; rs = 10;
  for (int i=0; i<4; i++)
          for(int j=0; j<4; j++)
                  if( el[i+y-1][j+x+5].activ==1 ){
                          for(int l=1; l<j+x+5; l++)
                                  if( el[i+y-1][l].activ==-1 )
                                          if (ls>(j+x+5)-(l+1))
                                                  ls = (j+x+5)-(l+1);
                          for(int l=12; l>j+x+5; l--)
                                  if( el[i+y-1][l].activ==-1 )
                                          if (rs>(l-1)-(j+x+5))
                                                  rs = (l-1)-(j+x+5);
                  }//qDebug()<< "ls="<< ls <<" rs="<< rs;
}

void tetris::Contact()
{
  next = false;
  for (int i=0; i<4; i++)
          for(int j=0; j<4; j++)
                  if( ob0[i][j]==1 && el[i+y][j+x+5].activ==-1 ){
                          for (int i=0; i<4; i++)
                                  for(int j=0; j<4; j++)
                                          if ( el[i+y-1][j+x+5].activ==1 ){
                                                  el[i+y-1][j+x+5].activ = -1;
                                                  el[i+y-1][j+x+5].color = temp;
                                          }
                           next = true;
                  }

}

void tetris::DeleteLine()
{
  for (int i=2+20; i>0; i--)
          if (el[i][2].activ==-1 && el[i][3].activ==-1 && el[i][4].activ==-1 && el[i][5].activ==-1 && el[i][6].activ==-1 && el[i][7].activ==-1 && el[i][8].activ==-1 && el[i][9].activ==-1 && el[i][10].activ==-1 && el[i][11].activ==-1 ){
              cur_score=cur_score+20;

              for (int l=i; l>0; l--)
                          for(int j=2; j<2+10; j++){
                                  el[l][j].activ = el[l-1][j].activ;
                                  el[l][j].color = el[l-1][j].color;
                          }

          i++;
          }


}

void tetris::RemoveTrack()
{

  for (int i=0; i<4; i++)
          for(int j=0; j<4; j++)
                  if ( el[i+y-1][j+x+5].activ==1 )
                          el[i+y-1][j+x+5].activ = 0;
}

void tetris::DelTrack()
{

  for (int i=0; i<4; i++)
          for(int j=0; j<4; j++)
                  if ( ob0[i][j]==1 ){
                          el[i+y-1][j+x+5].activ = 0;
                  }
}


void tetris::NextFigure()
{
cur_score=cur_score+1;
          n_temp = rand()%7+1;
          next = false;
          switch(n_temp){
          case 1: n_ob0 = ob11; break;
          case 2:	n_ob0 = ob21; break;
          case 3:	n_ob0 = ob31; break;
          case 4:	n_ob0 = ob41; break;
          case 5:	n_ob0 = ob51; break;
          case 6:	n_ob0 = ob61; break;
          case 7:	n_ob0 = ob71; break;
          }

          for (int i=0; i<4; i++)
                  for(int j=0; j<4; j++)
                          if (n_ob0[i][j])
                                  n_el[i][j].paint_n_element(i,j,n_temp);
                          else
                                  n_el[i][j].paint_n_element(i,j,0);
}



void tetris::Bonus()
{

  int i=22;
  cur_score=cur_score+20;
  for (int l=i; l>0; l--)//poprobivat' k=i; k>0...
                          for(int j=2; j<2+10; j++){
                                  el[l][j].activ = el[l-1][j].activ;
                                  el[l][j].color = el[l-1][j].color;
                          }
          i++;



}
void tetris::StartAgain()
{
  cur_lvl=1;
  cur_score=0;

  is_start_again=true;
  for (int i=0; i<3+20; i++)
                  for(int j=2; j<2+10; j++)
                          el[i][j].activ = 0;
          next = true;
	temp_speed=speed;
	timer->start(speed);
	qDebug()<<"sped"<<speed;
	StartGame();
}
