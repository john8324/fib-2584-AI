#include "TD.h"

TD::TD()
{
	weight.resize(1 << 23); // size of Feature
	FILE *fp = fopen("TD_w.bin", "r");
	if (fp) {
		fread(&weight[0], sizeof(double), 1 << 23, fp);
		fclose(fp);
	}
}

TD::~TD()
{
	FILE *fp = fopen("TD_w.bin", "w");
	if (fp) {
		fwrite(&weight[0], sizeof(double), 1 << 23, fp);
		fclose(fp);
	}
}

double TD::eval(const Feature &feature) const
{
	vector<int> f = feature.getFeature(); // sparse
	double sum = 0;
	for (int i = 0; i < f.size(); i++) {
		sum += weight[f[i]];
	}
	return sum;
}

void TD::updateWeight()
{
	auto last = afterStates.top();
	afterStates.pop();
	double Vs = 5000;
	if (last.first.maxTile() >= 610) {
		// WIN
		Vs = 100000;
	} else if (last.first.isOver()) {
		// LOSE
		Vs = 0;
	} else {
		cout << "LAST is NOT over!!!!!!" << endl;
	}
	while (!afterStates.empty()) {
		auto top = afterStates.top();
		afterStates.pop();
		const Feature f(top.first);
		const double ori_Vs = eval(f);
		double dV = alpha * (top.second + Vs - ori_Vs);
		// dv/df = w
		vector<int> ff = f.getFeature();
		for (int i = 0; i < ff.size(); i++) {
			weight[ff[i]] += dV;
			//cout << weight[ff[i]] << endl;
		}
		Vs -= top.second;
	}
}
