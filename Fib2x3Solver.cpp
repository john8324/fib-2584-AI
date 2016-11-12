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

static bool actual_valid(int _board, map<int, bool> &_validPos)
{
	stack<int> st;
	// push all valid positions
	for (auto it = _validPos.begin(); it != _validPos.end(); ++it) {
		if (it->second) {
			st.push(it->first);
		}
	}
	if (st.empty()) {
		// Generate roots
		int roots[4][2];
		roots[0][0] = 1, roots[0][1] = 1;
		roots[1][0] = 1, roots[1][1] = 3;
		roots[2][0] = 3, roots[2][1] = 1;
		roots[3][0] = 3, roots[3][1] = 3;
		for (int r = 0; r < 4; r++) {
			for (int a = 0; a < 6; a++) {
				for (int b = a + 1; b < 6; b++) {
					MyBoard tmp;
					int *head = &(tmp.board[0][0]);
					head[a] = roots[r][0];
					head[b] = roots[r][1];
					int comp = tmp.compress();
					// No need to check repeated states, just pushing them
					_validPos[comp] = true;
					st.push(comp);
				}
			}
		}
	}
	while (!st.empty()) {
		int top = st.top();
		st.pop();
		if (top == _board) {
			return true;
		} else {
			//cout << "st.size() = " << st.size() << endl;
			// Generate next boards
			MyBoard now(top), board(_board);
			// Don't generate boards if "now" cannot generate _board
			if (now.maxTile() <= board.maxTile()) {
				MyBoard tmp = now;
				int score = 0;
				for (int d = 0; d < 4; d++) {
					if (tmp.move((MoveDirection)d, score)) {
						// Moved, generate all possible boards
						for (int i = 0; i < 2; i++) {
							for (int j = 0; j < 3; j++) {
								int comp = 0;
								if (tmp.board[i][j] == 0) {
									// gen 1
									tmp.board[i][j] = 1;
									comp = tmp.compress();
									if (_validPos.find(comp) == _validPos.end()) {
										// prevent pushing repeated states
										_validPos[comp] = true;
										st.push(comp);
									}
									// gen 3
									tmp.board[i][j] = 3;
									comp = tmp.compress();
									if (_validPos.find(comp) == _validPos.end()) {
										// prevent pushing repeated states
										_validPos[comp] = true;
										st.push(comp);
									}
									// roll back
									tmp.board[i][j] = 0;
								}
							}
						}
					}
				}
			}
		}
	}
	_validPos[_board] = false;
	return false;
}

static double eval_expected(int _board, int d, map<int, pair<double, int>> &_expectedDataBase)
{
	if (d < 0) {
		cout << "FAIL: wrong depth!!" << endl;
		return 0;
	}
	// check database
	auto it = _expectedDataBase.find(_board);
	if (it != _expectedDataBase.end()) {
		if (it->second.second <= d) {
			return it->second.first;
		}
	}
	if (d > 100) {
		_expectedDataBase[_board] = pair<double, int>(0, d);
		return 0;
	}
	MyBoard now(_board);
	cout << "eval_expected::now = " << endl << now << endl;
	cout << "depth = " << d << endl;
	int zero = now.zeroCount();
	if (zero == 0) {
		_expectedDataBase[_board] = pair<double, int>(0, d);
		cout << "expected = " << 0 << endl;
		return 0;
	}
	double expected = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			if (now.board[i][j] == 0) {
				// gen 1
				now.board[i][j] = 1;
				int move_count = 0;
				double tmp_exp = 0;
				for (int dir = 0; dir < 4; dir++) {
					MyBoard tmp(now);
					int score = 0;
					if (tmp.move((MoveDirection)dir, score)) {
						cout << "score = " << score << endl;
						tmp_exp += score + eval_expected(tmp.compress(), d + 1, _expectedDataBase);
						move_count++;
					}
				}
				expected += move_count == 0 ? 0 : 0.75 * tmp_exp / move_count;
				// gen 3
				now.board[i][j] = 3;
				move_count = 0;
				tmp_exp = 0;
				for (int dir = 0; dir < 4; dir++) {
					MyBoard tmp(now);
					int score = 0;
					if (tmp.move((MoveDirection)dir, score)) {
						cout << "score = " << score << endl;
						tmp_exp += score + eval_expected(tmp.compress(), d + 1, _expectedDataBase);
						move_count++;
					}
				}
				expected += move_count == 0 ? 0 : 0.25 * tmp_exp / move_count;
				// roll back
				now.board[i][j] = 0;
			}
		}
	}
	expected /= zero;
	_expectedDataBase[_board] = pair<double, int>(expected, d);
	cout << "expected = " << expected << endl;
	return expected;
}

