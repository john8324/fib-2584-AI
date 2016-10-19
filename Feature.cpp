#include "Feature.h"

Feature::Feature(const MyBoard &board)
{
	int index[4][4];
	_feature.resize(1 << 23, false); // 8 * pow(32, 4) = 1 << 23
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			index[i][j] = MyBoard::get_fib_index(board.board[i][j]);
			if (index[i][j] < 0) throw("Feature FAIL!!!!!");
		}
	}
	// each row
	for (int i = 0; i < 4; i++) {
		_feature[i << 20 | index[i][0] << 15 | index[i][1] << 10 | index[i][2] << 5 | index[i][3]] = true;
	}
	// each column
	for (int j = 0; j < 4; j++) {
		_feature[1 << 22 | j << 20 | index[0][j] << 15 | index[1][j] << 10 | index[2][j] << 5 | index[3][j]] = true;
	}
}
