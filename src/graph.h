#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <utility>

enum { NOTHING, EULERIAN_PATH, EULERIAN_CYCLE };

class Graph {
    std::vector<std::list<std::size_t> > AdjList;

    public:

    Graph(const std::size_t &n);

    void addUndirectedEdge(const std::size_t& a, const std::size_t& b);
    void addDirectedEdge(const std::size_t& a, const std::size_t& b);

    const bool hasCycles() const;
    const unsigned int EulerianCycleAndEulerianPath() const;
    const std::pair <unsigned int, unsigned int> ConnectedComponents() const;
    bool isConnected() const;

    void print() const;

    const std::list<std::size_t>& neighbors(const std::size_t& v) const;
};

#endif /* ifndef GRAPH_H */
