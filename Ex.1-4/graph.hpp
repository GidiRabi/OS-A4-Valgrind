/**
 * File: Graph.hpp
 * Description: Declaration of the Graph class.
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <stddef.h>

using namespace std;

/**
 * Graph class.
 * represents an undirected graph with the given number of vertices.
 * Can find an Eulerian circuit in the graph.
 */
class Graph {
    private:
        size_t vertices;  // Number of vertices in the graph
        vector<vector<bool>> adjMatrix;  // Adjacency matrix of the graph
        void DFS(size_t v, vector<bool>& visited);  // Depth-first search from vertex v
        bool isEulerian();  // Check if the graph is Eulerian
        
    public:
        Graph(size_t vertices);  // Constructor
        bool addEdge(size_t u, size_t v);  // Add an edge between vertices u and v
        const vector<vector<bool>>& getAdjMatrix() const;  // Get the adjacency matrix of the graph
        vector<size_t> findEulerianCircuit();  // Find an Eulerian circuit in the graph
};

#endif // GRAPH_HPP