#ifndef __FIB2X3SOLVER_H__
#define __FIB2X3SOLVER_H__

// include anything you might use
#include <iostream>
#include <stack>
#include <map>
#include "MyBoard.h"

class Fib2x3Solver
{
public:
	Fib2x3Solver();
	~Fib2x3Solver();
	// initialize solver
	void initialize(int argc, char* argv[]);
	// do some action when game over
	double evaluteExpectedScore(int board[2][3]);
	int findBestMove(int board[2][3]);
	
	/**********************************
	You can implement any additional functions
	or define any variables you may need.
	**********************************/
private:
	bool validPosition(int board[2][3]);
	map<int, bool> _validPos;

};

#endif