#include "Fib2584Ai.h"

bool Fib2584Ai::_inited = false;

Fib2584Ai::Fib2584Ai()
{
}

void Fib2584Ai::initialize(int argc, char* argv[])
{
	if (_inited) return;
	srand(time(NULL));
	_inited = true;
}


MoveDirection Fib2584Ai::generateMove(int board[4][4])
{
	MoveDirection randomMove = static_cast<MoveDirection>(rand() % 4);
	return randomMove;
}

void Fib2584Ai::gameOver(int board[4][4], int iScore)
{
	return;
}

/**********************************
You can implement any additional functions
you may need.
**********************************/
