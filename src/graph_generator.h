#ifndef GRAPH_GENERATOR_H
#define GRAPH_GENERATOR_H

#include <random>
#include "graph.h"

namespace {
	std::default_random_engine generator;
}

// Binomial random graph
Graph BRG(const std::size_t& n, const double& p);

double distance(const std::pair<double, double> &a, const std::pair<double, double> &b);

// geometric random graph
Graph GRG(const std::size_t& n, const double& r);

void seed_generator();

#endif
