#include "global.h"
#include "checkerboard.h"
#include <iostream>
int main()
{
	checkerboard *m = new checkerboard();
	m->show_chessboard();
	int x, y;
	while (true)
	{
		std::cout << "ѡ��"<<std::endl;
		std::cin >> x >> y;
		if (m->select_chess(x, y)) //ѡ��ɹ�
		{
			std::cout << "�ƶ�" <<std::endl;
			std::cin >> x >> y;
			if (m->move_chess(x, y))
				m->show_chessboard();
		}

	}


	std::cin.get();
	return 0;

}