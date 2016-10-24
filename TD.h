#ifndef __TD_H__
#define __TD_H__

#include <iostream>
#include <vector>
#include <stack>
#include "Feature.h"

typedef pair<MyBoard, double> State;

// TD(0) learning
class TD{
public:
	// constructor and destructor
	TD();
	~TD();
	// method
	double eval(const Feature& feature) const;
	void pushAfterState(const State &state) {afterStates.push(state);}
	void updateWeight();

private:
	vector<double> weight;
	stack<State> afterStates;
	const double alpha = 0.002; // learning rate
};

#endif