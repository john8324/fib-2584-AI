#include "IDAB.h"

static int f(const MyBoard &board)
{
	return board.maxTile() + 10 * board.zeroCount();
}

int IDAB::F3(const MyBoard &board, int alpha, const int beta, const int depth, const int evil_count)
{
	// Fail soft alpha-beta
	if (depth >= limit) {
		return f(board);
	}
	vector<MyBoard> after;
	for (int i = 0; i < 4; i++) {
		MyBoard tmp = board;
		int r;
		if (tmp.move(static_cast<MoveDirection>(i), r)) {
			after.push_back(tmp);
		}
	}
	int m = 0;
	for (int i = 0; i < after.size(); i++) {
		alpha = m > alpha ? m : alpha;
		int t = G3(after[i], alpha, beta, depth + 1, evil_count + 1);
		m = t > m ? t : m;
		if (m >= beta) {
			break;
		}
	}
	return m;
}

int IDAB::G3(const MyBoard &board, const int alpha, int beta, const int depth, const int evil_count)
{
	// Fail soft alpha-beta
	if (depth >= limit) {
		return f(board);
	}
	const int k = evil_count & 3 ? 1 : 3;
	vector<MyBoard> after;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board.board[i][j] == 0) {
				MyBoard tmp(board);
				tmp.board[i][j] = k;
				after.push_back(tmp);
			}
		}
	}
	int m = 2147483647;
	for (int i = 0; i < after.size(); i++) {
		beta = m < beta ? m : beta;
		int t = F3(after[i], alpha, beta, depth + 1, evil_count);
		m = t < m ? t : m;
		if (m <= alpha) {
			break;
		}
	}
	return m;
}


