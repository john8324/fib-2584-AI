#ifndef __MYBOARD_H__
#define __MYBOARD_H__

#include <cstring>
#include <random>
#include "Fib2584/MoveDirection.h"
using namespace std;

struct MyBoard{
	int board[2][3];
	// constructor
	MyBoard() {memset(board, 0, sizeof(int) * 6);}
	MyBoard(const int other[2][3]) {memcpy(board, other, sizeof(int) * 6);}
	MyBoard(const MyBoard &other) {*this = other;}
	// operator
	bool operator ==(const MyBoard& other) const {return 0 == memcmp(board, other.board, sizeof(int) * 6);}
	bool operator !=(const MyBoard& other) const {return !(*this == other);}
	// method
	bool move(MoveDirection dir, int& score);
	bool isOver() const;
	bool isFull() const;
	int maxTile() const;
	int zeroCount() const {
		int count = 0;
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[i][j] == 0) count++;
			}
		}
		return count;
	}
	inline static int get_fib_index(int fib);
	friend ostream& operator<< (ostream& os, const MyBoard& board) {
		for(int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				os << board.board[i][j] << " ";
			}
			os << endl;
		}
		return os;
	}
};

inline int MyBoard::get_fib_index(int fib)
{
	const int _fib[] = {0, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309};
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