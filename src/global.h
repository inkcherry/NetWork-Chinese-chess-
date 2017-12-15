#pragma once
#define R_START 1;
//#define R_END 7;
enum { R_END = 7 };

#define B_START 8;
#define B_END 14;

//    帅			车           马         炮         士			象				兵
enum CHESS_TYPE {
	R_KING = 1, R_CAR = 2, R_HORSE = 3, R_CANON = 4, R_BISHOP = 5, R_ELEPHANT = 6, R_PAWN = 7,  //红方阵营
	B_KING = 8, B_CAR = 9, B_HORSE = 10, B_CANON = 11, B_BISHOP = 12, B_ELEPHANT = 13, B_PAWN = 14,//黑方阵营
	NO_CHESS = 0																				  //无子
};  

typedef bool CAMP;
const CAMP R_PARTY = 0;     //红方为0
const CAMP B_PARTY = 1;   //黑方为1
//#ifndef _CAMP_
//#define _CAMP_
//
//
//
//#endif // !1

CAMP get_camp(CHESS_TYPE &chess_);

const int  INITAL_CHESSBOARD[10][9] = {
	{ B_CAR,    B_HORSE,  B_ELEPHANT,  B_BISHOP,  B_KING,   B_BISHOP,  B_ELEPHANT,  B_HORSE,  B_CAR },
	{ NO_CHESS, NO_CHESS, NO_CHESS,    NO_CHESS,  NO_CHESS, NO_CHESS,  NO_CHESS,    NO_CHESS, NO_CHESS },
	{ NO_CHESS, B_CANON,  NO_CHESS,    NO_CHESS,  NO_CHESS, NO_CHESS,  NO_CHESS,    B_CANON,  NO_CHESS },
	{ B_PAWN,   NO_CHESS, B_PAWN,      NO_CHESS,  B_PAWN,   NO_CHESS,  B_PAWN,      NO_CHESS, B_PAWN },
	{ NO_CHESS, NO_CHESS, NO_CHESS,    NO_CHESS,  NO_CHESS, NO_CHESS,  NO_CHESS,    NO_CHESS, NO_CHESS },

	{ NO_CHESS, NO_CHESS, NO_CHESS,    NO_CHESS,  NO_CHESS, NO_CHESS,  NO_CHESS,    NO_CHESS, NO_CHESS },
	{ R_PAWN,   NO_CHESS, R_PAWN,      NO_CHESS,  R_PAWN,   NO_CHESS,  R_PAWN,      NO_CHESS, R_PAWN },
	{ NO_CHESS, R_CANON,  NO_CHESS,    NO_CHESS,  NO_CHESS, NO_CHESS,  NO_CHESS,    R_CANON,  NO_CHESS },
	{ NO_CHESS, NO_CHESS, NO_CHESS,    NO_CHESS,  NO_CHESS, NO_CHESS,  NO_CHESS,    NO_CHESS, NO_CHESS },
	{ R_CAR,    R_HORSE,  R_ELEPHANT,  R_BISHOP,  R_KING,   R_BISHOP,  R_ELEPHANT,  R_HORSE,  R_CAR }
};

class chess;
bool is_NO_CHESS(chess * chess_);
bool is_NO_CHESS(const chess * chess_);