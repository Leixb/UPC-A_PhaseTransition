#include<bits/stdc++.h>

#include "graph.h"
#include "graph_generator.h"

using namespace std;

int main(int argc, char *argv[]) {

	if (argc == 3) {
		const int n = atoi(argv[1]);
		const double p = stod(argv[2]);

		cout << BRG(n, p).NconnectedComponents() << endl;
		return 0;
	}

	int n;
	double p;

	while (cin >> n >> p) {
		const Graph g = BRG(n, p);

		//g.print();

		cout << g.NconnectedComponents() << endl;
	}

	return 0;
}
