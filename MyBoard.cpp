#include "MyBoard.h"

static void rotate_to_up(int board[4][4], MoveDirection dir)
{
	int tmp[4][4];
	switch (dir) {
		case MOVE_UP:
			break;
			
		case MOVE_DOWN:
			// upside down
			for (int j = 0; j < 4; j++) {
				tmp[0][j] = board[3][j];
				tmp[1][j] = board[2][j];
				tmp[2][j] = board[1][j];
				tmp[3][j] = board[0][j];
			}
			memcpy(board, tmp, sizeof(tmp));
			break;
			
		case MOVE_LEFT:
			// turn right
			tmp[0][0] = board[3][0], tmp[0][1] = board[2][0];
			tmp[0][2] = board[1][0], tmp[0][3] = board[0][0];
			tmp[1][0] = board[3][1], tmp[1][1] = board[2][1];
			tmp[1][2] = board[1][1], tmp[1][3] = board[0][1];
			tmp[2][0] = board[3][2], tmp[2][1] = board[2][2];
			tmp[2][2] = board[1][2], tmp[2][3] = board[0][2];
			tmp[3][0] = board[3][3], tmp[3][1] = board[2][3];
			tmp[3][2] = board[1][3], tmp[3][3] = board[0][3];
			memcpy(board, tmp, sizeof(tmp));
			break;
			
		case MOVE_RIGHT:
			// turn left
			tmp[0][0] = board[0][3], tmp[0][1] = board[1][3];
			tmp[0][2] = board[2][3], tmp[0][3] = board[3][3];
			tmp[1][0] = board[0][2], tmp[1][1] = board[1][2];
			tmp[1][2] = board[2][2], tmp[1][3] = board[3][2];
			tmp[2][0] = board[0][1], tmp[2][1] = board[1][1];
			tmp[2][2] = board[2][1], tmp[2][3] = board[3][1];
			tmp[3][0] = board[0][0], tmp[3][1] = board[1][0];
			tmp[3][2] = board[2][0], tmp[3][3] = board[3][0];
			memcpy(board, tmp, sizeof(tmp));
			break;
			
		default:
			break;
	}
}

inline static void reverse_rotate(int board[4][4], MoveDirection dir)
{
	switch (dir) {
		case MOVE_UP:
			break;
			
		case MOVE_DOWN:
			rotate_to_up(board, MOVE_DOWN);
			break;
			
		case MOVE_LEFT:
			rotate_to_up(board, MOVE_RIGHT);
			break;
			
		case MOVE_RIGHT:
			rotate_to_up(board, MOVE_LEFT);
			break;
			
		default:
			break;
	}
}

static int move_up(int board[4][4])
{
	int tmp[4], tmp_count, score = 0;
	/* check each column */
	for (int j = 0; j < 4; j++) {
		tmp_count = 0;
		for (int i = 0; i < 4; i++) {
			/* find the nonzero tile */
			if (board[i][j] == 0) {
				continue;
			}
			/* find next nonzero tile */
			int k;
			for (k = i + 1; k < 4; k++) {
				if (board[k][j] != 0) {
					break;
				}
			}
			if (k == 4) {
				tmp[tmp_count++] = board[i][j];
				break;
			}
			int mm = board[i][j] + board[k][j];
			if (-1 != MyBoard::get_fib_index(mm)) {
				tmp[tmp_count++] = mm; /* merged */
				score += mm;
				i = k;
			} else {
				tmp[tmp_count++] = board[i][j];
				i = k - 1;
			}
		}
		for (int i = 0; i < 4; i++) {
			board[i][j] = i < tmp_count ? tmp[i] : 0;
		}
	}
	return score;
}


bool MyBoard::move(MoveDirection dir, int &score)
{
	MyBoard ori = *this;
	rotate_to_up(board, dir);
	score = move_up(board);
	reverse_rotate(board, dir);
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
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (!board[i][j]) return false;
		}
	}
	return true;
}

int MyBoard::maxTile() const
{
	int max = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			max = board[i][j] > max ? board[i][j] : max;
		}
	}
	return max;
}
