#include <random>
#include "graph.h"

namespace graph_gen {
	std::default_random_engine generator;
}

// Binomial random graph
Graph BRG(const size_t& n, const double& p) {

	Graph g (n);

	std::bernoulli_distribution distribution(p);

	for (size_t i = 0; i < n; ++i)
		for (size_t j = i+1; j < n; ++j)
			if (distribution(graph_gen::generator)) g.addUndirectedEdge(i, j);

	return g;

}

// geometric random graph
Graph GRG(const size_t& n, const double& r) {
	Graph g (n);

	//TODO

	return g;
}
