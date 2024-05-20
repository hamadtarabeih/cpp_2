# cpp_2

﻿# Graph Class

This class represents a Graph data structure in C++. It supports both directed and undirected graphs, with or without weights. The graph is represented internally using an adjacency matrix.

## Class Methods

### Overloaded Operators

The class overloads several operators to provide intuitive operations on graphs.

- `<<` : Outputs the adjacency matrix of the graph.
- `+` : Adds two graphs together. The graphs must have the same number of vertices. The resulting graph's adjacency matrix is the element-wise sum of the two input graphs' adjacency matrices.
- `+=` : Adds another graph to the current graph. The graphs must have the same number of vertices.
- `+` (unary) : Returns a copy of the current graph.
- `-` : Subtracts another graph from the current graph. The graphs must have the same number of vertices. The resulting graph's adjacency matrix is the element-wise difference of the two input graphs' adjacency matrices.
- `-=` : Subtracts another graph from the current graph. The graphs must have the same number of vertices.
- `-` (unary) : Returns a new graph with all weights negated.
- `==` : Checks if two graphs are equal by comparing their adjacency matrices.
- `!=` : Checks if two graphs are not equal.
- `*=` : Multiplies all weights in the graph by a scalar.
- `/=` : Divides all weights in the graph by a scalar. Division by zero is not allowed.
- `<`, `>`, `<=`, `>=` : Compares two graphs based on the number of edges and vertices.
- `++` (prefix and postfix) : Increments all weights in the graph.
- `--` (prefix and postfix) : Decrements all weights in the graph.
- `*` : Multiplies all weights in the graph by a scalar or performs matrix multiplication if another graph is provided. The graphs must have the same number of vertices for matrix multiplication.

## Exceptions

The class throws `std::invalid_argument` exceptions when attempting to perform operations on graphs with different numbers of vertices or when attempting to divide by zero.

## Properties

The class maintains several properties about the graph:

- `numberOfVertices` : The number of vertices in the graph.
- `numberOfEdges` : The number of edges in the graph.
- `isDirected` : Whether the graph is directed.
- `isWeighted` : Whether the graph is weighted.
- `isCyclic` : Whether the graph contains cycles.

