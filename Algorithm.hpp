#ifndef ARIEL_ALGORITHM_HPP
#define ARIEL_ALGORITHM_HPP

#include "Graph.hpp"
#include <string>
#include <vector>

namespace ariel
{
    class Algorithms
    {
    public:
        static int isConnected(ariel::Graph &graph);
        static std::string shortestPath(ariel::Graph &graph, int s, int e);
        static std::string isContainsCycle(ariel::Graph& graph);
        static void negativeCycle(ariel::Graph &graph);
        static std::string isBipartite(ariel::Graph &graph);
        static void DFS(std::vector<bool>::size_type vertex, std::vector<int> &visited, std::vector<std::vector<int>> &adjacencyMatrix);
    };
}

#endif