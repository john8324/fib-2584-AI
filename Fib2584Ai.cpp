#include "Fib2584Ai.h"

#define MAX_DEPTH 8

static double G3(const MyBoard &board, double alpha, double beta, int d);

static double F3(const MyBoard &board, double alpha, double beta, int d)
{
	// Fail soft alpha-beta
	//printf("alpha = %f    beta = %f    d = %d\n", alpha, beta, d);
	if (d >= MAX_DEPTH) {
		return board.maxTile();
	}
	MyBoard after[] = {board, board, board, board};
	double m = -1e300;
	int count = 0;
	for (int i = 0; i < 4; i++) {
		int r;
		if (after[i].move(static_cast<MoveDirection>(i), r)) {
			count++;
			alpha = m > alpha ? m : alpha;
			double t = G3(after[i], alpha, beta, d + 1);
			m = t > m ? t : m;
			if (m >= beta) return m;
		}
	}
	return count ? m : board.maxTile();
}

static double G3(const MyBoard &board, double alpha, double beta, int d)
{
	// Fail soft alpha-beta
	//printf("alpha = %f    beta = %f    d = %d\n", alpha, beta, d);
	if (d >= MAX_DEPTH) {
		return board.maxTile();
	}
	double m = 1e300;
	int count = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board.board[i][j] == 0) {
				for (int k = 1; k <= 3; k += 2) {
					MyBoard after(board);
					after.board[i][j] = k;
					count++;
					beta = m < beta ? m : beta;
					double t = F3(after, alpha, beta, d + 1);
					m = t < m ? t : m;
					if (m <= alpha) return m;
				}
			}
		}
	}
	return count ? m : board.maxTile();
}

static void eval_evil(const MyBoard &board, double &val)
{
	val = F3(board, board.maxTile() + 1, board.maxTile() + 2, 0);
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
	int min_i = -1;
	double min_val = 1e300;
	for (int i = 0; i < 16; i++) {
		if (board[i/4][i%4] == 0) {
			board[i/4][i%4] = next;
			double val;
			eval_evil(MyBoard(board), val);
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
