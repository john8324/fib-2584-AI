#ifndef __FEATURE_H__
#define __FEATURE_H__

#include <vector>
#include "MyBoard.h"

// basic 4-tuple networks
class Feature{
public:
	Feature(const MyBoard &board);
	const vector<int>& getFeature() const {return _feature;}

private:
	vector<int> _feature; // sparse
};

#endif