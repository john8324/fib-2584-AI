#ifndef __MYBOARD_H__
#define __MYBOARD_H__

#include <cstring>
#include "Fib2584/MoveDirection.h"

struct MyBoard{
	int board[4][4];
	MyBoard() {memset(board, 0, sizeof(int) << 4);}
	MyBoard(const int other[4][4]) {memcpy(board, other, sizeof(int) << 4);}
	MyBoard(const MyBoard &other) {*this = other;}
};

#endif