/*
author: lowko527
about problem: standard all pairs shortest path with floyd warshall
time complexity: O(N cube)
mem complexity: O(N square)
usage instruction: provdies function floydWarshall to solve, see desc
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


/**
 * @brief APSP Computes the shortest paths between all pairs of vertices in a given weighted directed graph using the Floyd-Warshall algorithm.
 *
 * This function updates the `ans` matrix to contain the shortest path distances between every pair of vertices in the graph.
 * It handles graphs with negative weights and detects negative cycles.
 *
 * @param n The number of vertices in the graph.
 * @param graph A reference to a 2D vector representing the adjacency matrix of the graph.
 *              - `graph[i][j]` contains the weight of the edge from vertex `i` to vertex `j`.
 *              - If there is no edge between vertices `i` and `j`, `graph[i][j]` should be `INF`.
 *              - The diagonal elements `graph[i][i]` should be 0, as the distance from any vertex to itself is zero.
 * @param ans A reference to a 2D vector that will be updated to contain the shortest path distances between all pairs of vertices.
 */
vector<vector<int>> floydWarshall(int n, vector<vector<int>>& graph) {
    vector<vector<int>> ans = graph;
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (ans[i][k] != INF && ans[k][j] != INF && ans[i][k] + ans[k][j] < ans[i][j]) {
                    ans[i][j] = ans[i][k] + ans[k][j];
                }
            }
        }
    }
    // negative cycles re?
    for (int k = 0; k < n; ++k) {
        if (ans[k][k] < 0) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (ans[i][k] != INF && ans[k][j] != INF) {
                        ans[i][j] = -INF;
                    }
                }
            }
        }
    }

    return ans;
}


int main() {
    cin.tie(0); ios_base::sync_with_stdio(0);
    int n, m, q;
    int u, v, w;
    int tc = 0;
    while (cin >> n >> m >> q && !(n == 0 && m == 0 && q == 0)) {
    
        if (tc > 0) {
            cout << nl;
        }
        tc++;
        vector<vector<int>> graph(n, vector<int>(n, INF));
        for (int i = 0; i < n; i++) {
            graph[i][i] = 0;
        }
        for (int i = 0; i < m; i++) {
            cin >> u >> v >> w;
            graph[u][v] = graph[u][v] < w ? graph[u][v] : w;
        }

        // solev
        auto ans = floydWarshall(n, graph);
        for (int i = 0; i < q; i++) {
            cin >> u >> v;
            int r = ans[u][v];
            if (r == -INF) cout << "-Infinity" << nl;
            else if (r == INF) cout << "Impossible" << nl;
            else cout << r << nl;
        }
    }

}

/*
overwrite it :xx each time.
*/

