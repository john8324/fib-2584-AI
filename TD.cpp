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

double TD::eval(const Feature &feature)
{
	auto f = feature.getFeature();
	double sum = 0;
	for (int i = 0; weight.size(); i++) {
		sum += f[i] ? weight[i] : 0;
	}
	return sum;
}
