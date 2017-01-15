#include "Fib2584Ai.h"

#define MAX_DEPTH 10

static int G3(const MyBoard &board, int alpha, int beta, int d, int evil_count);

static int F3(const MyBoard &board, int alpha, int beta, int d, int evil_count)
{
	// Fail soft alpha-beta
	//printf("alpha = %f    beta = %f    d = %d\n", alpha, beta, d);
	if (d >= MAX_DEPTH) {
		return board.maxTile();
	}
	MyBoard after[] = {board, board, board, board};
	int m = -1;
	int count = 0;
	for (int i = 0; i < 4; i++) {
		int r;
		if (after[i].move(static_cast<MoveDirection>(i), r)) {
			count++;
			alpha = m > alpha ? m : alpha;
			int t = G3(after[i], alpha, beta, d + 1, evil_count + 1);
			m = t > m ? t : m;
			if (m >= beta) return m;
		}
	}
	return count ? m : board.maxTile();
}

static int G3(const MyBoard &board, int alpha, int beta, int d, int evil_count)
{
	// Fail soft alpha-beta
	//printf("alpha = %f    beta = %f    d = %d\n", alpha, beta, d);
	if (d >= MAX_DEPTH) {
		return board.maxTile();
	}
	int m = 2147483647;
	int count = 0, k = evil_count & 3 ? 1 : 3;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board.board[i][j] == 0) {
				MyBoard after(board);
				after.board[i][j] = k;
				count++;
				beta = m < beta ? m : beta;
				int t = F3(after, alpha, beta, d + 1, evil_count);
				m = t < m ? t : m;
				if (m <= alpha) return m;
			}
		}
	}
	return count ? m : board.maxTile();
}

static void eval_evil(const MyBoard &board, double &val, int evil_count)
{
	val = F3(board, board.maxTile() + 1, board.maxTile() + 2, 0, evil_count);
}

Fib2584Ai::Fib2584Ai()
{
	move_count = 0;
}

void Fib2584Ai::initialize(int argc, char* argv[])
{
	srand(time(NULL));
}

MoveDirection Fib2584Ai::generateMove(int board[4][4])
{
	MyBoard after[] = {board, board, board, board};
	int max_dir = -1, max_r = 0; // (dir and r) of max_score
	double max_score = -1e300;
	for (int i = 0; i < 4; i++) {
		int r;
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

int Fib2584Ai::generateEvilMove(int board[4][4])
{
	int next = (++move_count) & 3 ? 1 : 3;
	if (move_count == 1) {
		return 0;
	} else if (move_count == 2) {
		return 15;
	}
	int min_i = -1;
	double min_val = 1e300;
	for (int i = 0; i < 16; i++) {
		if (board[i/4][i%4] == 0) {
			board[i/4][i%4] = next;
			double val;
			eval_evil(MyBoard(board), val, move_count);
			if (val < min_val) {
				min_val = val;
				min_i = i;
			}
			board[i/4][i%4] = 0;
		}
	}
	return min_i;
}

void Fib2584Ai::gameOver(int board[4][4], int iScore)
{
	MyBoard after(board);
	//cout << "r = 0\nafter = \n" << after << endl;
	td.pushAfterState(State(after, 0));
	//printf("%d\n", iScore);
	td.updateWeight(iScore);
	move_count = 0;
}

/**********************************
You can implement any additional functions
you may need.
**********************************/
