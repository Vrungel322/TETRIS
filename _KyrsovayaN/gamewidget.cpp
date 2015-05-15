#include "gamewidget.h"
#include "element.h"
#include "singleton.h"
#include "button.h"
#include "tetris.h"
#include "setimage.h"
#include "bonusbutton.h"
#include "records.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QTextDocument>
#include <QPicture>
#include <QImage>
#include <QLabel>
#include <QTransform>
#include <QBrush>
#include <QPushButton>

#include <QMovie>
#include <QMediaPlayer>
#include <QThread>
#include <QMouseEvent>
#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <iostream>
#include <QRegExpValidator>


 extern tetris * obj;
GameWidget::GameWidget(QWidget *parent){
  int x = 600, y =600;

  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setFixedSize(x, y);
  //resize(x,y);

  scene = new QGraphicsScene();
  scene->setSceneRect(0,0,x, y);
  sceneL = new QGraphicsScene();
  sceneL->setSceneRect(0,0,x, y);
  sceneM = new QGraphicsScene();
  sceneM->setSceneRect(0,0,x, y);
  sceneS = new QGraphicsScene();
  sceneS->setSceneRect(0,0,x, y);
  sceneG = new QGraphicsScene();
  sceneG->setSceneRect(0,0,x, y);
  sceneP = new QGraphicsScene();
  sceneP->setSceneRect(0,0,x, y);
  sceneR = new QGraphicsScene();
  sceneR->setSceneRect(0,0,x, y);
  sceneOver = new QGraphicsScene();
  sceneOver->setSceneRect(0,0,x, y);
  sceneAbout = new QGraphicsScene();
  sceneAbout->setSceneRect(0,0,x, y);

recordi=new records[10];
temp=new records;
for (int i=0; i<10; i++)
  recordi[i].read(i); //qDebug()<<recordi[i].nomer<<" "<<recordi[i].name<<" "<<recordi[i].cur_score;

Text = new QGraphicsTextItem[30];

obj = new tetris();
obj->timer->stop();

start_timer=new QTimer();
connect(start_timer,SIGNAL(timeout()),this,SLOT(Start()));

remove_start_timer=new QTimer();
connect(remove_start_timer,SIGNAL(timeout()),this,SLOT(removing_start_timer()));

update_start_timer=new QTimer();
connect(update_start_timer,SIGNAL(timeout()),this,SLOT(umenshenie_start_timer()));

for_game_over=new QTimer();
for_game_over->start(obj->temp_speed);
connect(for_game_over,SIGNAL(timeout()),this,SLOT(check_g_o()));

for_bonus=new QTimer();
connect(for_bonus,SIGNAL(timeout()),this,SLOT(bonus_active()));

for_bonus_remove=new QTimer();
bB = new bonusbutton(QString("BONUS"));
connect(bB,SIGNAL(clicked()),this,SLOT(hz()));
connect(for_bonus_remove,SIGNAL(timeout()),this,SLOT(removing_bB()));

tbon = new QGraphicsTextItem();
tbon->setPos(385,380);
tbon->setHtml("<b>Here can be</b><br> <u><i>BONUS</i></u>");
QFont tFont("comic sans ms",25);
tbon->setFont(tFont);
sceneG->addItem(tbon);


nfig = new QGraphicsTextItem();
nfig->setPos(380,45);
nfig->setHtml("<b>Next:</b><br>");
QFont nfigFont("comic sans ms",25);
nfig->setFont(nfigFont);


for_music=new QTimer();
music = new QMediaPlayer();
music->setMedia(QUrl("qrc:/new/prefix1/CoubBeretta.mp3"));


QPixmap arrow2(":/new/prefix1/Cursor2.cur");
QCursor cursor_2(arrow2);
setCursor(cursor_2);

                                                                                    //Loaging
movie1 = new QMovie( ":/new/prefix1/loading.gif" );
myLabel1=new QLabel();

                                                                                      //Menu

titleText = new QGraphicsTextItem(QString("TETRIS"));
QFont titleFont("comic sans ms",60);
titleText->setFont(titleFont);
int txPos = this->width()/2 - titleText->boundingRect().width()/2;
int tyPos = 90;
titleText->setPos(txPos,tyPos);

playButton = new button(QString("Play"));
int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
int byPos = 200;
playButton->setPos(bxPos,byPos);
connect(playButton,SIGNAL(clicked()),this,SLOT(Game()));

recordsButton = new button(QString("Records"));
int rxPos = this->width()/2 - recordsButton->boundingRect().width()/2;
int ryPos = 275;
recordsButton->setPos(rxPos,ryPos);
connect(recordsButton,SIGNAL(clicked()),this,SLOT(Records()));

about = new button(QString("About"));
int abxPos = this->width()/2 - about->boundingRect().width()/2;
int abyPos = 350;
about->setPos(abxPos,abyPos);
connect(about,SIGNAL(clicked()),this,SLOT(About()));

quitButton = new button(QString("Quit"));
int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
int qyPos = 425;
quitButton->setPos(qxPos,qyPos);
connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));

