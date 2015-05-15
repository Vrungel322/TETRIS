#ifndef TETRIS_H
#define TETRIS_H

#include <QWidget>
#include <QKeyEvent>
#include "element.h"
#include <QLCDNumber>

class tetris : public QWidget
{
        Q_OBJECT

public:
        explicit tetris(QWidget *parent = 0);


        element** el, **n_el;
        int a=0;
        int temp_speed;
        bool is_start_again=false;
        int speed, k, temp, del, n;
        int x, y, ls, rs, n_temp;
        bool next, up;
        int m=1;
        bool g_o=false;

	int cur_lvl=1;
	int cur_score=0;	
	QLCDNumber *scoreLcd;
	 QLCDNumber *levelLcd;

	int **ob0, **n_ob0;
	int **ob11, **ob12;
	int **ob21;
	int **ob31, **ob32, **ob33, **ob34;
	int **ob41, **ob42, **ob43, **ob44;
	int **ob51, **ob52;
	int **ob61, **ob62;
	int **ob71, **ob72, **ob73, **ob74;

	QTimer *timer;
		void StartGame();
		void StartAgain();
		void NewFigure();
		void RotationFigure();
		void PaintFigure();
		void PaintMatrix();
		void Delimitation();
		void Contact();
		void DeleteLine();
		void RemoveTrack();
		void DelTrack();//new
		void NextFigure();

	~tetris();

signals:

public slots:
	void Time();
	void Bonus();
};

#endif // TETRIS_H
