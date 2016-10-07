#include "Fib2584Ai.h"

bool Fib2584Ai::_inited = false;
static const int *_fib = GameBoard::fibonacci_;

static int get_fib_index(int fib)
{
	if (fib < 0 || fib > 2584) {
		return -1;
	}
	for (int i = 0; i < 20; i++) {
		if (fib == _fib[i]) {
			return i;
		}
	}
	return -1;
}

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

static double ai_score(const int board[4][4])
{
	double score, max_board = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			max_board = board[i][j] > max_board ? board[i][j] : max_board;
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			score += board[i][j] == 0 ? 1 : 0;
			//score += 0.12 * pow(max_board - board[i][j], 3.5);
		}
	}
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
	double max_score = -1e300, score;
	int dir, max_dir = -1;
	int nextBoards[4][4][4];
	for (dir = 0; dir < 4; dir++) {
		memcpy(nextBoards[dir], board, sizeof(int) << 4);
	}
	
	rotate_to_up(nextBoards[1], MOVE_RIGHT);
	rotate_to_up(nextBoards[2], MOVE_DOWN);
	rotate_to_up(nextBoards[3], MOVE_LEFT);
	
	int tmp[4], tmp_count;
	
	for (dir = 0; dir < 4; dir++) {
		for (int j = 0; j < 4; j++) {
			// compact
			tmp_count = 0;
			for (int i = 0; i < 4; i++) {
				if (nextBoards[dir][i][j]) {
					tmp[tmp_count++] = nextBoards[dir][i][j];
				}
			}
			for (int i = 0; i < 4; i++) {
				nextBoards[dir][i][j] = i < tmp_count ? tmp[i] : 0;
			}
			
			// merge
			for (int i = 0; i < 3; i++) {
				int mm = nextBoards[dir][i][j] + nextBoards[dir][i+1][j];
				if (-1 != get_fib_index(mm)) {
					nextBoards[dir][i][j] = mm;
					for (int ii = i+1; ii < 3; ii++) {
						nextBoards[dir][ii][j] = nextBoards[dir][ii+1][j];
					}
					nextBoards[dir][3][j] = 0;
					break;
				}
			}
		}
	}
	
	reverse_rotate(nextBoards[1], MOVE_RIGHT);
	reverse_rotate(nextBoards[2], MOVE_DOWN);
	reverse_rotate(nextBoards[3], MOVE_LEFT);
	
	for (dir = 0; dir < 4; dir++) {
		if (0 == memcmp(nextBoards[dir], board, sizeof(int) << 4)) {
			continue;
		}
		score = ai_score(nextBoards[dir]);
		if (score > max_score) {
			max_score = score;
			max_dir = dir;
		}
	}
	
	if (max_dir == -1) printf("shit\n");
	return static_cast<MoveDirection>(max_dir);
}

void Fib2584Ai::gameOver(int board[4][4], int iScore)
{
	return;
}

/**********************************
You can implement any additional functions
you may need.
**********************************/
