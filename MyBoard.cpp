#include "MyBoard.h"

/*
static int move_up(int board[4][4])
{
int tmp[4], tmp_count, score = 0;
	// check each column
	for (int j = 0; j < 4; j++) {
		// compact
		tmp_count = 0;
		for (int i = 0; i < 4; i++) {
			if (board[i][j]) {
				tmp[tmp_count++] = board[i][j];
			}
		}
		for (int i = 0; i < 4; i++) {
			board[i][j] = i < tmp_count ? tmp[i] : 0;
		}
		
		// merge
		for (int i = 0; i < 3 && board[i+1][j]; i++) {
			int mm = board[i][j] + board[i+1][j];
			if (-1 != MyBoard::get_fib_index(mm)) {
				board[i][j] = mm;
				score += mm;
				for (int ii = i+1; ii < 3; ii++) {
					board[ii][j] = board[ii+1][j];
				}
				board[3][j] = 0;
			}
		}
	}
	return score;
}
*/

bool MyBoard::move(MoveDirection dir, int &score)
{
	MyBoard ori = *this;/*
	switch (dir) {
		case MOVE_UP:
			score = move_up(board);
			break;
			
		case MOVE_DOWN:
		case MOVE_LEFT:
		case MOVE_RIGHT:
			rotate_to_up(board, dir);
			score = move_up(board);
			reverse_rotate(board, dir);
			break;
			
		default:
			break;
	}*/
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
