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

MoveDirection Fib2584Ai::generateMove(const int board[4][4])
{
	MyBoard after[] = {board, board, board, board};
	int max_dir = -1;
	double max_score = -1e300;
	for (int i = 0; i < 4; i++) {
		if (after[i].move(static_cast<MoveDirection>(i))) {
			double score = 1 + td.eval(Feature(after[i])); // assume r = 1
			max_score = score > max_score ? score : max_score;
		}
	}
	max_dir = max_dir == -1 ? rand() % 4 : max_dir;
	td.pushAfterState(after[max_dir]);
	return static_cast<MoveDirection>(max_dir);
}

void Fib2584Ai::gameOver(int board[4][4], int iScore)
{
	//printf("%d\n", iScore);
	td.updateWeight();
}

/**********************************
You can implement any additional functions
you may need.
**********************************/
