#ifndef ARIEL_GRAPH_HPP
#define ARIEL_GRAPH_HPP

#include <vector>
#include <cstddef>
#include <iostream>

namespace ariel
{
    class Graph
    {
    private:
        std::vector<std::vector<int>> adjacencyMatrix;
        std::vector<bool> recStack;
        std::vector<bool> visited;
        bool isDirected;
        bool isWeighted;
        bool isCyclic;
        size_t numberOfEdges;
        size_t numberOfVertices;

    public:
        Graph()
        {
            isDirected = false;
            isWeighted = false;
            isCyclic = false;
            numberOfEdges = 0;
            numberOfVertices = 0;
        }
        std::vector<bool> getVisited() const;
        std::vector<std::vector<int>> getAdjacencyMatrix() const;
        bool isEdge(size_t v, size_t w) const;
        void printGraph() const;
        bool getIsCyclic();

        std::vector<int> getAd(size_t v);
        void loadGraph(const std::vector<std::vector<int>> &matrix);

        bool hasCycle();
        bool isCyclicUtil(size_t v, std::vector<bool> &visited, std::vector<bool> &recStack, std::vector<int> &path);
        void printCycle();
        size_t getVertices();
        size_t getNumEdges();

        friend std::ostream &operator<<(std::ostream &os, const Graph &graph)
        {
            for (size_t i = 0; i < graph.adjacencyMatrix.size(); i++)
            {
                os << "[";
                for (size_t j = 0; j < graph.adjacencyMatrix[i].size(); j++)
                {
                    os << graph.adjacencyMatrix[i][j];
                    if (j != graph.adjacencyMatrix[i].size() - 1)
                    {
                        os << ", ";
                    }
                }
                os << "]";
                if (i != graph.adjacencyMatrix.size() - 1)
                {
                    os << ", ";
                }
            }
            os << "\n";
            return os;
        }
        Graph operator+(const Graph &other)
        {
            // Check if the two graphs have the same number of vertices
            if (this->numberOfVertices != other.numberOfVertices)
            {
                throw std::invalid_argument("Graphs must have the same number of vertices to be added together");
            }

            Graph result;
            result.adjacencyMatrix.resize(this->numberOfVertices, std::vector<int>(this->numberOfVertices, 0));

            for (size_t i = 0; i < this->numberOfVertices; i++)
            {
                for (size_t j = 0; j < this->numberOfVertices; j++)
                {
                    result.adjacencyMatrix[i][j] = this->adjacencyMatrix[i][j] + other.adjacencyMatrix[i][j];
                }
            }

            // Update the properties of the resulting graph
            result.numberOfVertices = this->numberOfVertices;
            result.numberOfEdges = this->numberOfEdges + other.numberOfEdges;
            result.isDirected = this->isDirected || other.isDirected;
            result.isWeighted = this->isWeighted || other.isWeighted;
            result.isCyclic = this->isCyclic || other.isCyclic;

            return result;
        }
        // Addition assignment operator
        Graph &operator+=(const Graph &other)
        {
            // Check if the two graphs have the same number of vertices
            if (this->numberOfVertices != other.numberOfVertices)
            {
                throw std::invalid_argument("Graphs must have the same number of vertices to be added together");
            }

            for (size_t i = 0; i < this->numberOfVertices; i++)
            {
                for (size_t j = 0; j < this->numberOfVertices; j++)
                {
                    this->adjacencyMatrix[i][j] += other.adjacencyMatrix[i][j];
                }
            }

            // Update the properties of the graph
            this->numberOfEdges += other.numberOfEdges;
            this->isDirected = this->isDirected || other.isDirected;
            this->isWeighted = this->isWeighted || other.isWeighted;
            this->isCyclic = this->isCyclic || other.isCyclic;

            return *this;
        }

        // Unary plus operator
        Graph operator+() const
        {
            // The unary plus operator doesn't change the graph, so just return a copy of it
            return *this;
        }

        // Binary subtraction operator
        Graph operator-(const Graph &other)
        {
            // Check if the two graphs have the same number of vertices
            if (this->numberOfVertices != other.numberOfVertices)
            {
                throw std::invalid_argument("Graphs must have the same number of vertices to be subtracted");
            }

            Graph result;
            result.adjacencyMatrix.resize(this->numberOfVertices, std::vector<int>(this->numberOfVertices, 0));

            for (size_t i = 0; i < this->numberOfVertices; i++)
            {
                for (size_t j = 0; j < this->numberOfVertices; j++)
                {
                    result.adjacencyMatrix[i][j] = this->adjacencyMatrix[i][j] - other.adjacencyMatrix[i][j];
                }
            }

            // Update the properties of the resulting graph
            result.numberOfVertices = this->numberOfVertices;
            result.numberOfEdges = this->numberOfEdges - other.numberOfEdges;
            result.isDirected = this->isDirected && other.isDirected;
            result.isWeighted = this->isWeighted && other.isWeighted;
            result.isCyclic = this->isCyclic && other.isCyclic;

            return result;
        }

