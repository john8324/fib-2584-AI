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
	double Vs = 2000;
	while (!afterStates.empty()) {
		auto top = afterStates.top();
		afterStates.pop();
		const Feature f(top);
		const double ori_Vs = eval(f);
		if (top.maxTile() >= 610) {
			// WIN
			Vs = 100000;
		} else if (top.isOver()) {
			// LOSE
			Vs = 0;
		} else {
			Vs -= 1;
		}
		double dV = alpha * (1 + Vs - ori_Vs);
		// v = f dot w, dv/df = w
		vector<int> ff = f.getFeature();
		for (int i = 0; i < ff.size(); i++) {
			weight[ff[i]] += dV;
			//cout << weight[ff[i]] << endl;
		}
	}
}
