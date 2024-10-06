/**
 * File: Graph.cpp
 * Description: Implementation of the Graph class.
 */

#include <stack>
#include <algorithm>
#include <numeric>

#include "graph.hpp"

void Graph::DFS(size_t v, vector<bool>& visited) {
    visited[v] = true;
    for (size_t i = 0; i < vertices; ++i) {
        if (adjMatrix[v][i] && !visited[i]) {
            DFS(i, visited);
        }
    }
}

bool Graph::isEulerian() {
    // Check if all non-zero degree vertices are connected
    vector<bool> visited(vertices, false);
    size_t nonZeroDegreeVertex = vertices;  // Initialize to an invalid vertex index
    for (size_t i = 0; i < vertices; ++i) {
        if (count(adjMatrix[i].begin(), adjMatrix[i].end(), true) > 0) {
            nonZeroDegreeVertex = i;
            break;
        }
    }
    if (nonZeroDegreeVertex == vertices) return false;  // No non-zero degree vertex found

    DFS(nonZeroDegreeVertex, visited);

    for (size_t i = 0; i < vertices; ++i) {
        if (count(adjMatrix[i].begin(), adjMatrix[i].end(), true) > 0 && !visited[i]) {
            return false;
        }
    }

    // Check if all vertices have even degree (the euler circuit condition)
    for (size_t i = 0; i < vertices; ++i) {
        if (count(adjMatrix[i].begin(), adjMatrix[i].end(), true) > 0 && count(adjMatrix[i].begin(), adjMatrix[i].end(), true) % 2 != 0) {
            return false;
        }
    }

    return true;
}

Graph::Graph(size_t vertices) : vertices(vertices), adjMatrix(vertices, vector<bool>(vertices, false)) {}

bool Graph::addEdge(size_t u, size_t v) {
    // if the vertices are out of bounds or are the same, return false
    if (u >= vertices || v >= vertices || u == v) return false;
    adjMatrix[u][v] = true;
    adjMatrix[v][u] = true;
    return true;
}

const vector<vector<bool>>& Graph::getAdjMatrix() const {
    return adjMatrix;
}

/**
 * this function finds an Eulerian circuit in the graph.
 * the logic is: 
 * 1. start from any vertex and keep moving to adjacent vertices and removing the edges between them.
 * 2. if there are no adjacent vertices left, add the current vertex to the circuit and backtrack to the previous vertex.
 * 3. repeat the process until all edges are removed.
 */
vector<size_t> Graph::findEulerianCircuit() {
    if (!isEulerian()) return {};

    vector<size_t> circuit;  // represents the Eulerian circuit
    stack<size_t> currentPath;  // represents the current path
    vector<vector<bool>> tempAdjMatrix = adjMatrix;  // a deep copy of the adjacency matrix to a new vector of vectors

    currentPath.push(0);
    size_t currentVertex = 0;

    while (!currentPath.empty()) {
        // if there are no adjacent vertices left:
        if (count(tempAdjMatrix[currentVertex].begin(), tempAdjMatrix[currentVertex].end(), true) == 0) {
            // add the current vertex to the circuit and backtrack to the previous vertex
            circuit.push_back(currentVertex);
            currentVertex = currentPath.top();
            currentPath.pop();
        } else {
            for (size_t nextVertex = 0; nextVertex < vertices; ++nextVertex) {
                // if there is an edge between the current vertex and the next vertex:
                if (tempAdjMatrix[currentVertex][nextVertex]) {
                    currentPath.push(currentVertex);  // push the current vertex to the current path
                    tempAdjMatrix[currentVertex][nextVertex] = false;  // remove the edge between the current vertex and the next vertex
                    tempAdjMatrix[nextVertex][currentVertex] = false;
                    currentVertex = nextVertex;  // move to the next vertex
                    break;
                }
            }
        }
    }

    return circuit;
}