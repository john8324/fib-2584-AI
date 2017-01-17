#ifndef __IDAB_H__
#define __IDAB_H__

#include <cmath>
#include <algorithm>
#include <vector>
#include "MyBoard.h"
#include "TD.h"

// Iterative deepening alpha-beta prunning
class IDAB
{
public:
	IDAB() {};
	int F3(const MyBoard &board, int alpha, const int beta, const int depth, const int evil_count);
	int G3(const MyBoard &board, const int alpha, int beta, const int depth, const int evil_count);
	int IDAB_F3(const MyBoard &board, const int alpha, const int beta, const int evil_count);
	int IDAB_G3(const MyBoard &board, const int alpha, const int beta, const int evil_count);
	int limit;
};

#endif