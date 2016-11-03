#include "Fib2x3Solver.h"

static bool quick_valid(int board[2][3])
{
	if (MyBoard(board).zeroCount() >= 5) {
		return false;
	}
	bool flag = false;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == 1 || board[i][j] == 3 || board[i][j] == 0) {
				flag = true;
			} else if (-1 == MyBoard::get_fib_index(board[i][j])) {
				return false;
			}
		}
	}
	return flag;
}

Fib2x3Solver::Fib2x3Solver()
{
}

void Fib2x3Solver::initialize(int argc, char* argv[])
{
	
}

double Fib2x3Solver::evaluteExpectedScore(int board[2][3])
{
	if (!validPosition(board)) {
		return -1;
	}
	return 0;
}

// 0: up
// 1: right
// 2: down
// 3: left
// -1: cannot move
int Fib2x3Solver::findBestMove(int board[2][3])
{
	MyBoard after[4] = {board, board, board, board};
	if (!validPosition(board)) {
		return -1;
	}
	for (int i = 0; i < 4; i++) {
		int score = 0;
		bool flag = after[i].move((MoveDirection)i, score);
		cout << flag << endl;
		cout << score << endl;
		cout << after[i] << endl;
	}
	return -1;
}

/**********************************
You can implement any additional functions
you may need.
**********************************/

bool Fib2x3Solver::validPosition(int board[2][3])
{
	if (!quick_valid(board)) {
		return false;
	}
	MyBoard now(board);
	int comp = now.compress();
	MyBoard xd(comp);
	cout << "test" << (now == xd) << endl;
	return true;
}



