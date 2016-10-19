#include "Fib2584Ai.h"

bool Fib2584Ai::_inited = false;

static double ai_score(const MyBoard &board)
{
	double score = 0;
	if (board.maxTile() >= 610) {
		// WIN
		score = 100;
	} else if (board.isOver()) {
		// LOSE
		score = -100;
	} else if (board.isFull()) {
		// There are NO ZEROS in board
		for (int dir = 0; dir < 4; dir++) {
			MyBoard after = board;
			if (!after.move(static_cast<MoveDirection>(dir))) {
				continue;
			}
			score += 1;
		}
	} else {
		for (int i = 0; i < 4; i++) {
			for (int j = 0 ; j < 4; j++) {
				if (!board.board[i][j]) {
					MyBoard after = board;
					after.board[i][j] = 1;
					for (int dir = 0; dir < 4; dir++) {
						if (!after.move(static_cast<MoveDirection>(dir))) {
							continue;
						}
						score += 0.1;
					}
					// ----------------------------------------
					after = board;
					after.board[i][j] = 3;
					for (int dir = 0; dir < 4; dir++) {
						if (!after.move(static_cast<MoveDirection>(dir))) {
							continue;
						}
						score += 0.1;
					}
				}
			}
		}
	}
	return score;
}

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
			double score = ai_score(after[i]);
			max_score = score > max_score ? score : max_score;
		}
	}
	return static_cast<MoveDirection>(max_dir == -1 ? rand() % 4 : max_dir);
}

void Fib2584Ai::gameOver(int board[4][4], int iScore)
{
	printf("%d\n", iScore);
}

/**********************************
You can implement any additional functions
you may need.
**********************************/
