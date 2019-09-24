#include <iostream>
#include <cstdlib>

#include "graph.h"
#include "graph_generator.h"

using namespace std;

void usage() {
	cerr << "USAGE:" << endl
		 << "./prog N repeticions dy" << endl;
}

#define DEPTH_LIMIT 10

double repeat(const int& n, const double& p, const int&rep) {
	int count = 0;
	for (int i = 0; i < rep; ++i)  count += BRG(n, p).is_connected();
	return count;
}

void calculate(const vector<double> &v, const int &n, const double &dy,
			   const int&rep, const int &depth=0) {
	if (depth >= DEPTH_LIMIT) return;
	vector <double> next_it;
	vector <double> res (v.size());

	res[0] = repeat(n, 0, rep);

	// p = v[i]

	for (size_t i = 1; i < v.size(); ++i) {
		res[i] = repeat(n, v[i], rep)/double(rep);

		cout << v[i] << ' ' << res[i] << endl;

		if (abs(res[i] - res[i-1]) > dy) {
			next_it.push_back(v[i-1]);
			next_it.push_back((v[i]+v[i-1])/2);
			next_it.push_back(v[i]);
		}
	}

	if (next_it.size() > 0) calculate(next_it, n, dy, rep, depth+1);
}

int main(int argc, char *argv[]) {

	seed_generator();

	if (argc != 4) {
		usage();
		return 1;
	}

	const int n = atoi(argv[1]);
	const int repeticions = atoi(argv[2]);
	const double dy = stod(argv[3]);

	cout << "# N=" << n << " REP=" << repeticions << " dy=" << dy << endl
		 << "# p-connected" << ' ' << "p" << endl;

	vector<double> v(10);
	for (size_t i = 0; i < v.size(); ++i)
		v[i] = double(i)/double(v.size());

	calculate(v, n, dy, repeticions);
	//calculate({0,1}, n, dy, repeticions);

	return 0;
}
