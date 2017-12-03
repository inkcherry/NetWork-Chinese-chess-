#include "global.h"
bool is_NO_CHESS(chess * chess_)
{
	return chess_ == nullptr ? true:false;
}
bool is_NO_CHESS(const chess * chess_)
{
	return chess_ == nullptr ? true : false;
}