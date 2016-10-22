#include "TD.h"

static int max_state = 0;

TD::TD()
{
	weight.resize(1 << 22); // size of Feature
	FILE *fp = fopen("TD_w.bin", "r");
	if (fp) {
		fread(&weight[0], sizeof(double), 1 << 22, fp);
		fclose(fp);
	}
	afterStates.push(State(MyBoard(), 0)); // initial state
}

TD::~TD()
{
	FILE *fp = fopen("TD_w.bin", "w");
	if (fp) {
		fwrite(&weight[0], sizeof(double), 1 << 22, fp);
		fclose(fp);
	}
	cout << "max_state = " << max_state << endl;
}

double TD::eval(const Feature &feature) const
{
	vector<int> f = feature.getFeature(); // sparse binary feature
	double sum = 0;
	for (int i = 0; i < f.size(); i++) {
		sum += weight[f[i]];
	}
	//printf("eval sum = %.15e\n", sum);
	return sum;
}

void TD::updateWeight()
{
	max_state = afterStates.size() > max_state ? afterStates.size() : max_state;
	auto last = afterStates.top();
	afterStates.pop();
	double Vstt = 5000; // V(s(t+1))
	if (last.first.maxTile() >= 610) {
		// WIN
		Vstt = 1000000;
	} else if (last.first.isOver()) {
		// LOSE
		Vstt = -1000000;
	} else {
		cout << "LAST is NOT over!!!!!!" << endl;
		throw ("LAST is NOT over!!!!!!");
		return;
	}
	double rtt = last.second; // r(t+1)
	while (!afterStates.empty()) {
		auto top = afterStates.top();
		afterStates.pop();
		const Feature f(top.first);
		const double Vs = eval(f); // V(s(t))
		double dV = alpha * (rtt + Vstt - Vs);
		// v = w dot f, dv/df = w
		vector<int> ff = f.getFeature();
		for (int i = 0; i < ff.size(); i++) {
			weight[ff[i]] += dV;
			//cout << weight[ff[i]] << endl;
		}
		Vstt = Vs + dV; // update V(s(t)), V(s(t)) is V(s(t+1)) in next iteration
		rtt = top.second; // r(t) is r(t+1) in next iteration
	}
	afterStates.push(State(MyBoard(), 0)); // initial state
}
