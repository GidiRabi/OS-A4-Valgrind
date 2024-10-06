/**
 * File: main.cpp
 * Description: Main file for the Eulerian circuit finder program.
 */
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <getopt.h>
#include <algorithm>
#include <numeric>

#include "graph.hpp"

using namespace std;

/**
 * Utility function to check if a string is a number.
 * actually check is the string is positive integer.
 */
bool isNumber(const string& str) {
    return !str.empty() && all_of(str.begin(), str.end(), ::isdigit);
}

/**
 * Main function to find an Eulerian circuit in a random graph.
 */
int main(int argc, char* argv[]) {
    int opt;
    size_t numEdges = 0;
    size_t numVertices = 0;
    unsigned int seed = 0;

    // Parse command line arguments: -e numEdges -v numVertices -s seed
    while ((opt = getopt(argc, argv, "e:v:s:")) != -1) {
        switch (opt) {
            case 'e':
                if (isNumber(optarg)) {
                    numEdges = stoul(optarg);
                } else {
                    cerr << "Invalid number of edges." << endl;
                    return 1;
                }
                break;
            case 'v':
                if (isNumber(optarg)) {
                    numVertices = stoul(optarg);
             
                } else {
                    cerr << "Invalid number of vertices." << endl;
                    return 1;
                }
                break;
            case 's':
                if (isNumber(optarg)) {
                    seed = stoul(optarg);
                } else {
                    cerr << "Invalid seed." << endl;
                    return 1;
                }
                break;
            default:
                cerr << "Usage: " << argv[0] << " -e numEdges -v numVertices -s seed" << endl;
                return 1;
        }
    }

    if (numEdges == 0 || numVertices == 0) {  // Check if the number of edges and vertices are valid
        cerr << "Number of edges and vertices must be greater than 0." << endl;
        return 1;
    }

    if (numEdges > numVertices * (numVertices - 1) / 2) {  // Check if the number of edges is valid
        cerr << "Too many edges for the given number of vertices." << endl;
        return 1;
    }

    srand(seed);  // Seed the random number generator

    Graph graph(numVertices);

    // Add random edges to the graph until the number of edges is reached
    size_t edgesAdded = 0;
    while (edgesAdded < numEdges) {
        size_t u = (size_t) rand() % numVertices;  // Randomly select first vertex
        size_t v = (size_t) rand() % numVertices;  // Randomly select second vertex
        if (u != v && !graph.getAdjMatrix()[u][v]) {  // If the vertices are different and the edge doesn't already exist
            graph.addEdge(u, v);
            edgesAdded++;
        }
    }

    // Print the eulerian circuit:
    vector<size_t> eulerianCircuit = graph.findEulerianCircuit();
    if (eulerianCircuit.empty()) {
        cout << "No Eulerian circuit found." << endl;
    } else {
        cout << "Eulerian circuit: ";
        for (size_t vertex : eulerianCircuit) {
            cout << vertex << " ";
        }
        cout << endl;
    }

    return 0;
}