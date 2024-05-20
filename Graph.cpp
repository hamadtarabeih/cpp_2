#include "Graph.hpp"
#include <queue>
#include <unordered_map>
#include <iostream>
#include <climits>
#include <algorithm>
#include <string>
#include <vector>

using namespace ariel;
using namespace std;

size_t Graph::getVertices()
{
    return numberOfVertices;
};

size_t Graph::getNumEdges()
{
    return numberOfEdges;
}

bool Graph::getIsCyclic()
{
    return isCyclic;
}

std::vector<int> Graph::getAd(size_t v)
{
    return adjacencyMatrix[v];
}

void Graph::loadGraph(const std::vector<std::vector<int>> &matrix)
{
    // Not a squre matrix
    if (matrix.size() != matrix[0].size())
    {
        cout << "Not a squre matrix" << endl;
        return;
    }

    adjacencyMatrix = matrix;
    isCyclic = hasCycle();
    numberOfVertices = matrix.size();
    numberOfEdges = 0;

    for (size_t i = 0; i < matrix.size(); i++)
    {
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j] != 0)
            {
                numberOfEdges++;
                if (matrix[i][j] > 1)
                {
                    isWeighted = true;
                }
            }
            if (matrix[i][j] != matrix[j][i])
            {
                isDirected = true;
            }
        }
    }
}

std::vector<bool> Graph::getVisited() const
{
    return visited;
}

std::vector<std::vector<int>> Graph::getAdjacencyMatrix() const
{
    return adjacencyMatrix;
}

bool Graph::hasCycle()
{
    vector<bool> visited(numberOfVertices, false);
    vector<bool> recStack(numberOfVertices, false);
    vector<int> path;
    for (size_t i = 0; i < numberOfVertices; i++)
        if (isCyclicUtil(i, visited, recStack, path))
        {
            return true;
        }

    return false;
}

bool Graph::isEdge(size_t v, size_t w) const
{
    if (v < 0 || v >= adjacencyMatrix.size() || w < 0 || w >= adjacencyMatrix.size())
    {
        // v or w is not a valid vertex
        return false;
    }
    return adjacencyMatrix[v][w] != 0;
}

bool Graph::isCyclicUtil(size_t v, vector<bool> &visited, vector<bool> &recStack, vector<int> &path)
{
    visited[v] = true;
    recStack[v] = true;
    path.push_back(v);

    for (size_t i = 0; i < adjacencyMatrix[v].size(); i++)
    {
        if (adjacencyMatrix[v][i] != 0)
        {
            if (!visited[i])
            {
                if (isCyclicUtil(i, visited, recStack, path))
                    return true;
            }
            else if (recStack[i])
            {
                return true;
            }
        }
    }

    path.pop_back();
    recStack[v] = false;
    return false;
}
void Graph::printGraph() const
{
    std::cout << "Graph with " << numberOfVertices << " vertices and " << numberOfEdges << " edges." << std::endl;
}

void Graph::printCycle()
{
    std::vector<bool> visited(numberOfVertices, false);
    std::vector<bool> recStack(numberOfVertices, false);
    std::vector<int> path;

    for (size_t i = 0; i < numberOfVertices; i++)
    {
        if (!visited[i] && isCyclicUtil(i, visited, recStack, path))
        {
            if(path.size() < 3) {
                return;
            }
            cout << "The cycle is: ";
            for (size_t j = 0; j < path.size(); j++)
                cout << path[j] << "->";
            cout << path[0] << endl;
            return;
        }
        path.clear();
    }
}