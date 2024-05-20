#include "Algorithm.hpp"
#include "Graph.hpp"
#include <queue>
#include <unordered_map>
#include <iostream>
#include <climits>
#include <vector>

using namespace ariel;
using namespace std;

int ariel::Algorithms::isConnected(ariel::Graph &graph)
{
    std::vector<int> visited(graph.getVertices(), false);
    std::vector<std::vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix();

    DFS(0, visited, adjacencyMatrix);
    for (bool visit : visited)
    {
        if (!visit)
        {
            return 0;
        }
    }
    return 1;
}

void Algorithms::DFS(std::vector<bool>::size_type vertex, std::vector<int> &visited, std::vector<std::vector<int>> &adjacencyMatrix){
    visited[vertex] = true;
    for (std::vector<bool>::size_type i = 0; i < adjacencyMatrix[vertex].size(); i++)
    {
        if (adjacencyMatrix[vertex][i] != 0 && !visited[i])
        {
            DFS(i, visited, adjacencyMatrix);
        }
    }
}


std::string Algorithms::shortestPath(ariel::Graph &graph, int s, int e)
{
    size_t start = static_cast<size_t>(s);
    size_t end = static_cast<size_t>(e);
    std::queue<size_t> q;
    std::unordered_map<size_t, size_t> distances;
    std::unordered_map<size_t, size_t> previous;

    distances[start] = 0;
    q.push(start);

    while (!q.empty())
    {
        size_t current = q.front();
        q.pop();

        if (current == end)
        {
            std::string path;
            for (size_t i = end; i != start; i = previous[i])
            {
                path = "->" + std::to_string(i) + path;
            }
            path = std::to_string(start) + path;
            return path;
        }

        for (size_t i = 0; i < graph.getAdjacencyMatrix()[current].size(); i++)
        {
            if (graph.getAdjacencyMatrix()[current][i] != 0 && distances.count(i) == 0)
            {
                q.push(i);
                distances[i] = distances[current] + 1;
                previous[i] = current;
            }
        }
    }

    return "-1"; // Return an empty string if there's no path
}

void Algorithms::negativeCycle(ariel::Graph &graph)
{
    size_t V = graph.getAdjacencyMatrix().size();
    std::vector<int> dist(V, INT_MAX);
    dist[0] = 0;

    for (size_t i = 1; i <= V - 1; i++)
    {
        for (size_t j = 0; j < V; j++)
        {
            for (size_t k = 0; k < graph.getAdjacencyMatrix()[j].size(); k++)
            {
                if (dist[j] != INT_MAX && dist[j] + graph.getAdjacencyMatrix()[j][k] < dist[k])
                {
                    dist[k] = dist[j] + graph.getAdjacencyMatrix()[j][k];
                }
            }
        }
    }

    for (size_t j = 0; j < V; j++)
    {
        for (size_t k = 0; k < graph.getAdjacencyMatrix()[j].size(); k++)
        {
            if (dist[j] != INT_MAX && dist[j] + graph.getAdjacencyMatrix()[j][k] < dist[k])
            {
                std::cout << "Graph contains a negative weight cycle" << std::endl;
                return;
            }
        }
    }

    std::cout << "No negative weight cycle found" << std::endl;
}

std::string Algorithms::isBipartite(ariel::Graph &graph)
{
    size_t V = graph.getAdjacencyMatrix().size();
    std::vector<int> colorArr(V, -1);
    std::vector<size_t> setA, setB;

    for (size_t i = 0; i < V; i++)
    {
        if (colorArr[i] == -1)
        {
            std::queue<size_t> q;
            q.push(i);
            colorArr[i] = 1;
            setA.push_back(i);

            while (!q.empty())
            {
                size_t u = q.front();
                q.pop();

                for (size_t v = 0; v < V; ++v)
                {
                    if (graph.getAdjacencyMatrix()[u][v] && colorArr[v] == -1)
                    {
                        colorArr[v] = 1 - colorArr[u];
                        q.push(v);
                        if (colorArr[v] == 1)
                        {
                            setA.push_back(v);
                        }
                        else
                        {
                            setB.push_back(v);
                        }
                    }
                    else if (graph.getAdjacencyMatrix()[u][v] && colorArr[v] == colorArr[u])
                    {
                        return "0";
                    }
                }
            }
        }
    }

    std::string result = "The graph is bipartite: A={";
    for (size_t i = 0; i < setA.size(); ++i)
    {
        result += std::to_string(setA[i]);
        if (i != setA.size() - 1)
        {
            result += ", ";
        }
    }
    result += "}, B={";
    for (size_t i = 0; i < setB.size(); ++i)
    {
        result += std::to_string(setB[i]);
        if (i != setB.size() - 1)
        {
            result += ", ";
        }
    }
    result += "}.";
    return result;
}

std::string Algorithms::isContainsCycle(ariel::Graph &graph)
{
    if (graph.hasCycle())
    {
        graph.printCycle();
    }
    return "0";
}