image_set = new setimage();
int im_set_xPos = 450;
int  im_set_yPos = 10;
image_set->setPos( im_set_xPos, im_set_yPos);
connect(image_set,SIGNAL(clicked()),this,SLOT(Settings()));

                                                                                          //About
from_About = new button(QString("to_Menu"));
int fraxPos = this->width()/2 - from_About->boundingRect().width()/2;
int frayPos = 425;
from_About->setPos(fraxPos,frayPos);
connect(from_About,SIGNAL(clicked()),this,SLOT(Menu()));

text_About= new QGraphicsTextItem();
text_About->setPos(0,45);
text_About->setHtml("<b>Created by Nikita Romanenko</b><br>Student of KPI,FICT,group: IK-42<br>Contacts:<br> - e-mail: nikita241296@gmail.com"
                    "<br>Resources used: <br> - pictures by Dave Morrow"
                    "<br>Music: <br> - Coub-Beretta");
QFont text_AboutFont("comic sans ms",25);
text_About->setFont(text_AboutFont);

                                                                                          //Game

int dy=100;
startButton = new button(QString("Start"));
int sxPos = 390;
int syPos = 50+dy;
startButton->setPos(sxPos,syPos);
connect(startButton,SIGNAL(clicked()),this,SLOT(Start()));

againButton = new button(QString("StartAgain"));
int agbxPos = 390;
int agbyPos = 125+dy;
againButton->setPos(agbxPos,agbyPos);
connect(againButton,SIGNAL(clicked()),this,SLOT(StartAgain()));

btn_pause = new button(QString("Pause"));
int pausexPos = 390;
int pauseyPos = 200+dy;
btn_pause->setPos(pausexPos,pauseyPos);
connect(btn_pause,SIGNAL(clicked()),this,SLOT(Pause()));

sceneG->addRect(QRect(90,300,51,50));
QBrush brush;
brush.setStyle(Qt::SolidPattern);
level=new  QGraphicsTextItem(QString("Level:"));
QFont level_text_Font("comic sans ms",20);
level->setFont(level_text_Font);
level->setPos(0,300);

sceneG->addRect(QRect(90,220,51,50));
QBrush brush1;
brush1.setStyle(Qt::SolidPattern);
score=new  QGraphicsTextItem(QString("Score:"));
QFont cur_score_text_Font("comic sans ms",20);
score->setFont(cur_score_text_Font);
score->setPos(-2,220);

back_timer=new QGraphicsTextItem();
back_timer->setHtml(" < font background-color: #369; face='Comic Sans Ms' color='red' size='16'>Start in:</font>");
back_timer->setPos(150,250);

start_in = new QLCDNumber(1);
start_in->setSegmentStyle(QLCDNumber::Filled);
start_in->move(270,244);
start_in->setFixedSize(60,60);

                                                                                    //check_g_o
endText = new QGraphicsTextItem(QString("Sorry... Game is Over"));
QFont endFont("comic sans ms",45);
endText->setFont(endFont);
endText->setPos(0,150);

againButton1 = new button(QString("StartAgain"));
againButton1->setPos(193,250);
connect(againButton1,SIGNAL(clicked()),this,SLOT(StartAgain1()));

menuButton2 = new button(QString("Menu"));
menuButton2->setPos(193,325);
connect(menuButton2,SIGNAL(clicked()),this,SLOT(Menu()));

nic = new QGraphicsTextItem(QString("Nickname:"));
QFont nicFont("comic sans ms",30);
nic->setFont(nicFont);
nic->setDefaultTextColor(Qt::white);
nic->setPos(193,0);

nic1 = new QGraphicsTextItem(QString("(do not forget to press ENTER ,and no more 7 symbols)"));
QFont nic1Font("comic sans ms",13);
nic1->setFont(nic1Font);
nic1->setDefaultTextColor(Qt::white);
nic1->setPos(70,90);

