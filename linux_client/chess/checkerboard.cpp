#include "checkerboard.h"
#include <cstring>
class chess;
class horse;
checkerboard::checkerboard()
{
	cur_camp = R_PARTY;
	_initchessboard();
}

CAMP get_camp(CHESS_TYPE &chess_){ return (chess_ <= R_END) ? R_PARTY : B_PARTY; }


checkerboard::~checkerboard()
{
	
}

void  checkerboard::_initchessboard()  //
{
	for(int i=0;i<10;i++)
		for (int j = 0; j < 10; j++)
		{
			chessboard[i][j] = INITAL_CHESSBOARD[i][j];
		}
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{	
			_translate_to_chess_obj((CHESS_TYPE)INITAL_CHESSBOARD[i][j], i, j);
		}
	}
}

void  checkerboard::show_chessboard()
{
	std::cout <<"\n\r"<< "  ";
	for (int i = 0; i < 9; i++)
		std::cout << i<<" ";
	std::cout<<"\n\r";


	for (int i = 0; i < 10; i++)
	{
		std::cout<<"\n\r" << i<<" ";
		for (int j = 0; j < 9; j++)
			std::cout << _translate_to_word((CHESS_TYPE)chessboard[i][j]);
		std::cout <<" "<<i;
		
	}
	std::cout <<"\n\r"<< "  ";
	for (int i = 0; i < 9; i++)
		std::cout << i << " ";
	std::cout << "\n\r";

}

void checkerboard::_translate_to_chess_obj(const CHESS_TYPE &chess_,const int &i,const int &j)  //写这个东西是还有一点是可以复盘
{
	switch (chess_)
	{
	case R_KING:
		chess_board[i][j] = new king(R_PARTY, std::make_pair(i, j));
	    break;
	case R_CAR:
		chess_board[i][j] = new car(R_PARTY, std::make_pair(i, j));
		break;
	case R_HORSE:
		chess_board[i][j] = new horse(R_PARTY, std::make_pair(i, j));
		break;
	case R_CANON:
		chess_board[i][j] = new canon(R_PARTY, std::make_pair(i, j));
		break;
	case R_BISHOP:
		chess_board[i][j] = new bishop(R_PARTY, std::make_pair(i, j));
		break;
	case R_ELEPHANT:
		chess_board[i][j] = new elephant(R_PARTY, std::make_pair(i, j));
		break;
	case R_PAWN:
		chess_board[i][j] = new pawn(R_PARTY, std::make_pair(i, j));
		break;

		
	case B_KING:
		chess_board[i][j] = new king(B_PARTY, std::make_pair(i, j));
		break;
	case B_CAR:
		chess_board[i][j] = new car(B_PARTY, std::make_pair(i, j));
		break;
	case B_HORSE:
		chess_board[i][j] = new horse(B_PARTY, std::make_pair(i, j));
		break;
	case B_CANON:
		chess_board[i][j] = new canon(B_PARTY, std::make_pair(i, j));
		break;
	case B_BISHOP:
		chess_board[i][j] = new bishop(B_PARTY, std::make_pair(i, j));
		break;
	case B_ELEPHANT:
		chess_board[i][j] =new elephant(B_PARTY, std::make_pair(i, j));
		break;
	case B_PAWN:
		chess_board[i][j] = new pawn(B_PARTY, std::make_pair(i, j));
		break;
	case NO_CHESS:
		chess_board[i][j] = nullptr;
		break;
	default:
		break;
	}
}
const std::string  checkerboard::_translate_to_word(const CHESS_TYPE &chess){
	switch (chess)		
	{
	case R_KING:
		return "帅";
		break;
	case R_CAR:
		return "车";
		break;
	case R_HORSE:
		return "马";
		break;
	case R_CANON:
		return "炮";
		break;
	case R_BISHOP:
		return "士";
		break;
	case R_ELEPHANT:
		return "象";
		break;
	case R_PAWN:
		return "兵";
		break;
	case B_KING:
		return "將";
		break;
	case B_CAR:
		return "車";
		break;
	case B_HORSE:
		return "馬";
		break;
	case B_CANON:
		return "皰";
		break;
	case B_BISHOP:
		return "仕";
		break;
	case B_ELEPHANT:
		return "相";
		break;
	case B_PAWN:
		return "卒";
		break;
	case NO_CHESS:
		return "口";
		break;
	default:
		break;
	}
	/*return "呵";*/
}
bool checkerboard::select_chess(const int &x, const int &y)  //x是列10   y是9
{
	if (x < 0 || x>9 || y < 0 || y>10)   //test
	{
		std::cout << "选择失败重选"; return false;
	}

	chess* target_chess = chess_board[x][y];  //选择目的棋子
	if ((!is_NO_CHESS(target_chess)&&target_chess->get_camp() != cur_camp)|| is_NO_CHESS(target_chess))   //不是当前颜色执步 或者没有棋子
	{
		std::cout << "不是当前颜色执步或者没有棋子冲选"<<std::endl; return false;
	}
	cur_chess = target_chess;
	return true;
}
bool checkerboard::move_chess(const int &x, const int &y)
{
	chess* target_pos = chess_board[x][y];   //选择目的位置

	if (!is_NO_CHESS(target_pos)&&target_pos->get_camp() ==cur_camp) //目标位置有自己的棋子
	{
		std::cout << "那里有自己的棋子"<<std::endl; return false;
	}
	if (!(cur_chess->_can_move(x, y,chess_board)))
	{
		std::cout << "不符合移动规范"<<std::endl; return false;
	}
	//移动成功
	if (!is_NO_CHESS(target_pos))//如果那里有棋
		delete target_pos;//析构掉
	//真实矩阵
	
	chess_board[x][y]=chess_board[cur_chess->get_position().first][cur_chess->get_position().second];
	chess_board[cur_chess->get_position().first][cur_chess->get_position().second] = nullptr;
	//int辅助矩阵
	chessboard[cur_chess->get_position().first][cur_chess->get_position().second] = NO_CHESS;//移走
	chessboard[x][y] = cur_chess->get_type();
	//定义该对象position
	cur_chess->set_pos(x,y);

	reset_cur_camp(); //交换活动阵营

	return true;
}