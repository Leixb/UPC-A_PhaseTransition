#include <iostream>
#include <cstdlib>

#include "graph.h"
#include "graph_generator.h"

using namespace std;

void usage() {
	cerr << "USAGE:" << endl
		 << "./prog N repeticions delta_p" << endl;
}

int main(int argc, char *argv[]) {

	seed_generator();

	if (argc != 4) {
		usage();
		return 1;
	}

	const int n = atoi(argv[1]);
	const int repeticions = atoi(argv[2]);
	const double delta_p = stod(argv[3]);

	cout << "# N=" << n << " REP=" << repeticions << " delta=" << delta_p << endl
		 << "# p-connected" << ' ' << "p" << endl;

	for (double p = 0.0; p <= 1.0; p += delta_p) {

		int count = 0;

		for (int i = 0; i < repeticions; ++i) {
			count += BRG(n, p).is_connected();
		}

		cout << p << ' ' << double(count)/double(repeticions) << endl;

	}

	return 0;
}
