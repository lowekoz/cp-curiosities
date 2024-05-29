/*
author: lowko527
about problem: Finds an eulerian path in directed graph if possible (visits every edge exactly once allowing for revisiting vertices)
time complexity: O(V)
mem complexity: O(V+E)
usage instruction: Graph class with constructor of graph size, along with function add edge to add connection between u,v
assumptions: Graph is 0-labeled

Additional Desc.:
Program works by first doing some sanity checks on graph, connected/mathmatical invariant to check fast if it is impossible.
Otherwise, the program record walks much like DFS, and while there is still unvisited nodes left after finishing a walk,
it records another walk. Lastly it joins all the walks together to form one eulerian path. i.e. if we have:
Walk1 : A-B-C
Walk2 : B-D-B
the join: A-B-D-B-C

*/


#ifndef TEMPLATE
#include<bits/stdc++.h>
using namespace std;

const char nl = '\n';
#define _ << " " <<
const int INF = INT_MAX;
// const int MOD = (int)1e9 + 7;
long long MOD = (long long)1e18;
#endif

template<typename T>
void prp(vector<pair<T, T>>& a) {
    for (auto& p : a) {
        cout << "{" << p.first << " " << p.second << "}" << " ";
    }
    cout << nl;
}


struct Graph {

    int vertexCount;
    vector<vector<int>> adj;
    vector<int> inDeg;
    vector<int> outDeg;

    vector<vector<int>> paths;
    vector<int> outCnt;

    map<int, int> sus;
    vector<int> output;


    Graph(int n) {
        vertexCount = n;
        inDeg.resize(n);
        outDeg.resize(n);
        adj.resize(n);
        outCnt.resize(n);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        outCnt[u]++;
        inDeg[v]++;
        outDeg[u]++;
    }

    // Starting from currNode, constructs a path stored in path param,
    // that walks until no adjacent nodes left. Conttinues to produce walks
    // of unvisited nodes until all out.
    void walk(int currNode, vector<int>& path) {
        path.push_back(currNode);

        if (!adj[currNode].empty()) {
            int nxt = adj[currNode].back();
            adj[currNode].pop_back();
            outCnt[currNode]--;

            walk(nxt, path);
        }
        else {
            paths.push_back(path);
        }

        while (!adj[currNode].empty()) {
            vector<int> nw = { currNode };
            int nxt = adj[currNode].back();
            adj[currNode].pop_back();
            outCnt[currNode]--;

            sus[currNode] = paths.size();
            walk(nxt, nw);
        }
    }

    // solve for eulerian path
    pair<int, int> solve() {
        auto p = possibleEulerian();
        if (p.first == -1) {
            return p;
        }
        else {
            vector<int> a;
            walk(p.first, a);
        }

        //for (int i = 0; i < vertexCount; i++) {
        //    while (outCnt[i] != 0) {
        //        vector<int> a;
        //        sus[i] = paths.size(); // !
        //        walk(i, a);
        //    }
        //}
        return p;
    }

    // reconstruction (join) of walks into one eulerian path
    // works by recursively traversing joined paths pushing answer to output
    void evalFrame(vector<int>& currentFrame) {

        for (auto el : currentFrame) {
            if (sus.count(el)) {
                int ix = sus[el];
                sus.erase(el);
                evalFrame(paths[ix]);
            }
            else {
                output.push_back(el);
                //cout << el << " ";
            }
        }
    }

    // returns -1,-1 if not possible, otherwise a valid start node and end node.
    pair<int, int> possibleEulerian() {
        bool allZero = true;
        int start = -1;
        int end = -1;
        for (int i = 0; i < vertexCount; i++) {
            int diff = inDeg[i] - outDeg[i];
            if (diff != 0) {
                if (abs(diff) > 1) {
                    return { -1,-1 };
                }
                allZero = false;
                if (diff == -1) {
                    if (start == -1)
                    {
                        start = i;
                    }
                    else {
                        return { -1,-1 };
                    }
                    continue;
                }
                if (diff == 1) {
                    if (end == -1)
                    {
                        end = i;
                    }
                    else {
                        return { -1,-1 };
                    }
                }
            }
        }
        if (allZero) {
            for (int i = 0; i < vertexCount; i++) {
                if (outDeg[i] > 0) {
                    return { i,i };
                }
            }
        }
        return { start,end };
    }
};


int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m;
    int u, v;
    while (cin >> n >> m) {
        if (n == 0 && m == 0) {
            break;
        }
        Graph G(n);
        for (int i = 0; i < m; i++) {
            cin >> u >> v;
            G.addEdge(u, v);
        }

        auto r = G.solve();
        if (G.paths.size() == 0) {
            cout << "Impossible" << nl;
        }
        else {
            G.evalFrame(G.paths[0]);
            if (G.output.size() != m + 1) {
                cout << "Impossible" << nl;
            }
            else {
                // handle clwon islands
                for (int e : G.output) {
                    cout << e << " ";
                }
                cout << nl;
            }
        }
    }
}

/*

3 3
0 1
1 0
1 2

3 3
1 2
0 1
1 0

5 4
0 1
1 2
2 0
3 4

5 5
0 1
1 2
2 0
3 4
4 3

5 6
0 1
1 2
2 0
3 4
4 3
3 0


4 3
1 2
2 3
3 1


7 8
0 1
1 2
2 3
3 1
1 4
4 5
1 6
6 1

5 6
0 1
0 2
1 3
2 3
2 4
3 4

4 5
0 1
1 2
2 3
3 0
0 2

5 6
0 1
1 2
2 3
3 4
4 2
2 0

5 6
0 1
1 2
2 0
2 3
3 4
4 2

6 7
0 1
1 2
2 0
2 3
3 4
4 2
0 5

2 3
0 1
1 0
0 1
*/