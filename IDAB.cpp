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
	// position, reward
	vector<State> after;
	for (int i = 0; i < 4; i++) {
		MyBoard tmp = board;
		int r;
		if (tmp.move(static_cast<MoveDirection>(i), r)) {
			after.push_back(State(tmp, r));
		}
	}
	sort(after.begin(), after.end(), [](const State& a, const State& b) {return a.second > b.second;});
	int m = 0;
	for (int i = 0; i < after.size(); i++) {
		alpha = m > alpha ? m : alpha;
		int t = G3(after[i].first, alpha, beta, depth + 1, evil_count + 1);
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
	vector<pair<MyBoard, double>> after;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (board.board[i][j] == 0) {
				MyBoard tmp(board);
				tmp.board[i][j] = k;
				after.push_back(pair<MyBoard, double>(tmp, td.eval(Feature(tmp))));
			}
		}
	}
	sort(after.begin(), after.end(), [](const pair<MyBoard, double>& a, const pair<MyBoard, double>& b) {return a.second < b.second;});
	int m = 2147483647;
	for (int i = 0; i < after.size(); i++) {
		beta = m < beta ? m : beta;
		int t = F3(after[i].first, alpha, beta, depth + 1, evil_count);
		m = t < m ? t : m;
		if (m <= alpha) {
			break;
		}
	}
	return m;
}

int IDAB::IDAB_F3(const MyBoard &board, const int alpha, const int beta, const int evil_count)
{
	const clock_t st = clock();
	clock_t now = st;
	int m;
	for (limit = 1; limit <= 50 && (now - st) <= 0.06 * CLOCKS_PER_SEC; limit++) {
		m = F3(board, alpha, beta, 0, evil_count);
		now = clock();
	}
	//cout << limit << " " << (now - st) / (double)CLOCKS_PER_SEC << endl;
	return m;
}

int IDAB::IDAB_G3(const MyBoard &board, const int alpha, const int beta, const int evil_count)
{
	const clock_t st = clock();
	clock_t now = st;
	int m;
	for (limit = 1; limit <= 50 && (now - st) <= 0.06 * CLOCKS_PER_SEC; limit++) {
		m = G3(board, alpha, beta, 0, evil_count);
		now = clock();
	}
	//cout << limit << " " << (now - st) / (double)CLOCKS_PER_SEC << endl;
	return m;
}
