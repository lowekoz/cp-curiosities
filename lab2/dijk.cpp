/*
author: lowko527
about problem: Implementation of Dijkstras algorithm to solve single source shortes path non neg using Binary Priority Queue
time complexity: O((V+E)logV)
mem complexity: O(V+E)
usage instruction: Provided is a Dijkstra stuct that supports adding edges, setting src and solving the shortest path, see func solve
assumptions: non-negative values.
*/


#ifndef TEMPLATE
#include<bits/stdc++.h>
using namespace std;

const char nl = '\n';
#endif


struct Dijkstra {
	int n; // num of nodes
	vector<vector<pair<int, int>>> adjList; // [from] -> {{w, to}, ...}
	vector<int> prev;
	vector<int> dist; // distance to node[idx] from src
	
	Dijkstra(int n) {
		this->n = n;
		this->dist = vector<int>(n, INT32_MAX);
		this->prev = vector<int>(n, -1);
		this->adjList = vector<vector<pair<int, int>>>(n);
	}

	void addEdge(int from, int to, int weight) {
		this->adjList[from].push_back({ weight,to });
	}

	/**
	 * @brief Computes the shortest path distances from a given source node to all other nodes in the graph using a lazy version of Dijkstra's algorithm.
	 *
	 * @param src The source node from which the shortest path distances are calculated.
	 */
	void solve(int src) {
		vector<bool> vis(n, 0);
		this->dist[src] = 0;
		// dont want deafult.first comparator in heap, want min_heap hence specify comparator
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;
		pq.push({ 0,src }); // init
		while (!pq.empty()) {
			pair<int, int> current = pq.top();
			pq.pop();
			//{minVal (accumlative), at}
			int minVal = current.first;
			int at = current.second;
			vis[at] = true;
			if (dist[at] < minVal) continue;
			for (auto& nxt : adjList[at]) {
				if (vis[nxt.second]) continue;
				int newDist = dist[at] + nxt.first; // potential candidate
				if (newDist < dist[nxt.second]) { // found better alt.
					prev[nxt.second] = at;
					dist[nxt.second] = newDist;
					pq.push({ newDist,nxt.second });
				}
			}
		}
	}

	// reconstructPath takes the goal and constructs the path to get there
	vector<int> reconstructPath(int goal) {
		vector<int> path;
		path.push_back(goal);
		int tmp = goal;
		while (prev[tmp] != -1) {
			tmp = prev[tmp];
			path.push_back(tmp);
		}
		reverse(path.begin(), path.end());
		return path;

	}

	// getDist returns the distance to node after solved
	int getDist(int targetNode) {
		return dist[targetNode];
	}
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int a, b, w;
    int n, m, s, q; 
    while (cin >> n >> m >> q >> s && !(n == 0 && m == 0 && q == 0 && s == 0)) {
		Dijkstra obj(n);
        for (int i = 0; i < m; i++) {
            cin >> a >> b >> w;
			obj.addEdge(a, b, w);
        
		}

		obj.solve(s);
		int qm;
		for (int i = 0; i < q; i++) {
			cin >> qm;
			int r = obj.getDist(qm);
			if (r == INT32_MAX) {
				cout << "Impossible" << nl;
			}
			else {
				cout << r << nl;
			}
		}
    }
}