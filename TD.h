#ifndef __TD_H__
#define __TD_H__

#include <iostream>
#include <vector>
#include <stack>
#include "Feature.h"

// TD(0) learning
class TD{
public:
	// constructor and destructor
	TD();
	~TD();
	// method
	double eval(const Feature& feature) const;
	void pushAfterState(const MyBoard &board) {afterStates.push(board);}
	void updateWeight();

private:
	vector<double> weight;
	stack<MyBoard> afterStates;
	const double alpha = 0.04; // learning rate
};

#endif