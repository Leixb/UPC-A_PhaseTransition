#include <iostream>
#include "graph.h"
#include "graph_generator.h"

using namespace std;

int main(int argc, char *argv[]) {

	if (argc == 3) {
		const int n = atoi(argv[1]);
		const double r = stod(argv[2]);

		cout << GRG(n, r).NconnectedComponents() << endl;
		return 0;
	}

	int n;
	double r;

	while (cin >> n >> r) {
		const Graph g = GRG(n, r);

		g.print();

		cout << g.NconnectedComponents() << endl;
	}

	return 0;
}