less = new QGraphicsTextItem(QString("LESS SYMBOLS"));
QFont lessFont("comic sans ms",13);
less->setFont(lessFont);
less->setDefaultTextColor(Qt::red);
less->setPos(380,57);

                                                                                    //Pause

image_set->setPos( 450, 10);
connect(image_set,SIGNAL(clicked()),this,SLOT(Settings()));

pauseText = new QGraphicsTextItem(QString("PAUSE"));
QFont pauseFont("comic sans ms",60);
pauseText->setFont(pauseFont);
pauseText->setPos(160,150);

un_pause = new button(QString("UN_PAUSE"));
un_pause->setPos(193,250);
connect(un_pause,SIGNAL(clicked()),this,SLOT(Unpause()));

menuButton1 = new button(QString("Menu"));
menuButton1->setPos(193,325);
connect(menuButton1,SIGNAL(clicked()),this,SLOT(Menu()));

                                                                                 //records

menu_from_rec = new button(QString("Back"));
int mxPos = 200;
int myPos = 470;
menu_from_rec->setPos(mxPos,myPos);
connect(menu_from_rec,SIGNAL(clicked()),this,SLOT(Menu()));

                                                                                  //setting
setingsText = new QGraphicsTextItem(QString("SETTINGS"));
QFont setingsFont("comic sans ms",60);
setingsText->setFont(setingsFont);
setingsText->setPos(80,140);

musicButton_ON = new button(QString("Music ON"));
musicButton_ON->setPos(200,250);
connect(musicButton_ON,SIGNAL(clicked()),this,SLOT(MusicONON()));

musicButton_OFF = new button(QString("Music OFF"));
musicButton_OFF->setPos(200,325);
connect(musicButton_OFF,SIGNAL(clicked()),this,SLOT(MusicOFFOFF()));

back_Button = new button(QString("Back"));
back_Button->setPos(200,400);
connect(back_Button,SIGNAL(clicked()),this,SLOT(Back()));

theme0 = new button(QString("Theme_0"));
theme0->setPos(20,40);
connect(theme0,SIGNAL(clicked()),this,SLOT(changetheme0()));

theme1 = new button(QString("Theme_1"));
theme1->setPos(20,90);
connect(theme1,SIGNAL(clicked()),this,SLOT(changetheme1()));

                                                                          //kursors

QPixmap arrow0(":/new/prefix1/Cursor0.cur");
QCursor cursor_0(arrow0);
setCursor(cursor_0);

}

GameWidget::~GameWidget(){
//	delete scene;
//	delete sceneL;
//	delete sceneM;
//	delete sceneG;
//	delete sceneP;
}

void GameWidget::bonus_active()
{
  lol=0;
  bonus_canbe_clicked=1;
  for_bonus_remove->start(3000);
  bB->setPos(390,375);
  bB->activated();
  sceneG->addItem(bB);
  sceneG->removeItem(tbon);

}

void GameWidget::removing_bB()
{
  if(lol==0){
  sceneG->removeItem(bB);
  bB->nadpis=true;
  sceneG->addItem(tbon);
  bonus_canbe_clicked=0;
    }
}

void GameWidget::hz()
{

  obj->Bonus();
  obj->PaintFigure();
  obj->PaintMatrix();
  obj->Delimitation();
  obj->Contact();
  obj->RemoveTrack();
  removing_bB();
  lol=1;
  bonus_canbe_clicked=0;
}


void GameWidget::MusicON()
{
  music->play();
  MusicONON();
}

void GameWidget::MusicONON()
{
  music->play();
  for_music->start(248500);
  connect(for_music, SIGNAL(timeout()), this, SLOT(MusicON()));

}

void GameWidget::MusicOFFOFF()
{
  music->stop();
  for_music->stop();

}

void GameWidget::changetheme1()
{
  change_theme=1;
  sceneS->setBackgroundBrush(QBrush(QImage(":/new/prefix1/setings.jpg")));
  QPixmap arrow1(":/new/prefix1/Cursor1.cur");
  QCursor cursor_1(arrow1);
  setCursor(cursor_1);
}

void GameWidget::changetheme0()
{
  change_theme=0;
  sceneS->setBackgroundBrush(QBrush(QImage(":/new/prefix1/setings0.png")));
  QPixmap arrow2(":/new/prefix1/Cursor0.cur");
  QCursor cursor_2(arrow2);
  setCursor(cursor_2);
}

                                                          //otkuda idet otschet X ?????
