#include "Fib2584Ai.h"

Fib2584Ai::Fib2584Ai()
{
	move_count = 0;
}

void Fib2584Ai::initialize(int argc, char* argv[])
{
	srand(time(NULL));
	return;
}


MoveDirection Fib2584Ai::generateMove( int board[4][4] )
{
	MyBoard after[] = {board, board, board, board};
	int max_dir = -1;
	double max_score = -1e300;
	for (int i = 0; i < 4; i++) {
		int r;
		if (after[i].move(static_cast<MoveDirection>(i), r)) {
			const double score = after[i].zeroCount() + 0.001 * after[i].maxTile();
			if (score > max_score) {
				max_score = score;
				max_dir = i;
			}
		}
	}
	move_count = max_dir == -1 ? 0 : move_count;
	return static_cast<MoveDirection>(max_dir);
}

int Fib2584Ai::generateEvilMove(int board[4][4])
{
	int next = (++move_count) & 3 ? 1 : 3;
	while (1) {
		int i = rand() % 16;
		if (board[i/4][i%4] == 0) {
			return i;
		}
	}
	return 0;
}

void Fib2584Ai::gameOver(int board[4][4], int iScore)
{
	move_count = 0;
}

/**********************************
You can implement any additional functions
you may need.
**********************************/
