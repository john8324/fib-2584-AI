#include "MyBoard.h"

const int MyBoard::_fib[] = {0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309};

static int move_up(int board[2][3])
{
	int tmp[2], tmp_count, score = 0;
	// check each column
	for (int j = 0; j < 3; j++) {
		// compact
		tmp_count = 0;
		for (int i = 0; i < 2; i++) {
			if (board[i][j]) {
				tmp[tmp_count++] = board[i][j];
			}
		}
		for (int i = 0; i < 2; i++) {
			board[i][j] = i < tmp_count ? tmp[i] : 0;
		}
		
		// merge
		for (int i = 0; i < 1 && board[i+1][j]; i++) {
			int mm = board[i][j] + board[i+1][j];
			if (-1 != MyBoard::get_fib_index(mm)) {
				board[i][j] = mm;
				score += mm;
				for (int ii = i+1; ii < 1; ii++) {
					board[ii][j] = board[ii+1][j];
				}
				board[1][j] = 0;
			}
		}
	}
	return score;
}

static int move_left(int board[2][3])
{
	int tmp[3], tmp_count, score = 0;
	// check each row
	for (int i = 0; i < 2; i++) {
		// compact
		tmp_count = 0;
		for (int j = 0; j < 3; j++) {
			if (board[i][j]) {
				tmp[tmp_count++] = board[i][j];
			}
		}
		for (int j = 0; j < 3; j++) {
			board[i][j] = j < tmp_count ? tmp[j] : 0;
		}
		
		// merge
		for (int j = 0; j < 2 && board[i][j+1]; j++) {
			int mm = board[i][j] + board[i][j+1];
			if (-1 != MyBoard::get_fib_index(mm)) {
				board[i][j] = mm;
				score += mm;
				for (int jj = j+1; jj < 2; jj++) {
					board[i][jj] = board[i][jj+1];
				}
				board[2][i] = 0;
			}
		}
	}
	return score;
}

static void flip_up_down(int board[2][3])
{
	for (int j = 0; j < 3; j++) {
		int tmp = board[0][j];
		board[0][j] = board[1][j];
		board[1][j] = tmp;
	}
}

static void flip_left_right(int board[2][3])
{
	for (int i = 0; i < 2; i++) {
		int tmp = board[i][0];
		board[i][0] = board[i][2];
		board[i][2] = tmp;
	}
}

MyBoard::MyBoard(int comp)
{
	// extract
	for (int i = 1; i >= 0; i--) {
		for (int j = 2; j >= 0; j--) {
			board[i][j] = _fib[comp & 0x1F];
			comp = comp >> 5;
		}
	}
}

bool MyBoard::move(MoveDirection dir, int &score)
{
	MyBoard ori = *this;
	score = 0;
	switch (dir) {
		case MOVE_UP:
			score = move_up(board);
			break;
			
		case MOVE_DOWN:
			flip_up_down(board);
			score = move_up(board);
			flip_up_down(board);
			break;

		case MOVE_LEFT:
			score = move_left(board);
			break;

		case MOVE_RIGHT:
			flip_left_right(board);
			score = move_left(board);
			flip_left_right(board);
			break;
			
		default:
			break;
	}
	return ori != *this;
}

bool MyBoard::isOver() const
{
	for (int i = 0; i < 4; i++) {
		MyBoard tmp = *this;
		int s;
		if (tmp.move((MoveDirection)i, s)) return false;
	}
	return true;
}

bool MyBoard::isFull() const
{
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			if (!board[i][j]) return false;
		}
	}
	return true;
}

int MyBoard::maxTile() const
{
	int max = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			max = board[i][j] > max ? board[i][j] : max;
		}
	}
	return max;
}

int MyBoard::compress() const
{
	int comp = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			comp = comp << 5 | get_fib_index(board[i][j]);
		}
	}
	return comp;
}
