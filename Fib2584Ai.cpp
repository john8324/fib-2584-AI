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
	int max_dir = -1, max_r = 0; // (dir and r) of max_score
	double max_score = -1e300;
	for (int i = 0; i < 4; i++) {
		int r = 0;
		if (after[i].move(static_cast<MoveDirection>(i), r)) {
			const double score = r + td.eval(Feature(after[i]));
			if (score > max_score) {
				max_score = score;
				max_r = r;
				max_dir = i;
			}
		}
	}
	if (max_dir == -1) {
		cout << "board CANNOT move!!!!!!!!!!" << endl;
		cout << MyBoard(board);
		cout << "---------------------------" << endl;
		throw ("FAIL to gen move");
	}
	// max_r = max_dir == -1 ? 0 : max_r;
	//max_dir = max_dir == -1 ? rand() % 4 : max_dir;
	//cout << "r = 1\nafter = \n" << after[max_dir] << endl;
	//cout << "max_r = " << max_r << endl;
	td.pushAfterState(State(after[max_dir], max_r));
	return static_cast<MoveDirection>(max_dir);
}

void Fib2584Ai::gameOver(int board[4][4], int iScore)
{
	MyBoard after(board);
	//cout << "r = 0\nafter = \n" << after << endl;
	td.pushAfterState(State(after, 0));
	//printf("%d\n", iScore);
	td.updateWeight(iScore);
}

/**********************************
You can implement any additional functions
you may need.
**********************************/
