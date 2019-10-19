#include <iostream>
#include <cstdlib>
#include <list>
#include <utility>

#include "graph_generator.h"
#include "adaptative_calc.h"

using namespace std;

void usage() {
	cerr << "USAGE:" << endl
		 << "./prog tipus_graph propietat N repeticions dy" << endl;
}

Graph (*GeneradorGraph)(const size_t&, const double &p) = NULL;
int (*propietat)(const int&, const double&) = NULL;

double average(const int& n, const double &p, const int &rep) {
	int count = 0;
	for (int i = 0; i < rep; ++i)
		count += propietat(n, p);
	return double(count)/double(rep);
}

int numCompCon(const int& n, const double &p) {
	return GeneradorGraph(n, p).NconnectedComponents().first;
}

int esConnex(const int& n, const double &p) {
	return GeneradorGraph(n, p).NconnectedComponents().first == 1;
}

int midaCompConMax(const int& n, const double &p) {
	return GeneradorGraph(n, p).NconnectedComponents().second;
}

int cicle(const int& n, const double &p) {
	return GeneradorGraph(n, p).hasCycles();
}

int eulerianCycle(const int& n, const double &p) {
	return GeneradorGraph(n, p).EulerianCycleAndEulerianPath() == 2;
}

int eulerianPath(const int& n, const double &p) {
	return GeneradorGraph(n, p).EulerianCycleAndEulerianPath() == 1;
}

int main(int argc, char *argv[]) {

	seed_generator();

	if (argc != 6) {
		usage();
		return 1;
	}

	string tipus_graph = argv[1];
	string propietat_graph = argv[2];

	const int n = atoi(argv[3]);
	const int rep = atoi(argv[4]);
	const double dy = stod(argv[5]);

	cout << "# N=" << n << " REP=" << rep << " dy=" << dy << endl
		 << "# " << tipus_graph << endl
		 << "# " << propietat << ' ' << "p" << endl;

	if (tipus_graph == "BRG") GeneradorGraph = BRG;
	else if (tipus_graph == "GRG") GeneradorGraph = GRG;
	else return 1;

	if (propietat_graph == "numCompCon") propietat = numCompCon;
	else if (propietat_graph == "midaCompConMax") propietat = midaCompConMax;
	else if (propietat_graph == "esConnex") propietat = esConnex;
	else if (propietat_graph == "cicle") propietat = cicle; // Forest
	else if (propietat_graph == "eulerianPath") propietat = eulerianPath;
	else if (propietat_graph == "eulerianCycle") propietat = eulerianCycle;
	else return 1;

	const auto l = adaptative_calc(n, rep, dy, average);

	for (const pair<double, double>& p : l)
		cout << p.first << ' ' << p.second << endl;

	return 0;
}
