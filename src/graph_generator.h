#ifndef GRAPH_GENERATOR_H
#define GRAPH_GENERATOR_H

#include <random>
#include "graph.h"

namespace {
	std::default_random_engine generator;
}

// Binomial random graph
Graph BRG(const size_t& n, const double& p);
// geometric random graph
Graph GRG(const size_t& n, const double& r);

#endif
