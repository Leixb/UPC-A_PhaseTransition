#include<bits/stdc++.h>

#include "graph.h"
#include "graph_generator.h"

using namespace std;

#define DELTA_P 0.0025
#define N_CASOS 50

int main(int argc, char *argv[]) {

	if (argc != 2) {
		cerr << "Give N as parameter" << endl;
		return 1;
	}

	seed_generator();

	const int n = atoi(argv[1]);

	cout << "# p-connected" << ' ' << "p" << endl;

	for (double p = 0.0; p <= 1.0; p += DELTA_P) {

		int count = 0;

		for (int i = 0; i < N_CASOS; ++i) {
			count += BRG(n, p).NconnectedComponents() == 1;
		}

		cout << p << ' ' << double(count)/double(N_CASOS) << endl;

	}

	return 0;
}
