/*
author: lowko527 
about problem: Interval cover, greedy implementation from left to right
time complexity: O(nlogn), as impl does not assume presorted intervals
mem complexity: O(n) 
usage instruction: provides coverInterval function, see desc.
assumptions: 
*/


#ifndef TEMPLATE
#include<bits/stdc++.h>
using namespace std;

const char nl = '\n';
#define _ << " " <<
#endif

template<typename T>
void prp(vector<pair<T,T>>& a) {
    for (auto &p : a) {
        cout << "{" << p.first << " " << p.second << "}" << " ";
    }
    cout << nl;
}


/**
 * @brief Finds a minimum set of intervals that covers a given range.
 *
 * Given a set of intervals represented as pairs of start and end points, this function
 * finds a minimum subset of intervals that completely covers the specified range
 * [start, end].
 *
 * @tparam T The data type of the interval endpoints.
 * @param v A vector of pairs representing intervals, where each pair contains the start
 *          and end points of an interval.
 * @param start The start point of the range to be covered.
 * @param end The end point of the range to be covered.
 * @return A vector of pairs representing the minimum set of intervals that covers the range
 *         [start, end].
 */
template<typename T>
vector<pair<T,T>> coverInterval(vector<pair<T, T>> v, T& start, T& end) {

    sort(v.begin(), v.end());
    T boundry_nxt = start;
    pair<T, T> best = v[0];
    vector<pair<T, T>> resIntervals;
    v.push_back({ INT32_MAX,INT32_MAX }); // dummy
    
    for (int i = 0; i < (int)v.size() - 1; i++) {

        //gap in cover thus impossible
        if (v[i].first > boundry_nxt) {
            return {};
        }

        //covers longer distance
        if (v[i].second > best.second) {
            best = v[i];
        }

        //check if done
        if (best.second >= end) {
            resIntervals.push_back(best);
            return resIntervals;
        }

        //nxt boundry
        if (v[i + 1].first > boundry_nxt) {
            boundry_nxt = best.second;
            resIntervals.push_back(best);
        }
    }

    return {}; //if didnt make it all the way but continuous seg
}



int main() {
    cin.tie(0); ios_base::sync_with_stdio(0);
    long double A, B;
    while (cin >> A >> B) {
        vector<pair<long double, long double>> intervals;
        int n; cin >> n;
        long double x, y;
        map<pair<long double, long double>, int> indexmapping;
        for (int i = 0; i < n; i++) {
            cin >> x >> y;
            pair<long double, long double> mpair = make_pair(x, y);
            intervals.push_back(mpair);
            indexmapping[mpair] = i;
        }
        auto res = coverInterval(intervals, A, B);
        if (res.size() == 0) {
            cout << "impossible" << nl;
        }
        else {

        cout << res.size() << nl;
        for (auto& e : res) {
            cout << indexmapping[e] << " ";
        }
        cout << nl;
        }
    }

}

