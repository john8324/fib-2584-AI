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

static double eval_expected(int _board)
{
	return 0;
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
		//cout << score << endl;
		//cout << after[i] << endl;
		if (flag) {
			double expected = score + eval_expected(after[i].compress());
			max_expected = expected > max_expected ? expected : max_expected;
		}
	}
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