Fib2x3Solver::Fib2x3Solver()
{
	FILE *fp = fopen("pos.bin", "r");
	if (fp) {
		unsigned char buf[5];
		while (5 == fread(buf, 1, 5, fp)) {
			int pos = buf[3] << 24 | buf[2] << 16 | buf[1] << 8 | buf[0];
			_validPos[pos] = buf[4];
		}
		fclose(fp);
	}
	fp = fopen("expected_db.bin", "r");
	if (fp) {
		unsigned char buf[16];
		while (16 == fread(buf, 1, 16, fp)) {
			int pos = buf[3] << 24 | buf[2] << 16 | buf[1] << 8 | buf[0];
			int d = buf[7] << 24 | buf[6] << 16 | buf[5] << 8 | buf[4];
			double expected = *((double*)(buf + 8));
			_expectedDataBase[pos] = pair<double, int>(expected, d);
		}
		fclose(fp);
	}
}

Fib2x3Solver::~Fib2x3Solver()
{
	FILE *fp = fopen("pos.bin", "w");
	if (fp) {
		for (auto it = _validPos.begin(); it != _validPos.end(); ++it) {
			int pos = it->first;
			unsigned char buf[5];
			buf[0] = pos & 0xFF;
			buf[1] = pos >> 8 & 0xFF;
			buf[2] = pos >> 16 & 0xFF;
			buf[3] = pos >> 24 & 0xFF;
			buf[4] = it -> second;
			fwrite(buf, 1, 5, fp);
		}
		fclose(fp);
	}
	fp = fopen("expected_db.bin", "w");
	if (fp) {
		for (auto it = _expectedDataBase.begin(); it != _expectedDataBase.end(); ++it) {
			int pos = it->first, d = it->second.second;
			unsigned char buf[8];
			buf[0] = pos & 0xFF;
			buf[1] = pos >> 8 & 0xFF;
			buf[2] = pos >> 16 & 0xFF;
			buf[3] = pos >> 24 & 0xFF;
			buf[4] = d & 0xFF;
			buf[5] = d >> 8 & 0xFF;
			buf[6] = d >> 16 & 0xFF;
			buf[7] = d >> 24 & 0xFF;
			fwrite(buf, 1, 8, fp);
			fwrite(&(it->second.first), 8, 1, fp);
		}
		fclose(fp);
	}
}

void Fib2x3Solver::initialize(int argc, char* argv[])
{
	
}

double Fib2x3Solver::evaluteExpectedScore(int board[2][3])
{
	MyBoard after[4] = {board, board, board, board};
	if (!validPosition(board)) {
		return -1;
	}
	double max_expected = 0;
	for (int i = 0; i < 4; i++) {
		int score = 0;
		bool flag = after[i].move((MoveDirection)i, score);
		//cout << flag << endl;
		cout << score << endl;
		//cout << after[i] << endl;
		if (flag) {
			double expected = score + eval_expected(after[i].compress(), 0, _expectedDataBase);
			max_expected = expected > max_expected ? expected : max_expected;
		}
	}
	cout << "max_expected = " << max_expected << endl;
	return max_expected;
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
	map<int, bool>::iterator it = _validPos.find(comp);
	if (it != _validPos.end()) {
		return it->second;
	}
	// Validate this board completely
	return actual_valid(comp, _validPos);
}



