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
		return false;//绊马腿
	return true;
}

CAMP car::_can_move(const int&to_x, const int&to_y, chess *chess_board_[10][9])const
{	

	int from_x = position.first;
	int from_y = position.second;
	if(from_x==to_x)//横向移动
	{
		if(from_y<to_y)  //向右移动
			for(int i=from_y+1;i<to_y;i++)
			{
				if(!is_NO_CHESS(chess_board_[from_x][i]))
					return false;
			}
		else if(from_y>to_y)  //向左移动
			for(int i=from_y-1;i>to_y;i--)
			{
				if(!is_NO_CHESS(chess_board_[from_x][i]))
					return false;
			}
	}

	else if(from_y==to_y)//纵向移动
	{
		if(from_x<to_x)
			for(int i=from_x+1;i<to_x;i++)
			{
				if(!is_NO_CHESS(chess_board_[i][from_y]))
					return false;
			}
		if(from_x>to_x)
			for(int i=from_x-1;i>to_x;i--)
			{
				if(!is_NO_CHESS(chess_board_[i][from_y]))
					return false;
			}
	}
	else {return false;}  

	return true;
}


CAMP canon::_can_move(const int&to_x, const int&to_y, chess *chess_board_[10][9])const
{	
	int from_x = position.first;
	int from_y = position.second;
	//因为checkerboard会检测 to_x to_y是否有自己的棋
	if(!is_NO_CHESS(chess_board_[to_x][to_y])) //吃子模式
	{int count_chess=0;
		if(from_x==to_y)  //横向移动
		{
			if(from_y<to_y)  //向右移动
				for(int i=from_y+1;i<to_y;i++)
				{
					if(!is_NO_CHESS(chess_board_[from_x][i]))
						{if(++count_chess==2)return false;} //只能隔一个子
				}
		    else if(from_y>to_y)  //向左移动
				for(int i=from_y-1;i>from_y;i--)
				{
					if(!is_NO_CHESS(chess_board_[from_x][i]))
						{if(++count_chess==2)return false;} //只能隔一个子
				}
			if(count_chess==0)return false;//一个没隔开返回f
		}
		else if(from_y==to_y)
		{
			if(from_x<to_x)
				for(int i=from_x+1;i<to_x;i++)
				{
					if(!is_NO_CHESS(chess_board_[i][from_y]))
						{if(++count_chess==2)return false;} //只能隔一个子
				}
			if(from_x>to_x)
			{
					for(int i=from_x-1;i>to_x;i--)
					{
					if(!is_NO_CHESS(chess_board_[i][from_y]))
						{if(++count_chess==2)return false;} //只能隔一个子
					}
			}
			if(count_chess==0)return false;//一个没隔开返回f
		}
	}


	else          //移动模式 跟car基本一致 就是不能吃
	{
		if(from_x==to_x)//横向移动
		{
			if(from_y<to_y)  //向右移动
				for(int i=from_y+1;i<=to_y;i++)
				{
					if(!is_NO_CHESS(chess_board_[from_x][i]))
						return false;
				}
			else if(from_y>to_y)  //向左移动
				for(int i=from_y-1;i>=to_y;i--)
				{
					if(!is_NO_CHESS(chess_board_[from_x][i]))
						return false;
				}
			else return false;  //原地不动返回f
		}

		else if(from_y==to_y)//纵向移动
		{
			if(from_x<to_x)           // 向下
				for(int i=from_x+1;i<=to_x;i++)
				{
					if(!is_NO_CHESS(chess_board_[i][from_y]))
						return false;
				}
			if(from_x>to_x)          //向上
				for(int i=from_x-1;i>=to_x;i--)
				{
					if(!is_NO_CHESS(chess_board_[i][from_y]))
						return false;
				}
		}
		else {return false;}  
	}
	return true;
}
	
CAMP king::_can_move(const int&to_x, const int&to_y, chess *chess_board_[10][9])const
{
	int from_x = position.first;
	int from_y = position.second;
	std::pair<int,int>center=get_camp()==R_PARTY?std::make_pair(8,4):std::make_pair(1,4);
	if(abs(to_x-center.first)>1||abs(to_y-center.second)>1)   //不能出宫
	{		int op_center_x[3]={9-center.first,9-center.first+1,9-center.first-1};	//对方明将可以出宫干掉他
			
	
	       for(auto i :op_center_x)
			{
				if(!is_NO_CHESS(chess_board_[i][from_y])&&(chess_board_[i][from_y]->get_type()==R_KING||chess_board_[i][from_y]->get_type()==B_KING))
				// 跟对方的将在同一条直线上
				{ 
					if(i>from_x)
					{
						for(int j=from_x+1;j<i;j++)
						if(!is_NO_CHESS(chess_board_[j][from_y]))
							return false;   //中间有棋不算明将
					}
					else if(i<from_x)
					{
						for(int j=from_x-1;j>i;j--)
						if(!is_NO_CHESS(chess_board_[j][from_y]))//如果中间有隔开的棋子
							return false;
					}
				}
			}
			return true;
	}
		
	else
	{
		if((abs(from_x-to_x)+abs(from_y-to_y))==1)  //一格移动
			return true;
		return false;
	}														 
	return false;	
}

CAMP bishop::_can_move(const int&to_x, const int&to_y, chess *chess_board_[10][9])const
{
	int from_x = position.first;
	int from_y = position.second;
	std::pair<int,int>center=get_camp()==R_PARTY?std::make_pair(8,4):std::make_pair(1,4);
	if(abs(to_x-center.first)>1||abs(to_y-center.second)>1)return false;//不能出宫
	if(abs(to_x-from_x)==1&&abs(to_y-from_y)==1)return true;
	return false;
}

	
	
CAMP elephant::_can_move(const int&to_x, const int&to_y, chess *chess_board_[10][9])const
{
	int from_x = position.first;
	int from_y = position.second;
	std::pair<int,int>river=get_camp()==R_PARTY?std::make_pair(1,5):std::make_pair(-1,-4);   //>5   <4(>-4)
	if(to_x*river.first>=river.second)  //R:
		{
				if (abs(to_x-from_x)==2&&abs(to_y-from_y)==2)
				{
						if(is_NO_CHESS(chess_board_[(to_x+from_x)/2][(to_y+from_y)/2]))
							return true;
				}
		}
	return false;
}
CAMP pawn::_can_move(const int&to_x, const int&to_y, chess *chess_board_[10][9])const
{
	int from_x = position.first;
	int from_y = position.second;
	std::pair<int,int>cross_river=get_camp()==R_PARTY?std::make_pair(1,4):std::make_pair(-1,-5); // <4 >4(<-5)
	if(to_x*cross_river.first>from_x*cross_river.first)      //R:to>from  B:to<from--->-to>-from  不能往回走
		return false;
	
	//没过河
	if(from_x*cross_river.first>cross_river.second)  //R:from>4   B:from<5--->-from>-5  没过河只能直走
	{
		if(from_x==to_x)//不能横着走
		return false;
	}
	if(abs(to_x-from_x)+abs(to_y-from_y)!=1) //只能走一格
		return false;

	
		return true;
}	
