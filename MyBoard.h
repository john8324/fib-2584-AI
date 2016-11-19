#ifndef __MYBOARD_H__
#define __MYBOARD_H__

#include <cstring>
#include "Fib2584/GameBoard.h"

struct MyBoard{
	int board[4][4];
	// constructor
	MyBoard() {memset(board, 0, sizeof(int) << 4);}
	MyBoard(const int other[4][4]) {memcpy(board, other, sizeof(int) << 4);}
	MyBoard(const MyBoard &other) {*this = other;}
	// operator
	bool operator ==(const MyBoard& other) const {return 0 == memcmp(board, other.board, sizeof(int) << 4);}
	bool operator !=(const MyBoard& other) const {return !(*this == other);}
	// method
	bool move(MoveDirection dir, int& score);
	bool isOver() const;
	bool isFull() const;
	int maxTile() const;
	int zeroCount() const {
		int count = 0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (board[i][j] == 0) count++;
			}
		}
		return count;
	}
	inline static int get_fib_index(int fib);
	friend ostream& operator<< (ostream& os, const MyBoard& board) {
		for(int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				os << board.board[i][j] << " ";
			}
			os << endl;
		}
		return os;
	}
};

inline int MyBoard::get_fib_index(int fib)
{
	const int* _fib = GameBoard::fibonacci_;
	if (fib < 0 || fib > _fib[31]) {
		return -1;
	}
	int left = 0, right = 32; // [left, right)
	while (left < right) {
		int mid = (left + right) / 2;
		if (fib == _fib[mid]) return mid;
		else if (fib < _fib[mid]) right = mid;
		else left = mid + 1;
	}
	return -1;
}

#endif