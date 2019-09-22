#include<iostream>

#include "graph.h"
#include "graph_generator.h"

using namespace std;

inline void run(const int &n, const double &p) {
	const Graph g = BRG(n, p);

	cout << "# n=" << n << endl
		 << "# p=" << p << endl
		 << "# Ncomponents=" << g.NconnectedComponents() << endl;

	g.print();
}

int main(int argc, char *argv[]) {

	seed_generator();

	if (argc == 3) {
		run(atoi(argv[1]), stod(argv[2]));

		return 0;
	}

	int n;
	double p;

	while (cin >> n >> p) run(n, p);

	return 0;
}
