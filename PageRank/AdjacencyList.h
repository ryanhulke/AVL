#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <cstdio>
using namespace std; 

class AdjacencyList {
    unordered_map<string, vector<string>> adjList;
    public:
        void AddEdge(string from, string to){
            // if the key doesn't exist, create it
            if (adjList.find(from) == adjList.end()) {
                adjList[from] = vector<string>();
            }
            // if the key doesn't exist, create it
            if (adjList.find(to) == adjList.end()) {
                adjList[to] = vector<string>();
            }
            adjList[from].push_back(to);
        };
        void PageRank(int powerIterations){
            int numURLs = adjList.size();
            double initialPageRank = 1.0 / numURLs;
            unordered_map<string, double> ranks;
            // initialize ranks
            for (auto it = adjList.begin(); it != adjList.end(); it++) {
                ranks[it->first] = initialPageRank;
            }
            // power iterations
            while (--powerIterations > 0) {
                unordered_map<string, double> newRanks;
                for (auto it = adjList.begin(); it != adjList.end(); it++) {
                    if (newRanks.find(it->first) == newRanks.end()) {
                        newRanks[it->first] = 0.0;
                    }
                    for (auto neighbor : it->second) {
                       newRanks[neighbor] += (1.0 / it->second.size())*ranks[it->first];
                    }
                }
                ranks = newRanks;
                newRanks.clear();
            }
            // convert hashmap to vector of pairs and sort
            vector<pair<string, double>> elems(ranks.begin(), ranks.end());
            sort(elems.begin(), elems.end());
            for (auto it = elems.begin(); it != elems.end(); it++) {
                cout << it->first << " ";
                fprintf(stdout, "%.2f", it->second);
                cout << endl;
            }
        }; 
};