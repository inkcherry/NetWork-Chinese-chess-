#include "chess.h"
chess::~chess()
{
}
CAMP horse::_can_move(const int&to_x, const int&to_y, chess *chess_board_[10][9])const
{  
	int from_x = position.first;
	int from_y = position.second;
	if (!((abs(to_y - from_y) == 1 && abs(to_x - from_x) == 2)
		|| (abs(to_y - from_y) == 2 && abs(to_x - from_x) == 1)))
		return false;

	int i, j;
	if (to_y - from_y == 2)
	{
		i = from_x;
		j = from_y + 1;
	}
	else if (from_y - to_y == 2)
	{
		i = from_x;
		j = from_y - 1;
	}
	else if (to_x - from_x == 2)
	{
		i = from_x + 1;
		j = from_y;
	}
	else if (from_x - to_x == 2)
	{
		i = from_x - 1;
		j = from_y;
	}
	if (!is_NO_CHESS(chess_board_[i][j]))
		return false;//∞Ì¬ÌÕ»
}
