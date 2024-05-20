/*
author: lowko527 
about problem: Range sum implementation with segmenttree
time complexity: O(nlogn)
mem complexity: O(n) 
usage instruction: provdies function kanpsack to solve, see desc 
assumptions: 
Additional Desciption: 
 - I want you to expand your documentation with a high-level description of how the data structure operates. In particular, how does a Fenwick Tree improve on the naive O(N) approach?

First of, note that this does not use a fenwick tree but a seg tree, I find fenwick trees only to be a better alternative 
than segtrees if the memory is of importance, otherwise segtrees are somewhat more interesting to work with, hence I went for that instead.
Rangesum is solved with seg tree by maintaining a binary tree structure where parent leaves store the sum of its children. The inehric properties of this
structure allows for logn updates and logn calculate sum, in contrast to the Naive approach iterating over the full segment again on update is not as efficint.

*/

#ifndef TEMPLATE
#include<bits/stdc++.h>
using namespace std;

const char nl = '\n';
#define _ << " " <<
#endif


#define int long long // fulhack skippa templates

struct segtree {
    vector<int> heap{0};
    int bp{1};

    segtree(int len) {
        while(bp < len) bp <<= 1; //pow(2,ceil(log2(len)));
        heap.resize(2*bp);
        // for (int i = 0; i < 2 * bp; i++) {
        //     heap[i] = i;
        // }
        build();
    }

    // f is the modular implementation of a function to be applied on a range query, note that this allows for other functions
    // such as bitwist and etc.
    int f(int a, int b){
        return a+b;
    }

    // build initialises the tree.
    void build(int hidx = 1) {
        if (hidx >= bp) {
            return;
        }
        build(hidx * 2);
        build(hidx * 2 + 1);
        heap[hidx] = f(heap[hidx * 2],heap[hidx * 2 + 1]);
    }

    // updateIdx propagates the update throughout the struct
    void updateIdx(int idx, int val) {
        idx += bp;
        heap[idx] = f(heap[idx],val);
        while (idx > 1) {
            idx /= 2;
            heap[idx] = f(heap[idx * 2],heap[idx * 2 + 1]);
        }
    }

    // rangeF take left and right parameters and calculates function "f" on them.
    int rangeF(int l, int r) {
        //get f of interval [l,r)
        l += bp;
        r += bp - 1;
        int ans = 0;
        while (r >= l) {
            if (l & 1) {
                ans = f(ans,heap[l]);
                l += 1;
            }
            if (!(r & 1)) {
                ans = f(ans,heap[r]);
                r -= 1;
            }
            l /= 2;
            r /= 2;
        }
        return ans;
    }
};


signed main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int n,q; cin >> n >> q;
    char c;
    int a,b;
    segtree z(n);
    while(q--){
        cin >> c;
        if(c=='+'){
            cin >> a >> b;
            z.updateIdx(a,b);
        } else{
            cin >> a;
            cout << z.rangeF(0,a) << nl;
        }
    }
}