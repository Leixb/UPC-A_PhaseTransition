#include "graph.h"

#include<queue>
#include<vector>
#include<iostream>

Graph::Graph(const size_t &n) {
	AdjList = std::vector<std::list<std::size_t> > (n);
}

void Graph::addDirectedEdge(const std::size_t &a, const std::size_t &b) {
	AdjList[a].push_back(b);
}

void Graph::addUndirectedEdge(const std::size_t &a, const std::size_t &b) {
	AdjList[a].push_back(b);
	AdjList[b].push_back(a);
}


const std::list<std::size_t>& Graph::neighbors(const std::size_t& v) const {
	return AdjList[v];
}

unsigned int Graph::NconnectedComponents() const {
	std::vector<bool> visited(AdjList.size(), false);

	unsigned int count = 0;
	std::size_t next = 0;

	std::queue<std::size_t> Q;

	while (next < AdjList.size()) {

		++count;

		Q.push(next);

		// BFS
		while (!Q.empty()) {
			size_t v = Q.front();
			Q.pop();

			visited[v] = true;

			for (const std::size_t &u : this->neighbors(v))
				if (!visited[u]) Q.push(u);
		}

		for (;next < AdjList.size() && visited[next]; ++next);
	}

	return count;
}

void Graph::print() const {

	for (std::size_t i = 0; i < AdjList.size(); ++i) {
		std::cout << i << " :";
		for (const std::size_t &j : AdjList[i]) std::cout << ' ' << j;
		std::cout << std::endl;
	}

}
