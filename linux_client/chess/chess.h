#pragma once
#include <iostream>
#include "global.h"
class checkerboard;

 class chess
{
public:
	
	chess(const CAMP camp_, std::pair<int, int> position_) :camp(camp_), position(position_) {};  //坐标阵营
	virtual ~chess();
	std::pair<int, int> get_position()const {return position;};
	CHESS_TYPE get_type()const { return type; };
	CAMP get_camp()const { return camp; }
	void set_pos(const int &x, const int &y) { position.first = x, position.second = y; }
	virtual CAMP _can_move (const int&x,const int&y, chess *chess_board_[10][9])const=0;         //检测能否移动到相应位置,只检测 不写入
public:
	CAMP camp;							  //阵营
	CHESS_TYPE type;					  //兵种
	std::pair<int,int> position;
};


 class no_chess :public chess {          //无子 ，只提供接口
	 CAMP _can_move(const int&x, const int&y,  chess *chess_board_[10][9]) { return false; }
 };


 class king :public chess             //帅
{
	 
};
 class horse :public chess            //马
 {
 public:
	 horse(const CAMP camp_, std::pair<int, int> position_) :chess(camp_, position_) { type = (camp == R_PARTY) ? R_HORSE : B_HORSE; };
	 CAMP _can_move(const int&x, const int&y, chess *chess_board_[10][9])const;
 };
 class car :public chess			  //车
 {

 };
 class canon :public chess            //炮
 {

 };
 class bishop :public chess			  //士
 {

 };
 class elephant :public chess            //象
 {

 };
 class pawn :public chess             //兵
 {

 };
