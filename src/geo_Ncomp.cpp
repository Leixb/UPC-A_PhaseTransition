#include <iostream>
#include <cstdlib>
#include <list>

#include "graph_generator.h"
#include "adaptative_calc.h"

using namespace std;

void usage() {
	cerr << "USAGE:" << endl
		 << "./prog N repeticions dy" << endl;
}

double average(const int& n, const double &r, const int &rep) {
	int count = 0;
	for (int i = 0; i < rep; ++i)  count += GRG(n, r).NconnectedComponents();
	return double(count)/double(rep);
}


int main(int argc, char *argv[]) {

	seed_generator();

	if (argc != 4) {
		usage();
		return 1;
	}

	const int n = atoi(argv[1]);
	const int rep = atoi(argv[2]);
	const double dy = stod(argv[3]);

	cout << "# N=" << n << " REP=" << rep << " dy=" << dy << endl
		 << "# avg_Ncomp" << ' ' << "r" << endl;

	const auto l = adaptative_calc(n, rep, dy, average);

	for (const pair<double, double>& p : l)
		cout << p.first << ' ' << p.second << endl;

	return 0;
}
