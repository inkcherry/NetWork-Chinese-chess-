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


//  class no_chess :public chess {          //无子 ，只提供接口
// 	 CAMP _can_move(const int&x, const int&y,  chess *chess_board_[10][9]) { return false; }
//  };


class king :public chess             //帅
{
	public:
	 king(const CAMP camp_, std::pair<int, int> position_) :chess(camp_, position_) { type = (camp == R_PARTY) ? R_KING : B_KING; };
	 CAMP _can_move(const int&x, const int&y, chess *chess_board_[10][9])const;
};
	

class horse :public chess            //马
{
 public:
	 horse(const CAMP camp_, std::pair<int, int> position_) :chess(camp_, position_) { type = (camp == R_PARTY) ? R_HORSE : B_HORSE; };
	 CAMP _can_move(const int&x, const int&y, chess *chess_board_[10][9])const;
};
	

 class car :public chess			  //车
{
	public:
		car(const CAMP camp_, std::pair<int, int> position_) :chess(camp_, position_) { type = (camp == R_PARTY) ? R_CAR : B_CAR; };
		CAMP _can_move(const int&x, const int&y, chess *chess_board_[10][9])const;
};
	

 class canon :public chess            //炮
 {
	public:
		canon(const CAMP camp_, std::pair<int, int> position_) :chess(camp_, position_) { type = (camp == R_PARTY) ? R_CANON : B_CANON; };
		CAMP _can_move(const int&x, const int&y, chess *chess_board_[10][9])const;
 };
 class bishop :public chess			  //士
 {
   public:
	 bishop(const CAMP camp_, std::pair<int, int> position_) :chess(camp_, position_) { type = (camp == R_PARTY) ? R_BISHOP : B_BISHOP; };
	 CAMP _can_move(const int&x, const int&y, chess *chess_board_[10][9])const;
 };
 class elephant :public chess            //象
 {
	public:
	 elephant(const CAMP camp_, std::pair<int, int> position_) :chess(camp_, position_) { type = (camp == R_PARTY) ? R_ELEPHANT : B_ELEPHANT; };
	 CAMP _can_move(const int&x, const int&y, chess *chess_board_[10][9])const;
 };
 class pawn :public chess             //兵
 {
	public:
	 pawn(const CAMP camp_, std::pair<int, int> position_) :chess(camp_, position_) { type = (camp == R_PARTY) ? R_PAWN : B_PAWN; };
	 CAMP _can_move(const int&x, const int&y, chess *chess_board_[10][9])const;
 };
