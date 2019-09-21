#include "graph_generator.h"

#include <chrono>
#include <cmath>
#include <iostream>

using std::size_t;
using std::pair;

// Binomial random graph
Graph BRG(const size_t& n, const double& p) {

	Graph g (n);

	std::bernoulli_distribution distribution(p);

	for (size_t i = 0; i < n; ++i)
		for (size_t j = i+1; j < n; ++j)
			if (distribution(generator)) g.addUndirectedEdge(i, j);

	return g;

}

double distance(const pair<double, double> &a, const pair<double, double> &b) {
	return hypot(a.first-b.first, a.second-b.second);
}

// geometric random graph
Graph GRG(const size_t& n, const double& r) {
	Graph g (n);

	std::vector<pair<double, double> > coords(n);

	std::uniform_real_distribution<double> distr_x(0.0, 1.0), distr_y(0.0, 1.0);

	for (size_t i = 0; i < n; ++i) coords[i] = {distr_x(generator), distr_y(generator)};

	for(size_t i = 0; i < n; ++i) {
		for(size_t j = i+1; j < n; ++j){
			if(distance(coords[i], coords[j]) <= r) g.addUndirectedEdge(i, j);
		}
	}

	return g;
}

void seed_generator() {
	generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
}
