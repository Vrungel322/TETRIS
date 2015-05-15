#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QMediaPlayer>
#include "tetris.h"
#include "button.h"
#include "bonusbutton.h"
#include "setimage.h"
#include "records.h"
#include <QLCDNumber>
#include <QLabel>
#include <QPixmap>
#include <QLineEdit>
class GameWidget : public QGraphicsView
{
    Q_OBJECT

  QString str;
  QLineEdit* edit;

        QTimer *LoadTimer;
        QTimer *for_music;
        QTimer *for_lvl;
        QTimer *for_score;
        QTimer *for_bonus;
        QTimer *for_bonus_remove;
        QTimer *for_game_over;
        QTimer *start_timer;
        QTimer *remove_start_timer;
        QTimer *update_start_timer;

        //QLCDNumber *levelLcd;
        //QLCDNumber *scoreLcd;        
        QLCDNumber *start_in;

        bonusbutton* bB;

        QGraphicsTextItem* level;
        QGraphicsTextItem* next_figure;
        QGraphicsTextItem* score;
        QGraphicsTextItem* tbon;
        QGraphicsTextItem* nfig;
        QGraphicsTextItem* back_timer;

        QMediaPlayer * music;

	tetris* obj;

	int is_paused=0;
	int change_theme=0;	
	int bilo=0;
	int lol=0;
	int bonus_canbe_clicked;
	int into_menu=1;
	int pp=4;

					//Loading
	QMovie *movie1;
	QLabel *myLabel1;
	QPalette p1;
					//Menu
	QGraphicsTextItem* titleText;
	QGraphicsTextItem* Text;
	button* playButton;
	button* recordsButton;
	button* quitButton;
	button* about;
	setimage* image_set;
					//About
	button* from_About;
	QGraphicsTextItem* text_About;
					//Game
	button* startButton;
	button* againButton;
	button* btn_pause;

					//g_o
	QGraphicsTextItem* endText;
	QGraphicsTextItem* nic;
	QGraphicsTextItem* nic1;
	QGraphicsTextItem* less;
	button* againButton1;
	button* menuButton2;

					//Pause
	QGraphicsTextItem* pauseText;
	button* un_pause;
	button* menuButton1;

					//Records
	button* menu_from_rec;
	records* recordi;
	records* temp;

					//Settings
	QGraphicsTextItem* setingsText;
	button* musicButton_ON;
	button* musicButton_OFF;
	button* theme0;
	button* theme1;
	button* back_Button;

				    //kursors

public slots:
	void bonus_active();
	void removing_bB();
	void hz();
	//void Menu1(QKeyEvent *bukv);
	void Menu();
	void About();
	void work_with_file();
	void Game();
	void Start();
	void Pause();
	void Unpause();
	void Records();
	void Settings();
	void MusicON();
	void MusicONON();
	void MusicOFFOFF();
	void changetheme1();
	void changetheme0();	
	void StartAgain();
	void StartAgain1();
	//void lvl_up();
	//void score_up();
	void check_g_o();
	void Back();
	void removing_start_timer();
	void umenshenie_start_timer();
	void Display(QGraphicsScene*);
public:
	GameWidget(QWidget *parent = NULL);

	void Loading();

	QGraphicsScene* scene;
	QGraphicsScene* sceneL;
	QGraphicsScene* sceneM;
	QGraphicsScene* sceneS;
	QGraphicsScene* sceneG;
	QGraphicsScene* sceneP;
	QGraphicsScene* sceneR;
	QGraphicsScene* sceneOver;
	QGraphicsScene* sceneAbout;
	void keyPressEvent(QKeyEvent * event);


    ~GameWidget();
};

#endif // GAMEWIDGET_H


