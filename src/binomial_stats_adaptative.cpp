#include <iostream>
#include <cstdlib>
#include <list>

#include "graph.h"
#include "graph_generator.h"

using namespace std;

void usage() {
	cerr << "USAGE:" << endl
		 << "./prog N repeticions dy" << endl;
}

#define DEPTH_LIMIT 10

int repeat(const int& n, const double& p, const int &rep) {
	int count = 0;
	for (int i = 0; i < rep; ++i)  count += BRG(n, p).is_connected();
	return count;
}

double average(const int& n, const double &p, const int &rep) {
	return double(repeat(n, p, rep))/double(rep);
}

void calculate(list<pair<double, double>> &l, vector<list<pair<double,double> >::iterator> &v,
			   const int &n, const double &dy, const int&rep, const int &depth=0) {
	if (depth > DEPTH_LIMIT) return; // no s hauria d arribar a complir mai si no afegim a next_it a la ultima iteracio

	vector <list<pair<double, double> >::iterator> next_it;

	for (const auto it : v) {
		auto prev = it;
		advance(prev, -1);

		if (it->second < -0.5) // Nomes calculem els que no han estat calculats previament
			it->second = average(n, it->first, rep);

		if (depth == DEPTH_LIMIT) continue; // No afegim mes si ja estem al limit

		if (abs(it->second - prev->second) > dy) {
			next_it.push_back(l.emplace(it, (it->first + prev->first)/2, -1));
			next_it.push_back(it);
		}
	}

	if (next_it.size() > 0)
		calculate(l, next_it, n, dy, rep, depth+1);
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

	const size_t part_ini = 10;

	list<pair<double, double> > l;
	l.emplace_back(0, 0);

	vector<list<pair<double, double> >::iterator> v(part_ini-1);

	for (size_t i = 1; i < part_ini; ++i)
		v[i-1] = l.emplace(l.end(), double(i)/double(part_ini), -1);


	calculate(l, v, n, dy, repeticions);
	for (const pair<double, double>& p : l)
		//if (p.second > -0.5)
		cout << p.first << ' ' << p.second << endl;

	return 0;
}
