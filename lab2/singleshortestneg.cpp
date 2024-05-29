/*
author: lowko527
about problem: standard bellman ford algorithm, with only one source compute all dst.
time complexity: O(V*E)
mem complexity: O(V*E)
usage instruction: provdies function bellmanFord, see desc
assumptions:
*/


#ifndef TEMPLATE
#include<bits/stdc++.h>
using namespace std;

const char nl = '\n';
#define _ << " " <<
const int INF = INT_MAX;
#endif

template<typename T>
void prp(vector<pair<T, T>>& a) {
    for (auto& p : a) {
        cout << "{" << p.first << " " << p.second << "}" << " ";
    }
    cout << nl;
}


struct Edge {
    int source, destination, weight;
};


/**
 * @brief Computes the shortest paths from a single source node to all other nodes in a directed graph using the Bellman-Ford algorithm.
 *
 * This function calculates the shortest paths from the given source node to all other nodes in the graph. It handles negative weights and detects negative cycles.
 *
 * @param n The number of nodes in the graph.
 * @param edges A vector of Edge structures representing the edges in the graph.
 *              - Each Edge structure contains three integers: source, destination, and weight.
 *              - `edges[i].source` and `edges[i].destination` represent the endpoints of the i-th edge.
 *              - `edges[i].weight` represents the weight of the i-th edge.
 * @param source The source node from which the shortest paths are calculated.
 * @param dist A reference to a vector that will store the shortest distances from the source node to all other nodes.
 *             - After the function executes, `dist[i]` will contain the shortest distance from the source node to node i.
 *             - If there is no path from the source node to node i, `dist[i]` will be INF.
 *             - If there is a negative weight cycle that is reachable from the source node and affects the path to node i, `dist[i]` will be NEG_INF.
 * @return returns a vector of all nodes with -inf reachable
 */
vector<bool> bellmanFord(int n, const vector<Edge>& edges, int source, vector<int>& dist) {
    dist.assign(n, INF); dist[source] = 0;

    for (int i = 1; i < n; ++i) {
        for (const auto& edge : edges) {
            int u = edge.source; int v = edge.destination; int weight = edge.weight;
            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }
    queue<int> bfsq;
    
    // neg cyclss last iter
    for (const auto& edge : edges) {
        int u = edge.source;int v = edge.destination;int weight = edge.weight;
        if (dist[u] != INF && dist[u] + weight < dist[v]) {
            //dist[v] = -INF;
            { bfsq.push(v); }
        }
    }


    vector<bool> negInfPropagation(n, false);
    while (!bfsq.empty()) {
        int u = bfsq.front();bfsq.pop();
        negInfPropagation[u] = true;
        for (auto& e : edges) {
            if (e.source == u) { 
                if (!negInfPropagation[e.destination]) {
                    bfsq.push(e.destination);
                }
            }
        }
    }
    return negInfPropagation;
}


int main() {
    cin.tie(0); ios_base::sync_with_stdio(0);
    int n, m, q,s;
    int u, v, w;
    int tc = 0;
    while (cin >> n >> m >> q >> s && !(n == 0 && m == 0 && q == 0 && s==0)) {
    
        /*if (tc > 0) {
            cout << nl;
        }
        tc++;*/

        vector<Edge> edges;
        for (int i = 0; i < m; i++) {
            cin >> u >> v >> w;
            Edge e{ u,v,w };
            edges.push_back(e);
        }

        vector<int> dist;
        auto ffs = bellmanFord(n, edges, s, dist);

        for (int i = 0; i < q; i++) {
            cin >> v;
            if (ffs[v]) {
                cout << "-Infinity" << nl;
            }
            else if (dist[v] == INF) cout << "Impossible" << nl;
            else cout << dist[v] << nl;
        }

        
    }

}

/*

5 4 3 0
0 1 999
1 2 -2
2 1 1
0 3 2
1
0
4
2 1 1 0
0 1 -100
1
0 0 0 0

*/