void GameWidget::keyPressEvent(QKeyEvent *event)
{

  switch( event->key() ){
                  case Qt::Key_Left :
                  if (obj->ls){
                          if (obj->next) obj->DelTrack();
                          obj->x--;
                          obj->PaintFigure();
                          obj->PaintMatrix();
                          obj->Delimitation();
                          obj->Contact();
                          obj->RemoveTrack();
                  }
                  break;
                  case Qt::Key_Right :
                  if (obj->rs){
                          if (obj->next) obj->DelTrack();
                          obj->x++;
                          obj->PaintFigure();
                          obj->PaintMatrix();
                          obj->Delimitation();
                          obj->Contact();
                          obj->RemoveTrack();
                  }
                  break;
                  case Qt::Key_Down :
                  if (!obj->next){
                          obj->y++;
                          obj->PaintFigure();
                          obj->PaintMatrix();
                          obj->Delimitation();
                          obj->Contact();
                          obj->RemoveTrack();
                  }
                  break;
                  case Qt::Key_Up :
                  if (!obj->next){
                          obj->RotationFigure();
                          obj->PaintFigure();
                          obj->PaintMatrix();
                          obj->Delimitation();
                          obj->Contact();
                          obj->RemoveTrack();
                  }
                  break;
                case Qt::Key_Space :
                if (!obj->next&&bonus_canbe_clicked==1){
                        obj->Bonus();
                        obj->PaintFigure();
                        obj->PaintMatrix();
                        obj->Delimitation();
                        obj->Contact();
                        obj->RemoveTrack();
                        bonus_canbe_clicked=0;
                        removing_bB();
                }
                break;
          }

}

void GameWidget::Loading()
{

//MusicON();

	LoadTimer = new QTimer(this);
	LoadTimer->start(3000);

	sceneL->setBackgroundBrush(QBrush(QImage(":/new/prefix1/loading.jpg")));

	p1 = myLabel1->palette();
	p1.setBrush(QPalette::Window,QBrush(QColor(255,255,255,0)));
	myLabel1->setAutoFillBackground(true);
	myLabel1->setPalette(p1);
	myLabel1->setMovie( movie1 );
	myLabel1->move(240,330);
	myLabel1->resize(200,200);
	myLabel1->setMovie( movie1 );
	movie1->start();
	sceneL->addWidget(myLabel1);

//	QMovie *movie = new QMovie( ":/new/prefix1/kvadratik.gif" );
//	QLabel *myLabel=new QLabel();
//	QPalette p = myLabel->palette();
//	p.setBrush(QPalette::Window,QBrush(QColor(255,255,255,0)));
//	myLabel->setAutoFillBackground(true);
//	myLabel->setPalette(p);
//	myLabel->setMovie( movie );
//	myLabel->move(200,230);
//	myLabel->resize(200,200);
//	myLabel->setMovie( movie );
//	movie->start();
//	sceneL->addWidget(myLabel);

	Display(sceneL);
	connect(LoadTimer, SIGNAL(timeout()), this, SLOT(Menu()));

}


void GameWidget::work_with_file()
{
  menuButton2->setVisible(0);
 if(edit->text().size()<7) {
     sceneOver->removeItem(less);

  bool temp = false;
          str = edit->text();
          QString t;

          for (int i=0; i<10; i++)
                  if (recordi[i].name==str){
                      if(recordi[i].score.toInt()<obj->cur_score){
                          recordi[i].score = QString::number(obj->cur_score);
                          temp = true;
                          for (int i=0; i<10; i++)
                                  for (int j=i; j<10; j++)
                                          if (recordi[i].score.toInt()<recordi[j].score.toInt()){
                                                  t = recordi[i].name;
                                                  recordi[i].name = recordi[j].name;
                                                  recordi[j].name = t;

                                                  t = recordi[i].score;
                                                  recordi[i].score = recordi[j].score;
                                                  recordi[j].score = t;
                                          }
                      }
                      temp=true;
                  }

          if (!temp)
                  for (int i=0; i<10; i++)
                          if (recordi[i].score.toInt()<obj->cur_score){
                                  for (int j=9; j>i; j--){
                                          recordi[j].name = recordi[j-1].name;
                                          recordi[j].score =recordi[j-1].score;
                                  }
                          recordi[i].name = str;
                         recordi[i].score = QString::number(obj->cur_score);
                          break;
                          }
          for (int i=0; i<10; i++){
                  qDebug()<<recordi[i].nomer;
                  qDebug()<<recordi[i].name;
                  qDebug()<<recordi[i].score;
          }

          recordi[0].Remove();
          for (int i=0; i<10; i++)
                  recordi[i].write();

          edit->close();
          menuButton2->setVisible(1);

  }
 else {menuButton2->setVisible(0);sceneOver->addItem(less); edit->clear();edit->close();check_g_o(); }
}

