#include "graph.h"

#include<queue>
#include<vector>
#include<iostream>

using std::size_t;

Graph::Graph(const size_t &n) {
    AdjList = std::vector<std::list<size_t> > (n);
}

void Graph::addDirectedEdge(const size_t &a, const size_t &b) {
    AdjList[a].push_back(b);
}

void Graph::addUndirectedEdge(const size_t &a, const size_t &b) {
    AdjList[a].push_back(b);
    AdjList[b].push_back(a);
}


const std::list<size_t>& Graph::neighbors(const size_t& v) const {
    return AdjList[v];
}

const bool Graph::hasCycles() const {
    std::vector<bool> visited(AdjList.size(), false);

    size_t next = 0;

    std::queue<size_t> Q;

    while (next < AdjList.size()) {

	Q.push(next);

	// BFS
	while (!Q.empty()) {
	    size_t v = Q.front();
	    Q.pop();

	    // Si estem tornant a visitar un vertex -> hi ha cicle
	    if (visited[v]) return true;

	    visited[v] = true;

	    for (const size_t &u : this->neighbors(v))
		if (!visited[u]) Q.push(u);
	}

	// Busquem seguent vertex no visitat (nova component)
	for (;next < AdjList.size() && visited[next]; ++next);
    }

    return false;
}

// 0 si nada, 1 si Path, 2 si Cycle y Path
const unsigned int Graph::EulerianCycleAndEulerianPath() const {
    unsigned int nVertex = AdjList.size();

    std::pair<unsigned int, unsigned int> info = ConnectedComponents();
    unsigned int nCC = info.first;
    unsigned int max = info.second;

    // all of its vertices with nonzero degree belong to a single connected component
    bool singleCC = (nCC + max - 1) == nVertex;

    if (singleCC) {
	int oddVertex = 0;
	for (unsigned int i = 0; i < nVertex; ++i)
	    if (AdjList[i].size() % 2 != 0)
		++oddVertex;

	if (oddVertex == 0) return EULERIAN_CYCLE;
	if (oddVertex == 2) return EULERIAN_PATH;
    }

    return NOTHING;
}

// retorna nombre de components connexes i mida de la component connexa gegant.
const std::pair <unsigned int, unsigned int> Graph::ConnectedComponents() const {
    std::vector<bool> visited(AdjList.size(), false);

    unsigned int count = 0;
    unsigned int max = 0;
    size_t next = 0;

    std::queue<size_t> Q;

    while (next < AdjList.size()) {

	++count;

	unsigned size = 0;

	Q.push(next);

	// BFS
	while (!Q.empty()) {
	    size_t v = Q.front();
	    Q.pop();

	    if (visited[v]) continue;

	    visited[v] = true;
	    ++size;

	    for (const size_t &u : this->neighbors(v))
		if (!visited[u]) Q.push(u);
	}

	if (size > max) max = size;

	// Busquem seguent vertex no visitat (nova component)
	for (;next < AdjList.size() && visited[next]; ++next);
    }

    return std::make_pair(count, max);
}

// Retorna true si el graph es connex
bool Graph::isConnected() const {
    std::vector<bool> visited(AdjList.size(), false);
    size_t count = 0;

    std::queue<size_t> Q;
    Q.push(0);

    while (!Q.empty()) {
	const size_t v = Q.front();
	Q.pop();

	if (visited[v]) continue;

	visited[v] = true;
	++count;

	for (const size_t &u : neighbors(v))
	    if (!visited[u]) Q.push(u);
    }

    return count == AdjList.size();
}

void Graph::print() const {
    // Prints adjacency list as a python dict

    std::cout << '{' << std::endl;
    for (size_t i = 0; i < AdjList.size(); ++i) {
	std::cout << i << " : [";
	for (const size_t &j : AdjList[i])
	    std::cout << j << ", ";
	std::cout << "],"<< std::endl;
    }
    std::cout << '}' << std::endl;

}
