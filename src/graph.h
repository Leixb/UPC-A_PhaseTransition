#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>

class Graph {
	std::vector<std::list<std::size_t> > AdjList;

	public:

	Graph(const std::size_t &n);

	void addUndirectedEdge(const std::size_t& a, const std::size_t& b);
	void addDirectedEdge(const std::size_t& a, const std::size_t& b);

	unsigned int NconnectedComponents() const;
	bool is_connected() const;

	void print() const;

	const std::list<std::size_t>& neighbors(const std::size_t& v) const;
};

#endif /* ifndef GRAPH_H */