void GameWidget::Menu()
{


                                            QPoint mouse_position = this->mapFromGlobal(QCursor::pos());
                                             qDebug()<<"rx:"<<mouse_position.rx();
  into_menu=1;
  //obj->g_o=false;
  for_game_over->stop();

	LoadTimer->stop();

	if(change_theme==0){
	sceneM->setBackgroundBrush(QBrush(QImage(":/new/prefix1/menu0.png")));
	  }
	if(change_theme==1){
	sceneM->setBackgroundBrush(QBrush(QImage(":/new/prefix1/menu.jpg")));
	  }

        sceneM->addItem(titleText);

	sceneM->addItem(playButton);

	sceneM->addItem(recordsButton);

	sceneM->addItem(about);

	sceneM->addItem(quitButton);

	sceneM->addItem(image_set);


	Display(sceneM);
}

void GameWidget::About()
{
  sceneAbout->setBackgroundBrush(QBrush(QImage(":/new/prefix1/About2.jpg")));

  sceneAbout->addItem(from_About);

  sceneAbout->addItem(text_About);
  Display(sceneAbout);
}


void GameWidget::Game()
{
  into_menu=0;

  if(obj->g_o){
      update_start_timer->start(1001);
      start_timer->start(4000);
      remove_start_timer->start(4001);
      StartAgain1();

    };
  is_paused=0;
  pp=4;

  update_start_timer->start(1001);
  start_timer->start(4000);
  remove_start_timer->start(4001);

  if(change_theme==0){
  sceneG->setBackgroundBrush(QBrush(QImage(":/new/prefix1/game0.png")));
    }
  if(change_theme==1){
  sceneG->setBackgroundBrush(QBrush(QImage(":/new/prefix1/game.jpg")));
    }


	//sceneG->addItem(startButton);

	sceneG->addItem(againButton);

	sceneG->addItem(btn_pause);

        sceneG->addItem(level);

        sceneG->addWidget(obj->levelLcd);

        sceneG->addItem(score);

        sceneG->addWidget(obj->scoreLcd);

        sceneG->addItem(back_timer);

        sceneG->addWidget(start_in);


	Display(sceneG);
}

