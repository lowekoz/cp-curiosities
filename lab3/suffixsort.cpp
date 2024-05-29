/*
author: lowko527
about problem: Sorting of all suffixes, with vector of integers indicating the position of suffices by index
time complexity: O(n + k) (non-negotiable var k as it uses couting sort implementation.)
mem complexity: O(n)
usage instruction: provided is a function CreateSuffixArray that takes a string and provides a sorted suffix arr representation

Additional Desc.
https://codeforces.com/edu/course/2/lesson/2
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

// helper function to suffix sort
void countingSort(vector<array<int, 3>>& v, int maxEqVal) {
	int n = v.size();
	maxEqVal += 1; //maxEqKlass till 0
	//sätt allt i scope så vi bara kan copy pastea!
	{
		vector<array<int, 3>> v_new(n);
		vector<int> cnt(maxEqVal); //hur stor varje bucket är
		for (int i = 0; i < n; i++) {
			cnt[v[i][2]]++; //efter el 2
		}
		//egentligen onädigt med n stna platser, behöver bara max eq class
		vector<int> calcIndex(maxEqVal); //vilken index varje key-bucket ska börja på.
		calcIndex[0] = 0; //0 börjar på 0. 1 börjar på prevstart + cnt(0) osv.
		for (int i = 1; i < maxEqVal; i++) {
			calcIndex[i] = calcIndex[i - 1] + cnt[i - 1]; //0 3 5 7 7 7 7 7 ish.
		}
		//nu vet vi första tomma platsen i bucket med för key x (idx x).
		//placera dess i orginal array
		for (int i = 0; i < n; i++) {
			//i vår nya array, vi hämtar en eqvivalence klass säg 2, ser var nästa 2a ska vara ->
			//lägger in den på den positionen, och säger att nästa två ska vara på en större pos.
			v_new[calcIndex[v[i][2]]] = v[i];
			calcIndex[v[i][2]] += 1;
		}
		v = v_new;
	}

	//samma sak igen
	{
		vector<array<int, 3>> v_new(n);
		vector<int> cnt(maxEqVal); //hur stor varje bucket är
		for (int i = 0; i < n; i++) {
			cnt[v[i][1]]++; //efter el 2
		}

		//egentligen onädigt med n stna platser, behöver bara max eq class
		vector<int> calcIndex(maxEqVal); //vilken index varje key-bucket ska börja på.
		calcIndex[0] = 0; //0 börjar på 0. 1 börjar på prevstart + cnt(0) osv.
		for (int i = 1; i < maxEqVal; i++) {
			calcIndex[i] = calcIndex[i - 1] + cnt[i - 1]; //0 3 5 7 7 7 7 7 ish.
		}
		//nu vet vi första tomma platsen i bucket med för key x (idx x).
		//placera dess i orginal array
		//Troligtvis fel?
		for (int i = 0; i < n; i++) {
			//i vår nya array, vi hämtar en eqvivalence klass säg 2, ser var nästa 2a ska vara ->
			//lägger in den på den positionen, och säger att nästa två ska vara på en större pos.
			v_new[calcIndex[v[i][1]]] = v[i];
			calcIndex[v[i][1]] += 1;
		}
		v = v_new;
	}
}

vector<int> CreateSuffixArray(string s) {

	//s += "$";
	s.push_back('\0');
	int n = s.length();
	vector<pair<char, int>> initialIter;

	for (int i = 0; i < n; i++) {
		initialIter.push_back({ s[i],i });
	}

	sort(initialIter.begin(), initialIter.end()); 
	vector<int> SuffixesStartsEkvivalensklass(n); 

	int eqKlassVal = 0;
	SuffixesStartsEkvivalensklass[initialIter[0].second] = 0; //idx i motsvarar start i (suffixmässigt i s)
	for (int i = 1; i < n; i++) {
		if (!(initialIter[i].first == initialIter[i - 1].first)) {
			eqKlassVal += 1;
		}
		SuffixesStartsEkvivalensklass[initialIter[i].second] = eqKlassVal;
	}

	vector<array<int, 3>> tmp(n); //sprar äv ans hör
	int k = 0;
	int limit = 1;
	while (limit < n) {
		limit = limit << 1;
	}
	while ((1 << k) <= limit) {
		//vi vill, göra eq.klasser för pos,startInStr,endInStr för k+1 givet prev eq.klasser
		//vector<array<int,3>> tmp(n); //måste veta var start är! -> andra är bara för sort. Sedan mha. start bygga nästa eq.

		for (int i = 0; i < n; i++) {
			tmp[i] = { i,SuffixesStartsEkvivalensklass[i],SuffixesStartsEkvivalensklass[(i + (1 << (k))) % n] };
		}

		//sortera tmp counting sort! först efter bakre, sedan efter främre! -> garantera flyttar bara så lång
		countingSort(tmp, eqKlassVal);

		eqKlassVal = 0;
		SuffixesStartsEkvivalensklass[tmp[0][0]] = 0;
		for (int i = 1; i < n; i++) {
			bool flag = false;

			if (tmp[i - 1][1] < tmp[i][1]) flag = true;

			if ((tmp[i - 1][1] == tmp[i][1]) && (tmp[i - 1][2] < tmp[i][2])) flag = true;

			if (flag) {
				eqKlassVal += 1;
			}

			SuffixesStartsEkvivalensklass[tmp[i][0]] = eqKlassVal;
		}

		k += 1;

	}

	vector<int> ans(n);
	for (int i = 0; i < n; i++) {
		ans[i] = tmp[i][0];
	}
	return ans;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
	string s;
	while (getline(cin,s)) {
		int n; cin >> n;
		vector<int> q(n);
		for (int i = 0; i < n; i++) {
			cin >> q[i];
		}
		cin.ignore(); // consume newline

		auto v = CreateSuffixArray(s);
		/*for (auto el : v) {
			cout << el << " ";
		}*/
		for (auto el : q) {
			cout << v[el + 1] << " ";
		}
		cout << nl;
	}
}

/*
1
151 783 57 278

7 35 3 18 33 26 6 2
17 12 19 20 21 22 18

*/
