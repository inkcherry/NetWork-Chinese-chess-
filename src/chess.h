#pragma once
#include <iostream>
#include "global.h"
class checkerboard;

 class chess
{
public:
	
	chess(const CAMP camp_, std::pair<int, int> position_) :camp(camp_), position(position_) {};  //������Ӫ
	~chess();
	std::pair<int, int> get_position()const {return position;};
	CHESS_TYPE get_type()const { return type; };
	CAMP get_camp()const { return camp; }
	void set_pos(const int &x, const int &y) { position.first = x, position.second = y; }
	virtual CAMP _can_move (const int&x,const int&y, chess *chess_board_[10][9])const=0;         //����ܷ��ƶ�����Ӧλ��,ֻ��� ��д��
public:
	CAMP camp;							  //��Ӫ
	CHESS_TYPE type;					  //����
	std::pair<int,int> position;
};


 class no_chess :public chess {          //���� ��ֻ�ṩ�ӿ�
	 CAMP _can_move(const int&x, const int&y,  chess *chess_board_[10][9]) { return false; }
 };


 class king :public chess             //˧
{
	 
};
 class horse :public chess            //��
 {
 public:
	 horse(const CAMP camp_, std::pair<int, int> position_) :chess(camp_, position_) { type = (camp == R_PARTY) ? R_HORSE : B_HORSE; };
	 CAMP _can_move(const int&x, const int&y, chess *chess_board_[10][9])const;
 };
 class car :public chess			  //��
 {

 };
 class canon :public chess            //��
 {

 };
 class bishop :public chess			  //ʿ
 {

 };
 class elephant :public chess            //��
 {

 };
 class pawn :public chess             //��
 {

 };
