#include "graph_generator.h"

#include <chrono>

// Binomial random graph
Graph BRG(const size_t& n, const double& p) {

	Graph g (n);

	std::bernoulli_distribution distribution(p);

	for (size_t i = 0; i < n; ++i)
		for (size_t j = i+1; j < n; ++j)
			if (distribution(generator)) g.addUndirectedEdge(i, j);

	return g;

}

// geometric random graph
Graph GRG(const size_t& n, const double& r) {
	Graph g (n);

	std::vector<std::pair<double, double> > coords(n);

	std::uniform_real_distribution<double> distr_x(0.0, 1.0), distr_y(0.0, 1.0);

	for (size_t i = 0; i < n; ++i)
		coords[i] = {distr_x(generator), distr_y(generator)};

	return g;
}

void seed_generator() {
	generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
}
