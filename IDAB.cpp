#include "IDAB.h"

int IDAB::F3(const MyBoard &board, int alpha, int beta, int depth, int limit, int evil_count)
{
	// Fail soft alpha-beta
	if (depth >= limit) {
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
			int t = G3(after[i], alpha, beta, depth + 1, limit, evil_count + 1);
			m = t > m ? t : m;
			if (m >= beta) return m;
		}
	}
	return m;
}

int IDAB::G3(const MyBoard &board, int alpha, int beta, int depth, int limit, int evil_count)
{
	// Fail soft alpha-beta
	if (depth >= limit) {
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
				int t = F3(after, alpha, beta, depth + 1, limit, evil_count);
				m = t < m ? t : m;
				if (m <= alpha) return m;
			}
		}
	}
	return count ? m : board.maxTile();
}


