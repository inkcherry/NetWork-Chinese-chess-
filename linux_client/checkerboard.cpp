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
	std::cout << "  ";
	for (int i = 0; i < 9; i++)
		std::cout << i<<" ";
	std::cout<<std::endl;


	for (int i = 0; i < 10; i++)
	{
		std::cout << i<<" ";
		for (int j = 0; j < 9; j++)
			std::wcout << _translate_to_word((CHESS_TYPE)chessboard[i][j]);
		std::cout <<" "<<i<< std::endl;
		
	}
	std::cout << "  ";
	for (int i = 0; i < 9; i++)
		std::cout << i << " ";
	std::cout << std::endl;

}

void checkerboard::_translate_to_chess_obj(const CHESS_TYPE &chess_,const int &i,const int &j)  //д��������ǻ���һ���ǿ��Ը���
{
	switch (chess_)
	{
	case R_KING:
		chess_board[i][j] = nullptr;
	    break;
	case R_CAR:
		chess_board[i][j] = nullptr;
		break;
	case R_HORSE:
		chess_board[i][j] = new horse(R_PARTY, std::make_pair(i, j));
		break;
	case R_CANON:
		chess_board[i][j] = nullptr;
		break;
	case R_BISHOP:
		chess_board[i][j] = nullptr;
		break;
	case R_ELEPHANT:
		chess_board[i][j] = nullptr;
		break;
	case R_PAWN:
		chess_board[i][j] = nullptr;
		break;
	case B_KING:
		chess_board[i][j] = nullptr;
		break;
	case B_CAR:
		chess_board[i][j] = nullptr;
		break;
	case B_HORSE:
		chess_board[i][j] = new horse(B_PARTY, std::make_pair(i, j));
		break;
	case B_CANON:
		chess_board[i][j] = nullptr;
		break;
	case B_BISHOP:
		chess_board[i][j] = nullptr;
		break;
	case B_ELEPHANT:
		chess_board[i][j] = nullptr;
		break;
	case B_PAWN:
		chess_board[i][j] = nullptr;
		break;
	case NO_CHESS:
		chess_board[i][j] = nullptr;
		break;
	default:
		break;
	}
}
char* checkerboard::_translate_to_word(const CHESS_TYPE &chess){
	switch (chess)		
	{
	case R_KING:
		return "˧";
		break;
	case R_CAR:
		return "��";
		break;
	case R_HORSE:
		return "��";
		break;
	case R_CANON:
		return "��";
		break;
	case R_BISHOP:
		return "ʿ";
		break;
	case R_ELEPHANT:
		return "��";
		break;
	case R_PAWN:
		return "��";
		break;
	case B_KING:
		return "��";
		break;
	case B_CAR:
		return "܇";
		break;
	case B_HORSE:
		return "�R";
		break;
	case B_CANON:
		return "��";
		break;
	case B_BISHOP:
		return "��";
		break;
	case B_ELEPHANT:
		return "��";
		break;
	case B_PAWN:
		return "��";
		break;
	case NO_CHESS:
		return "��";
		break;
	default:
		break;
	}
	/*return "��";*/
}
bool checkerboard::select_chess(const int &x, const int &y)  //x����10   y��9
{
	if (x < 0 || x>9 || y < 0 || y>10)   //test
	{
		std::cout << "ѡ��ʧ����ѡ"; return false;
	}

	chess* target_chess = chess_board[x][y];  //ѡ��Ŀ������
	if ((!is_NO_CHESS(target_chess)&&target_chess->get_camp() != cur_camp)|| is_NO_CHESS(target_chess))   //���ǵ�ǰ��ɫִ�� ����û������
	{
		std::cout << "���ǵ�ǰ��ɫִ������û�����ӳ�ѡ"<<std::endl; return false;
	}
	cur_chess = target_chess;
	return true;
}
bool checkerboard::move_chess(const int &x, const int &y)
{
	chess* target_pos = chess_board[x][y];   //ѡ��Ŀ��λ��

	if (!is_NO_CHESS(target_pos)&&target_pos->get_camp() ==cur_camp) //Ŀ��λ�����Լ�������
	{
		std::cout << "�������Լ�������"<<std::endl; return false;
	}
	if (!(cur_chess->_can_move(x, y,chess_board)))
	{
		std::cout << "�������ƶ��淶"<<std::endl; return false;
	}

	//�ƶ��ɹ�
	if (!is_NO_CHESS(target_pos))//�����������
		delete target_pos;//������
	//int��������
	chessboard[cur_chess->get_position().first][cur_chess->get_position().second] = NO_CHESS;//����
	chessboard[x][y] = cur_chess->get_type();

	reset_cur_camp(); //�������Ӫ

	return true;
}