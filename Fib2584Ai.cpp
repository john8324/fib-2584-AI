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
	move_count = 0;
}

/**********************************
You can implement any additional functions
you may need.
**********************************/
