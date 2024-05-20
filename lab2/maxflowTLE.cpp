/*
author: lowko527 (inspiration from @WilliamFiset yt on Max Flow Ford Fulkerson)
about problem: Implementation of Max Flow through well known Ford Fulkerson algorithm DFS version
time complexity: O(Maxflow * E), worst case for augmenting DFS is proportional to maxflow value
mem complexity: O(V+E) adj 
usage instruction: Provided is a Folkersonsolver struct that constructs with src,sink and supports adding edges, and solving for max flow
assumptions: 
*/


#ifndef TEMPLATE
#include<bits/stdc++.h>
using namespace std;

const char nl = '\n';
#define _ << " " <<
#endif


class Edge {
public:
    int from, to;
    long flow = 0;
    long capacity;
    Edge* residual;

    Edge() {

    }

    Edge(int from, int to, int capacity) {
        this->from = from;
        this->to = to;
        this->capacity = capacity;
    }

    bool isResidual() {
        return this->capacity == 0;
    }

    long remainingCapacity() {
        return capacity - flow;
    }

    void augument(long bottleNeck) {
        flow += bottleNeck;
        (*residual).flow -= bottleNeck;
    }
};

class FordFulkersonDfsSolver {
public:
    static const long INF = LONG_MAX / 2;

    // number of nodes, source and sink node
    int n, s, t;

    int visitedToken = 1;
    vector<int> visited;

    long maxFlow = 0;

    vector<vector<Edge*>> graph;


    void addEdge(int from, int to, int capacity) {

        //Edge forward(); != Edge* forward = new Edge();
        Edge* forward = new Edge();
        Edge* backward = new Edge();
        forward->from = from;
        forward->to = to;
        forward->capacity = capacity;
        backward->from = to;
        backward->to = from;
        backward->capacity = 0;

        forward->residual = backward;
        backward->residual = forward;

        graph[from].push_back(forward);
        graph[to].push_back(backward);
    }

    /**
     * @brief Implements the Ford-Fulkerson algorithm using Depth-First Search (DFS) to find the maximum flow in a flow network.
     *
     * This function assumes that the flow network and its residual graph are already initialized.
     * It updates the flow values to find the maximum flow from the source to the sink.
     */
    void solve() {
        // finding all augmeting paths - initially bottleneck flow INF
        for (long f = dfs(s, INF); f != 0; f = dfs(s, INF)) {
            // next iter with dfs - when no paths left to be found returns 0
            visitedToken++;
            maxFlow += f;
        }
    }

    long dfs(int node, long flow) {
        // reached sink - actual path so return bottleneck flow found
        if (node == t) return flow;

        visited[node] = visitedToken; // avoid cycling


        for (Edge* e : graph[node]) {
            if (e->remainingCapacity() > 0 && visited[e->to] != visitedToken) {

                long bottleNeck = dfs(e->to, min(flow, e->remainingCapacity()));

                if (bottleNeck > 0) {
                    // if found path - traceback
                    e->augument(bottleNeck);
                    return bottleNeck;
                }
            }
        }

        return 0;
    }

    FordFulkersonDfsSolver(int n, int s, int t) {
        this->n = n;
        this->s = s;
        this->t = t;
        visited = vector<int>(n, 0);
        graph = vector<vector<Edge*>>(n); // 0 index
    }
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int a, b, w;
    int n, m, s, t; 
    cin >> n >> m >>s  >> t;

    FordFulkersonDfsSolver solver(n, s, t);
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> w;
        solver.addEdge(a, b, w);
	}

	solver.solve();
    vector<array<int, 3>> out;
    for (int from = 0; from < (int)solver.graph.size(); from++) {
        for (auto e : solver.graph[from]) {
            if (e->flow > 0) {
                out.push_back({ e->from,e->to,e->flow });
            }
        }
    }
    cout << n << " " << solver.maxFlow << " " << (int)out.size() << nl;
    for (auto& el : out) {
        cout << el[0] _ el[1] _ el[2] << nl;
    }
}

/*
2 1 0 1
0 1 5

4 5 0 3
0 1 10
1 2 1
1 3 1
0 2 1
2 3 10
*/