void GameWidget::Start()
{
  start_timer->stop();
  remove_start_timer->stop();
  update_start_timer->stop();
  for_game_over->start(obj->temp_speed);

	obj->timer->start(obj->speed);
	for_bonus->start(22000);

	sceneG->addItem(nfig);

	for (int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			sceneG->addItem(&obj->n_el[i][j]);

	Display(sceneG);

}


void GameWidget::StartAgain()
{
  obj->timer->start(obj->speed);
  for_bonus->start(15000);
  obj->cur_lvl=1;
  obj->cur_score=0;
  obj->StartAgain();
  for_game_over->start(obj->temp_speed);
}

void GameWidget::StartAgain1()
{
  sceneOver->removeItem(less);
  edit->close();
  obj->g_o=false;
  Display(sceneG);
  obj->timer->start(obj->speed);
  for_bonus->start(15000);
  obj->cur_lvl=0;
  obj->cur_score=0;
  obj->StartAgain();
  for_game_over->start(obj->temp_speed);

}

void GameWidget::check_g_o()
{
  if(obj->g_o){
 // obj->timer->stop();

  if(change_theme==0){
  sceneOver->setBackgroundBrush(QBrush(QImage(":/new/prefix1/pause0.png")));
    }
  if(change_theme==1){
  sceneOver->setBackgroundBrush(QBrush(QImage(":/new/prefix1/pause.jpg")));
    }

  for_game_over->stop();



  edit = new QLineEdit(this);
  edit->move(230,65);
  edit->setFocus();
  edit->show();
  connect(edit, SIGNAL(returnPressed()), this, SLOT(work_with_file()));


  sceneOver->addItem(endText);

  sceneOver->addItem(nic);

  sceneOver->addItem(nic1);

  sceneOver->addItem(againButton1);

  sceneOver->addItem(menuButton2);
  menuButton2->setVisible(0);



  Display(sceneOver);


    }
}

void GameWidget::Back()
{
  if(is_paused==1)
    {

      if(change_theme==0){
      sceneP->setBackgroundBrush(QBrush(QImage(":/new/prefix1/pause0.png")));
        }
      if(change_theme==1){
      sceneP->setBackgroundBrush(QBrush(QImage(":/new/prefix1/pause.jpg")));
        }
      Display(sceneP);
    }
  if(is_paused==0||is_paused==1&&into_menu==1){

      if(change_theme==0){
      sceneM->setBackgroundBrush(QBrush(QImage(":/new/prefix1/menu0.png")));
        }
      if(change_theme==1){
      sceneM->setBackgroundBrush(QBrush(QImage(":/new/prefix1/menu.jpg")));
        }
      Display(sceneM);
    }
}

void GameWidget::removing_start_timer()
{
  sceneG->removeItem(back_timer);
  start_in->destroyed();

  for (int i=3;i<3+20;i++)
          for(int j=2;j<2+10;j++)
            sceneG->addItem(&obj->el[i][j]);
}

void GameWidget::umenshenie_start_timer()
{
  pp=pp-1;
  start_in->display(pp);
}

void GameWidget::Pause()
{

  is_paused++;

  obj->timer->stop();
  for_bonus_remove->stop();
  for_bonus->stop();

  if(change_theme==0){
  sceneP->setBackgroundBrush(QBrush(QImage(":/new/prefix1/pause0.png")));
    }
  if(change_theme==1){
  sceneP->setBackgroundBrush(QBrush(QImage(":/new/prefix1/pause.jpg")));
    }

  sceneP->addItem(image_set);

  sceneP->addItem(pauseText);

  sceneP->addItem(un_pause);

  sceneP->addItem(menuButton1);

  Display(sceneP);


}

void GameWidget::Unpause()
{
  obj->timer->start(obj->temp_speed);
  for_bonus_remove->start(3000);
  for_game_over->start(obj->temp_speed);
  for_bonus->start(22000);
  is_paused=0;

  if(change_theme==0){
  sceneG->setBackgroundBrush(QBrush(QImage(":/new/prefix1/game0.png")));
    }
  if(change_theme==1){
  sceneG->setBackgroundBrush(QBrush(QImage(":/new/prefix1/game.jpg")));
    }

  Display(sceneG);

}

void GameWidget::Records()
{
  //connect(edit, SIGNAL(returnPressed()), this, SLOT());

  into_menu=0;

  if(change_theme==0){
  sceneR->setBackgroundBrush(QBrush(QImage(":/new/prefix1/records0.png")));
    }
  if(change_theme==1){
  sceneR->setBackgroundBrush(QBrush(QImage(":/new/prefix1/records.jpg")));
    }

  QFont Font("comic sans ms",36);
 // recordi[5].name="aaaaa";
  for (int i=0, j=0; j<10; i=i+3, j++){

      Text[i].setFont(Font);
      Text[i].setHtml(QString(recordi[j].nomer));
      Text[i].setPos(10,40*j);
      Text[i].setDefaultTextColor(Qt::white);
      sceneR->addItem(&Text[i]);

      Text[i+1].setFont(Font);
      Text[i+1].setHtml(QString(recordi[j].name));
      Text[i+1].setPos(150,40*j);
      Text[i+1].setDefaultTextColor(Qt::white);
      sceneR->addItem(&Text[i+1]);

      Text[i+2].setFont(Font);
      Text[i+2].setHtml(QString(recordi[j].score));
      Text[i+2].setPos(400,40*j);
      Text[i+2].setDefaultTextColor(Qt::white);
      sceneR->addItem(&Text[i+2]);
  }

        sceneR->addItem(menu_from_rec);

	Display(sceneR);
}

void GameWidget::Settings()
{

  Display(sceneS);
  if(change_theme==0){
      sceneS->setBackgroundBrush(QBrush(QImage(":/new/prefix1/setings0.png")));
        }
      if(change_theme==1){
      sceneS->setBackgroundBrush(QBrush(QImage(":/new/prefix1/setings.jpg")));
        }


     sceneS->addItem(setingsText);

     sceneS->addItem(musicButton_ON);

     sceneS->addItem(musicButton_OFF);

     sceneS->addItem(back_Button);

     sceneS->addItem(theme0);

     sceneS->addItem(theme1);

//  if(is_paused==0){

//      connect(menuButton,SIGNAL(clicked()),this,SLOT(Menu()));
//    }
//  if(is_paused==1){

//      connect(menuButton,SIGNAL(clicked()),this,SLOT(Game()));
//    }
}



void GameWidget::Display(QGraphicsScene* scene0)
{
  scene = scene0;
  setScene(scene);

}
