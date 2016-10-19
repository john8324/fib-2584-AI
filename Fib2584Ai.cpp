#include "Fib2584Ai.h"

bool Fib2584Ai::_inited = false;

static double ai_score(const MyBoard &board)
{
	double score = 0;
	typedef pair<MyBoard, int> BoardState;
	// stack
	stack<BoardState> st_board;
	// push first
	st_board.push(BoardState(board, 0));
	while (!st_board.empty()) {
		// select top
		BoardState top = st_board.top();
		st_board.pop();
		if (top.first.maxTile() >= 10) {
			// WIN
			score += 10;
		} else if (top.first.isOver()) {
			// LOSE
			score -= 2.5;
		} else if (top.first.isFull()) {
			// There are NO ZEROS in board
			for (int dir = top.second; dir < 4; dir++) {
				MyBoard after = top.first;
				if (!after.move(static_cast<MoveDirection>(dir))) {
					continue;
				}
				st_board.push(BoardState(top.first, dir+1));
				st_board.push(BoardState(after, 0));
				break;
			}
		} else {
			for (int k = top.second; k < 128; k++) {
				int i = k >> 5, j = (k >> 3) & 0x11, dir = (k >> 1) & 0x11, n = k & 1;
				MyBoard after = top.first;
				if (after.board[i][j] == 0) {
					after.board[i][j] = n ? 3 : 1;
					if (!after.move(static_cast<MoveDirection>(dir))) {
						continue;
					}
					st_board.push(BoardState(top.first, k+1));
					st_board.push(BoardState(after, 0));
					break;
				}
			}
		}
	}
	//printf("Score!!!!!!!!!!!!!!!!!!\n");
	return score;
}

Fib2584Ai::Fib2584Ai()
{
}

void Fib2584Ai::initialize(int argc, char* argv[])
{
	if (_inited) return;
	srand(time(NULL));
	_inited = true;
}

MoveDirection Fib2584Ai::generateMove(const int board[4][4])
{
	MyBoard after[] = {board, board, board, board};
	int max_dir = -1;
	double max_score = -1e300;
	for (int i = 0; i < 4; i++) {
		if (after[i].move(static_cast<MoveDirection>(i))) {
			double score = ai_score(after[i]);
			max_score = score > max_score ? score : max_score;
		}
	}
	return static_cast<MoveDirection>(max_dir == -1 ? rand() % 4 : max_dir);
}

void Fib2584Ai::gameOver(int board[4][4], int iScore)
{
	printf("%d\n", iScore);
}

/**********************************
You can implement any additional functions
you may need.
**********************************/
