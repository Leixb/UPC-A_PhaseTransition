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

unsigned int Graph::NconnectedComponents() const {
	std::vector<bool> visited(AdjList.size(), false);

	unsigned int count = 0;
	size_t next = 0;

	std::queue<size_t> Q;

	while (next < AdjList.size()) {

		++count;

		Q.push(next);

		// BFS
		while (!Q.empty()) {
			size_t v = Q.front();
			Q.pop();

			if (visited[v]) continue;

			visited[v] = true;

			for (const size_t &u : this->neighbors(v))
				if (!visited[u]) Q.push(u);
		}

		for (;next < AdjList.size() && visited[next]; ++next);
	}

	return count;
}

bool Graph::is_connected() const {
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
	// Prints adjacency list as a python dict (ca n be parsed with sagemath)

	std::cout << '{' << std::endl;
	for (size_t i = 0; i < AdjList.size(); ++i) {
		std::cout << i << " : [";
		for (const size_t &j : AdjList[i])
			std::cout << j << ", ";
		std::cout << "],"<< std::endl;
	}
	std::cout << '}' << std::endl;

}
