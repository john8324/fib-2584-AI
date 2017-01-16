#ifndef __IDAB_H__
#define __IDAB_H__

#include <algorithm>
#include <vector>
#include "MyBoard.h"

// Iterative deepening alpha-beta prunning
class IDAB
{
public:
	IDAB() {};
	int F3(const MyBoard &board, int alpha, int beta, int depth, int limit, int evil_count);
	int G3(const MyBoard &board, int alpha, int beta, int depth, int limit, int evil_count);
	int executeIDAB();
};

#endif