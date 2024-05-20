/*
author: lowko527
about problem: Implementation of Minimum Spanning Tree from DSU greedily always appending the lowest cost edges not already in set.
time complexity: O(ElogE) (E as in edges, var "m" in code)
mem complexity: O(V+E)
usage instruction: See findMinSpanningTree function
assumptions: findMinSpanningTree assumes presorted arr of edges and dependency on UF structure, also assumes that nodes are labeld 0..n-1
*/


#ifndef TEMPLATE
#include<bits/stdc++.h>
using namespace std;

const char nl = '\n';
#endif

struct UF {

    vector<int> component_size;
    vector<int> repr;
    vector<pair<int, int>> additionalInfo; //self is max and min initially

    UF(int number_of_elements) {
        for (int i = 0; i < number_of_elements; i++) {
            repr.push_back(i);
            component_size.push_back(1);
            additionalInfo.push_back({ i,i });
        }
    }

    int size(int a) {
        a = find(a);
        return component_size[a];
    }

    int find(int a) {
        if (repr[a] == a) {
            return a;
        }
        repr[a] = find(repr[a]);
        return repr[a];
    }

    void merge(int gravity, int pebble) {
        gravity = find(gravity);
        pebble = find(pebble);

        if (gravity == pebble) {
            return;
        }

        // heuristic
        if (component_size[pebble] > component_size[gravity]) {
            swap(pebble, gravity);
        }

        repr[pebble] = gravity;
        component_size[gravity] += component_size[pebble];
        component_size[pebble] = 0;

        //additional info - [min,max]
        //additionalInfo[gravity].first = min(additionalInfo[gravity].first, additionalInfo[pebble].first);
        //additionalInfo[gravity].second = max(additionalInfo[gravity].second, additionalInfo[pebble].second);
        return;
    }

    int count_islands() {
        /*count number of disjoint components by counting number of non-zero sizes.*/
        int count = 0;
        for (auto el : component_size) {
            if (el > 0) {
                count += 1;
            }
        }
        return count;
    }

    bool get(int u, int v) {
        /*check if two elements u and v belong to the same set.*/
        u = find(u);
        v = find(v);
        if (u == v) {
            return true;
        }
        return false;
    }
};

/**
 * @brief Finds the minimum spanning tree (MST) of a graph using Kruskal's algorithm.
 *
 * @param n The number of vertices in the graph.
 * @param edges A reference to a vector of edges, where each edge is represented by an array of three integers: {u, v, w}.
 *              Here, 'u' and 'v' are the vertices connected by the edge, and 'w' is the weight of the edge.
 * @return A pair consisting of:
 *         - The total weight of the minimum spanning tree.
 *         - A vector of pairs, where each pair represents an edge in the MST with the format (u, v).
 */
pair<int,vector<pair<int,int>>> findMinSpanningTree(int n, vector<array<int,3>> &edges) {
    UF z(n);
    int wcost = 0;
    vector<pair<int, int>> eres;
    for (auto& e : edges) {
        if (!(z.get(e[2], e[1]))) {
            z.merge(e[2], e[1]);
            wcost += e[0];
            eres.push_back({ min(e[2],e[1]), max(e[2],e[1]) });
        }
    }

    if (eres.size() != n - 1) {
        return { -1,eres };
    }
    else {
        return { wcost,eres };
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int a, b, w;
    int n, m; 
    while (cin >> n >> m && !(n == 0 && m == 0)) {
        vector<array<int, 3>> v(m);
        for (int i = 0; i < m; i++) {
            cin >> a >> b >> w;
            v[i] ={ w,a,b };
        }
        sort(v.begin(), v.end());

        auto res = findMinSpanningTree(n, v);

        if (res.first == -1){
            cout << "Impossible" << nl;
        }
        else {
            sort(res.second.begin(), res.second.end());
            cout << res.first << nl;
            for (auto& e : res.second) {
                cout << e.first << " " << e.second << nl;
            }
        }
    }
}