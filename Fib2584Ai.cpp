#include "Fib2584Ai.h"

Fib2584Ai::Fib2584Ai()
{
	move_count = evil_count = 0;
}

void Fib2584Ai::initialize(int argc, char* argv[])
{
	srand(time(NULL));
}

MoveDirection Fib2584Ai::generateMove(int board[4][4])
{
	MyBoard after[] = {board, board, board, board};
	if (after[0].maxTile() == 1 && after[0].zeroCount() == 14) {
		evil_count = 2;
	}
	//cout << evil_count << " " << move_count << endl;
	++evil_count;
	int max_dir = -1, max_r = 0; // (dir and r) of max_score
	double max_score = -1e300;
	for (int i = 0; i < 4; i++) {
		int r;
		if (after[i].move(static_cast<MoveDirection>(i), r)) {
			const double score = r + idab.td.eval(Feature(after[i])) + (train ? 0 : idab.IDAB_G3(after[i], 1, 2, evil_count, 0.03) < 1 ? -10000 : 0);
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
	if (train) {
		idab.td.pushAfterState(State(after[max_dir], max_r));
	}
	return static_cast<MoveDirection>(max_dir);
}

int Fib2584Ai::generateEvilMove(int board[4][4])
{
	if (MyBoard(board) == MyBoard()) {
		move_count = 0;
	}
	int next = (++move_count) & 3 ? 1 : 3;
	if (move_count == 1) {
		return rand() % 16;
	} else if (move_count == 2) {
		int i = rand() % 15;
		return board[i/4][i%4] == 0 ? i : 15;
	} else if (train) {
		vector<int> zeros;
		for (int i = 0; i < 16; i++) {
			if (board[i/4][i%4] == 0) {
				zeros.push_back(i);
			}
		}
		return zeros[rand() % zeros.size()];
	}
	int min_i = -1;
	int min_val = 2147483647;
	for (int i = 0; i < 16; i++) {
		if (board[i/4][i%4] == 0) {
			board[i/4][i%4] = next;
			// evil_eval
			MyBoard after(board);
			int val, alpha, beta;
			alpha = after.maxTile();
			beta = alpha + 800;
			beta = min_val < beta ? min_val : beta;
			val = idab.IDAB_F3(after, alpha, beta, move_count, 0.025);
			if (val < min_val) {
				min_val = val;
				min_i = i;
			}
			board[i/4][i%4] = 0;
			if (min_val <= alpha) {
				break;
			}
		}
	}
	return min_i;
}

void Fib2584Ai::gameOver(int board[4][4], int iScore)
{
	if (train) {
		MyBoard after(board);
		//cout << "r = 0\nafter = \n" << after << endl;
		idab.td.pushAfterState(State(after, 0));
		//printf("%d\n", iScore);
		idab.td.updateWeight(iScore);
	}
	move_count = 0;
}

/**********************************
You can implement any additional functions
you may need.
**********************************/
