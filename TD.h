#ifndef __TD_H__
#define __TD_H__

#include <iostream>
#include <vector>
#include "Feature.h"

// TD(0) learning
class TD{
public:
	TD();
	~TD();
	double eval(const Feature& feature);

private:
	vector<double> weight;
	const double alpha = 0.01; // learning rate
};

#endif