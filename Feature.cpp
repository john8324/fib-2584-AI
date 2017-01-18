#include "Feature.h"

Feature::Feature(const MyBoard &board)
{
	int index[4][4];
	_feature.resize(40); // sum = 40
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			index[i][j] = MyBoard::get_fib_index(board.board[i][j]);
			if (index[i][j] < 0) throw("Feature FAIL!!!!!");
		}
	}
	// 4-tuple
	// 4 * pow(32, 4) = 1 << 22 features, but sum = 32
	// 考慮旋轉對稱
	// 外側長條
	_feature[ 0] = 0 << 20 | index[0][0] << 15 | index[0][1] << 10 | index[0][2] << 5 | index[0][3];
	_feature[ 1] = 0 << 20 | index[0][3] << 15 | index[1][3] << 10 | index[2][3] << 5 | index[3][3];
	_feature[ 2] = 0 << 20 | index[3][3] << 15 | index[3][2] << 10 | index[3][1] << 5 | index[3][0];
	_feature[ 3] = 0 << 20 | index[3][0] << 15 | index[2][0] << 10 | index[1][0] << 5 | index[0][0];
	_feature[ 4] = 0 << 20 | index[0][3] << 15 | index[0][2] << 10 | index[0][1] << 5 | index[0][0];
	_feature[ 5] = 0 << 20 | index[3][3] << 15 | index[2][3] << 10 | index[1][3] << 5 | index[0][3];
	_feature[ 6] = 0 << 20 | index[3][0] << 15 | index[3][1] << 10 | index[3][2] << 5 | index[3][3];
	_feature[ 7] = 0 << 20 | index[0][0] << 15 | index[1][0] << 10 | index[2][0] << 5 | index[3][0];
	// 內側長條
	_feature[ 8] = 1 << 20 | index[1][0] << 15 | index[1][1] << 10 | index[1][2] << 5 | index[1][3];
	_feature[ 9] = 1 << 20 | index[0][2] << 15 | index[1][2] << 10 | index[2][2] << 5 | index[3][2];
	_feature[10] = 1 << 20 | index[2][3] << 15 | index[2][2] << 10 | index[2][1] << 5 | index[2][0];
	_feature[11] = 1 << 20 | index[3][1] << 15 | index[2][1] << 10 | index[1][1] << 5 | index[0][1];
	_feature[12] = 1 << 20 | index[1][3] << 15 | index[1][2] << 10 | index[1][1] << 5 | index[1][0];
	_feature[13] = 1 << 20 | index[3][2] << 15 | index[2][2] << 10 | index[1][2] << 5 | index[0][2];
	_feature[14] = 1 << 20 | index[2][0] << 15 | index[2][1] << 10 | index[2][2] << 5 | index[2][3];
	_feature[15] = 1 << 20 | index[0][1] << 15 | index[1][1] << 10 | index[2][1] << 5 | index[3][1];
	// 角落田字
	_feature[16] = 2 << 20 | index[0][0] << 15 | index[0][1] << 10 | index[1][1] << 5 | index[1][0];
	_feature[17] = 2 << 20 | index[0][3] << 15 | index[1][3] << 10 | index[1][2] << 5 | index[0][2];
	_feature[18] = 2 << 20 | index[3][3] << 15 | index[3][2] << 10 | index[2][2] << 5 | index[2][3];
	_feature[19] = 2 << 20 | index[3][0] << 15 | index[2][0] << 10 | index[2][1] << 5 | index[3][1];
	_feature[20] = 2 << 20 | index[0][0] << 15 | index[1][0] << 10 | index[1][1] << 5 | index[0][1];
	_feature[21] = 2 << 20 | index[0][3] << 15 | index[0][2] << 10 | index[1][2] << 5 | index[1][3];
	_feature[22] = 2 << 20 | index[3][3] << 15 | index[2][3] << 10 | index[2][2] << 5 | index[3][2];
	_feature[23] = 2 << 20 | index[3][0] << 15 | index[3][1] << 10 | index[2][1] << 5 | index[2][0];
	// 中間田字
	_feature[24] = 3 << 20 | index[0][1] << 15 | index[1][1] << 10 | index[1][2] << 5 | index[0][2];
	_feature[25] = 3 << 20 | index[1][3] << 15 | index[1][2] << 10 | index[2][2] << 5 | index[2][3];
	_feature[26] = 3 << 20 | index[3][2] << 15 | index[2][2] << 10 | index[2][1] << 5 | index[3][1];
	_feature[27] = 3 << 20 | index[2][0] << 15 | index[2][1] << 10 | index[1][1] << 5 | index[1][0];
	_feature[28] = 3 << 20 | index[0][2] << 15 | index[1][2] << 10 | index[1][1] << 5 | index[0][1];
	_feature[29] = 3 << 20 | index[2][3] << 15 | index[2][2] << 10 | index[1][2] << 5 | index[1][3];
	_feature[30] = 3 << 20 | index[3][1] << 15 | index[2][1] << 10 | index[2][2] << 5 | index[3][2];
	_feature[31] = 3 << 20 | index[1][0] << 15 | index[1][1] << 10 | index[2][1] << 5 | index[2][0];
	// additional features
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (index[i][j] > 18) {
				index[i][j] = 7;
			} else if (index[i][j] > 14) {
				index[i][j] = 6;
			} else if (index[i][j] > 4) {
				index[i][j] = 5;
			}
		}
	}
	// 6-tuple
	// pow(8, 6) = 1 << 18 features, but sum = 8
	// 1 2 3 4
	// x x 6 5
	// x x x x
	// x x x x
	_feature[32] = 1 << 22 | index[0][0] << 15 | index[0][1] << 12 | index[0][2] << 9 | index[0][3] << 6 | index[1][3] << 3 | index[1][2];
	_feature[33] = 1 << 22 | index[0][3] << 15 | index[1][3] << 12 | index[2][3] << 9 | index[3][3] << 6 | index[3][2] << 3 | index[2][2];
	_feature[34] = 1 << 22 | index[3][3] << 15 | index[3][2] << 12 | index[3][1] << 9 | index[3][0] << 6 | index[2][0] << 3 | index[2][1];
	_feature[35] = 1 << 22 | index[3][0] << 15 | index[2][0] << 12 | index[1][0] << 9 | index[0][0] << 6 | index[0][1] << 3 | index[1][1];
	_feature[36] = 1 << 22 | index[0][0] << 15 | index[1][0] << 12 | index[2][0] << 9 | index[3][0] << 6 | index[3][1] << 3 | index[2][1];
	_feature[37] = 1 << 22 | index[0][3] << 15 | index[0][2] << 12 | index[0][1] << 9 | index[0][0] << 6 | index[1][0] << 3 | index[1][1];
	_feature[38] = 1 << 22 | index[3][3] << 15 | index[2][3] << 12 | index[1][3] << 9 | index[0][3] << 6 | index[0][2] << 3 | index[1][2];
	_feature[39] = 1 << 22 | index[3][0] << 15 | index[3][1] << 12 | index[3][2] << 9 | index[3][3] << 6 | index[2][3] << 3 | index[2][2];
}
