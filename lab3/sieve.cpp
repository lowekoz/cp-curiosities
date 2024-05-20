
/*
author: lowko527
about problem: Implementation of well known Sieve of Eratosthenes
time complexity: O(nlognlogn)
mem complexity: O(n)
usage instruction: see function primeSieveBool 
assumptions: No negative number shenanigans, (no err checks)
*/

#include <bits/stdc++.h>
// ############ AUX
using namespace std;
const char nl = '\n';

template<typename T>
std::istream& operator>> (std::istream& stream, std::vector<T>& a) {
	a.clear(); // remove whatever was in a before

	std::string line;
	do {
		if (stream.eof())
			return stream; // if the stream has ended, just let a be empty

		getline(stream, line);
	} while (line.empty());

	std::istringstream line_stream(line);
	T x;
	while (line_stream >> x)
		a.push_back(x);

	return stream;
}

void pr(vector<long double>& a) {
	for (auto e : a) {
		cout << e << " ";
	}
	cout << nl;
}

// ############ END AUX

void solve() {
	
}

/**
 * @brief Generates a boolean vector indicating prime numbers up to a specified maximum value.
 *
 * @param max The maximum value up to which to check for prime numbers. The range is [0, max].
 * @param cnt Reference to an integer that will be set to the count of prime numbers found within the range.
 * @return A vector of booleans where each index indicates whether the corresponding number is prime.
 */
vector<bool> primeSieveBool(int max, int& cnt) {
    vector<bool> sieve(max + 1, 1);
	sieve[0] = 0;
	sieve[1] = 0;
	int num = 2;
    while (num <= max) {
        if (sieve[num]) {
			cnt++;
            for (int i = num + num; i <= max; i += num) {
                sieve[i] = 0;
            }
        }
        num += 1;
    }
    return sieve;
}

int main() {
	cin.tie(0); ios_base::sync_with_stdio(0);
	/*int t; cin >> t;
	while (t--) {
		solve();
	}*/
	int n, q; cin >> n >> q;
	int x;
	int cnt = 0;
	vector<bool> b = primeSieveBool(n, cnt);
	cout << cnt << nl;
	for (int i = 0; i < q; i++) {
		cin >> x;
		if (b[x]) cout << 1 << nl;
		else cout << 0 << nl;
	}
}
/*

*/