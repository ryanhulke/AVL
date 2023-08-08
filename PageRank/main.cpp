#include "AdjacencyList.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main () {
    int numLines, powerIterations;
    string from, to;
    cin >> numLines >> powerIterations;
    AdjacencyList adjList;
    for (int i = 0; i < numLines; i++) {
        cin >> from >> to;
        adjList.AddEdge(from, to);
    }
    adjList.PageRank(powerIterations);
}