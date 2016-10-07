#ifndef __FIB2584AI_H__
#define __FIB2584AI_H__

#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>
#include "Fib2584/MoveDirection.h"
#include "Fib2584/GameBoard.h"

class Fib2584Ai
{
public:
	Fib2584Ai();
	// initialize ai
	void initialize(int argc, char* argv[]);
	// generate one move
	MoveDirection generateMove(const int board[4][4]);
	// do some action when game over
	void gameOver(int board[4][4], int iScore);

	/**********************************
	You can implement any additional functions
	or define any variables you may need.
	**********************************/

private:
	static bool _inited;
};

#endif