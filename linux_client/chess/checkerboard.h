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
	int chessboard[10][9]; //棋盘
	chess *chess_board[10][9];
	void _initchessboard();
	CAMP cur_camp;		  //当前活动阵营
	chess *cur_chess;      //当前活动棋子
	void _translate_to_chess_obj(const CHESS_TYPE &chess_, const int &i, const int &j);//将棋谱翻译成对象
	const std::string _translate_to_word(const CHESS_TYPE &chess);
};