        // Subtraction assignment operator
        Graph &operator-=(const Graph &other)
        {
            // Check if the two graphs have the same number of vertices
            if (this->numberOfVertices != other.numberOfVertices)
            {
                throw std::invalid_argument("Graphs must have the same number of vertices to be subtracted");
            }

            for (size_t i = 0; i < this->numberOfVertices; i++)
            {
                for (size_t j = 0; j < this->numberOfVertices; j++)
                {
                    this->adjacencyMatrix[i][j] -= other.adjacencyMatrix[i][j];
                }
            }

            // Update the properties of the graph
            this->numberOfEdges -= other.numberOfEdges;
            this->isDirected = this->isDirected && other.isDirected;
            this->isWeighted = this->isWeighted && other.isWeighted;
            this->isCyclic = this->isCyclic && other.isCyclic;

            return *this;
        }

        // Unary minus operator
        Graph operator-() const
        {
            Graph result = *this;
            for (size_t i = 0; i < this->numberOfVertices; i++)
            {
                for (size_t j = 0; j < this->numberOfVertices; j++)
                {
                    result.adjacencyMatrix[i][j] = -result.adjacencyMatrix[i][j];
                }
            }
            return result;
        }
        bool operator==(const Graph &other) const
        {
            return this->adjacencyMatrix == other.adjacencyMatrix;
        }

        bool operator!=(const Graph &other) const
        {
            return !(*this == other);
        }

        // Multiplication assignment operator
        Graph &operator*=(int scalar)
        {
            for (auto &row : this->adjacencyMatrix)
            {
                for (auto &weight : row)
                {
                    weight *= scalar;
                }
            }
            return *this;
        }

        // Division assignment operator
        Graph &operator/=(int scalar)
        {
            if (scalar == 0)
            {
                throw std::invalid_argument("Division by zero is not allowed");
            }

            for (auto &row : this->adjacencyMatrix)
            {
                for (auto &weight : row)
                {
                    weight /= scalar;
                }
            }
            return *this;
        }

        bool operator<(const Graph &other) const
        {
            if (this->numberOfEdges < other.numberOfEdges)
                return true;
            if (this->numberOfEdges > other.numberOfEdges)
                return false;
            return this->numberOfVertices < other.numberOfVertices;
        }

        bool operator>(const Graph &other) const
        {
            return other < *this;
        }

        bool operator<=(const Graph &other) const
        {
            return !(*this > other);
        }

        bool operator>=(const Graph &other) const
        {
            return !(*this < other);
        }
        // Prefix increment operator
        Graph &operator++()
        {
            for (auto &row : this->adjacencyMatrix)
            {
                for (auto &weight : row)
                {
                    ++weight;
                }
            }
            return *this;
        }

        // Prefix decrement operator
        Graph &operator--()
        {
            for (auto &row : this->adjacencyMatrix)
            {
                for (auto &weight : row)
                {
                    --weight;
                }
            }
            return *this;
        }

        // Postfix increment operator
        Graph operator++(int)
        {
            Graph temp = *this;
            ++*this;
            return temp;
        }

        // Postfix decrement operator
        Graph operator--(int)
        {
            Graph temp = *this;
            --*this;
            return temp;
        }
        // Multiplication by an integer scalar
        Graph operator*(int scalar)
        {
            Graph result = *this;
            for (auto &row : result.adjacencyMatrix)
            {
                for (auto &weight : row)
                {
                    weight *= scalar;
                }
            }
            return result;
        }

        // Multiplication of two graphs
        Graph operator*(const Graph &other)
        {
            // Check if the two graphs have the same number of vertices
            if (this->numberOfVertices != other.numberOfVertices)
            {
                throw std::invalid_argument("Graphs must have the same number of vertices to be multiplied");
            }

            Graph result;
            result.adjacencyMatrix.resize(this->numberOfVertices, std::vector<int>(this->numberOfVertices, 0));

            for (size_t i = 0; i < this->numberOfVertices; i++)
            {
                for (size_t j = 0; j < this->numberOfVertices; j++)
                {
                    for (size_t k = 0; k < this->numberOfVertices; k++)
                    {
                        result.adjacencyMatrix[i][j] += this->adjacencyMatrix[i][k] * other.adjacencyMatrix[k][j];
                    }
                }
            }

            // Update the properties of the resulting graph
            result.numberOfVertices = this->numberOfVertices;
            result.numberOfEdges = this->numberOfEdges * other.numberOfEdges;
            result.isDirected = this->isDirected || other.isDirected;
            result.isWeighted = this->isWeighted || other.isWeighted;
            result.isCyclic = this->isCyclic || other.isCyclic;

            return result;
        }
    };
}

#endif