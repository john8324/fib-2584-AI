#ifndef __TD_H__
#define __TD_H__

#include <iostream>
#include <vector>
#include <stack>
#include "Feature.h"

// <position, reward>
typedef pair<MyBoard, int> State;

// TD(0) learning
class TD{
public:
	// constructor and destructor
	TD();
	~TD();
	// method
	double eval(const Feature& feature) const;
	void pushAfterState(const State &state) {afterStates.push(state);}
	void updateWeight(int iScore);

private:
	vector<double> weight;
	stack<State> afterStates;
	const double alpha = 0.0005; // learning rate
};

#endif