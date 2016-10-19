#include "Feature.h"

Feature::Feature(const MyBoard &board)
{
	int index[4][4];
	_feature.resize(8); // 8 * pow(32, 4) = 1 << 23 features, but only 8 features are 'true'
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			index[i][j] = MyBoard::get_fib_index(board.board[i][j]);
			if (index[i][j] < 0) throw("Feature FAIL!!!!!");
		}
	}
	// each row
	for (int i = 0; i < 4; i++) {
		_feature[i] = i << 20 | index[i][0] << 15 | index[i][1] << 10 | index[i][2] << 5 | index[i][3];
	}
	// each column
	for (int j = 0; j < 4; j++) {
		_feature[j + 4] = 1 << 22 | j << 20 | index[0][j] << 15 | index[1][j] << 10 | index[2][j] << 5 | index[3][j];
	}
}
