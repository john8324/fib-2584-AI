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
	st.push(0); // initial value
	// push all valid positions
	for (auto it = _validPos.begin(); it != _validPos.end(); ++it) {
		if (it->second) {
			st.push(it->first);
		}
	}
	while (!st.empty()) {
		int top = st.top();
		st.pop();
		if (top == 0) {
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
						if (_validPos.find(comp) == _validPos.end()) {
							// prevent pushing repeated states
							_validPos[comp] = true;
							st.push(comp);
						}
					}
				}
			}
		} else if (top == _board) {
			return true;
		} else {
			cout << "st.size() = " << st.size() << endl;
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

Fib2x3Solver::Fib2x3Solver()
{
	FILE *fp = fopen("pos.txt", "r");
	if (fp) {
		int pos, valid;
		while (2 == fscanf(fp, "%d%d", &pos, &valid)) {
			_validPos[pos] = valid;
		}
		fclose(fp);
	}
}

Fib2x3Solver::~Fib2x3Solver()
{
	FILE *fp = fopen("pos.txt", "w");
	if (fp) {
		for (auto it = _validPos.begin(); it != _validPos.end(); ++it) {
			fprintf(fp, "%d %d\n", it->first, it->second);
		}
		fclose(fp);
	}
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
	map<int, bool>::iterator it = _validPos.find(comp);
	if (it != _validPos.end()) {
		return it->second;
	}
	// Validate this board completely
	return actual_valid(comp, _validPos);
}



