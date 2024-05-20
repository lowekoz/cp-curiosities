/*
author: lowko527 
about problem: standard knapsack, recursive impl wiht full 2D table memo (non map)
time complexity: O(N*C)
mem complexity: O(N*C) 
usage instruction: provdies function kanpsack to solve, see desc 
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

struct Item {
    int value;
    int weight;
    int index;
};

// Recursive function to solve knapsack problem and reconstruct selected items
int knapsackRecursive(const vector<Item>& items, int capacity, int currentIndex, vector<vector<int>>& dp) {
    // base case
    if (capacity <= 0 || currentIndex < 0) {
        return 0;
    }
    // use memoization.
    if (dp[currentIndex][capacity] != -1) {
        return dp[currentIndex][capacity];
    }
    if (items[currentIndex].weight > capacity) {
        return knapsackRecursive(items, capacity, currentIndex - 1, dp);
    }

    // either pick or skip item 
    int includeItem = items[currentIndex].value +
        knapsackRecursive(items, capacity - items[currentIndex].weight, currentIndex - 1, dp);
    int excludeItem = knapsackRecursive(items, capacity, currentIndex - 1, dp);

    // Memoization
    if (includeItem > excludeItem) {
        dp[currentIndex][capacity] = includeItem;
    }
    else {
        dp[currentIndex][capacity] = excludeItem;
    }

    return dp[currentIndex][capacity];
}

/**
 * @brief Solves the knapsack problem iteratively using dynamic programming.
 *
 * Given a set of items and the capacity of the knapsack, this function finds the maximum value
 * that can be achieved by selecting a subset of items such that the total weight does not exceed
 * the capacity of the knapsack.
 *
 * @param items A vector of Item structures representing the available items, where each item
 *              contains a value and a weight.
 * @param capacity The capacity of the knapsack.
 * @param selectedItems A reference to a vector of Item structures that will store the selected items
 *                      contributing to the maximum value.
 * @return The maximum value that can be achieved by selecting a subset of items without exceeding
 *         the capacity of the knapsack.
 */
int knapsack(const vector<Item>& items, int capacity, vector<Item>& selectedItems) {
    int n = items.size();
    vector<vector<int>> dp(n, vector<int>(capacity + 1, -1));
    int maxValue = knapsackRecursive(items, capacity, n - 1, dp);

    // reconstruct
    int remainingCapacity = capacity;
    for (int i = n - 1; i >= 0 && maxValue > 0; --i) {
        if (i == 0 || dp[i][remainingCapacity] != dp[i - 1][remainingCapacity]) {
            selectedItems.push_back(items[i]);
            maxValue -= items[i].value;
            remainingCapacity -= items[i].weight;
        }
    }
    return dp[n - 1][capacity];
}


int main() {
    cin.tie(0); ios_base::sync_with_stdio(0);
    int C, n;
    while (cin >> C >> n) {
        vector <Item> itemNo(n);
        for (int i = 0; i < n; i++) {
            int v, w; cin >> v >> w;
            itemNo[i].value = v; itemNo[i].weight = w; itemNo[i].index = i;
        }
        vector<Item> selectedItems;
        int maxVal = knapsack(itemNo, C, selectedItems);
        cout << selectedItems.size() << nl;
        for (auto ite: selectedItems) {
            cout << ite.index << " ";
        }
        cout << nl;
    }

}

/*
overwrite it :xx each time.
*/

