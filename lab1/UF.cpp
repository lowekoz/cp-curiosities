/*
author: lowko527
about problem: Implementation of well known Union Find (disjoint set union), uses size heuristic only when merging sets.
time complexity: Find O(logn), Merge O(logn)
mem complexity: O(n)
usage instruction: Create struct UF of size n, supports merge operation and find representative of set operation 
assumptions: 0 index parents
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


int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, q; cin >> n >> q;
    char c;
    int a, b;
    UF z(n);
    string out;
    for (int i = 0; i < q; i++) {
        cin >> c >> a >> b;
        if (c == '=') z.merge(a, b);
        else {
            out = z.get(a, b) ? "yes" : "no";
            cout << out << nl;
        }
    }
}