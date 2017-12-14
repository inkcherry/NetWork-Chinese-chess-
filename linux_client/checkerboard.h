#pragma once
//#include "global.h";
#include "chess.h"
#include <iostream>




class checkerboard
{
public:
	
	checkerboard();
	~checkerboard();
	void show_chessboard();
	void reset_cur_camp() { cur_camp = !cur_camp; }
	bool select_chess(const int &x, const int &y);
	bool move_chess(const int &x, const int &y);
private:
	int chessboard[10][9]; //����
	chess *chess_board[10][9];
	void _initchessboard();
	CAMP cur_camp;		  //��ǰ���Ӫ
	chess *cur_chess;      //��ǰ�����
	void _translate_to_chess_obj(const CHESS_TYPE &chess_, const int &i, const int &j);//�����׷���ɶ���
	char* _translate_to_word(const CHESS_TYPE &chess);
};

