/* https://www.algospot.com/judge/problem/read/WILDCARD */

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <limits>
#include <algorithm>

#define MAXLEN 100

using namespace std;

int solve(int t, int p);

string pat, txt, tmp;
int cache[MAXLEN][MAXLEN];

int main() {
	int C, N;
	cin >> C;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	vector<string> passed;

	while (C--) {
		pat.clear();
		passed.clear();

		getline(cin, pat);
		cin >> N;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
#ifdef IOTEST
		cout << ">>> pat = " << pat << endl;
		cout << ">>> N = " << N << endl;
#endif
#ifdef TEST
		cout << "--------- pat :" << pat << " ----------" << endl;
#endif

		for (int i=0; i<N; ++i) {
			txt.clear();
			getline(cin, txt);
			memset(cache, -1, sizeof(int) * MAXLEN * MAXLEN);
#ifdef IOTEST
			cout << ">>> Input " << i << ") " << txt << ", len = " << txt.size() << endl;
#endif
			if (solve(0, 0) == 1) passed.push_back(txt);
		}

		sort(passed.begin(), passed.end());
		for (string str : passed) cout << str << endl;
	}

	return 0;
}

int solve(int t, int p) {
#ifdef TEST
	cout << "(" << t << "," << p << ") => (" << txt[t] << "," << pat[p] << ")" << endl;
#endif
	if (p == pat.size() and t == txt.size()) {
#ifdef TEST
		cout << ">>> Case 1 (both end), returning 1"<< endl;
#endif
		return 1;
	}
	if (t == txt.size() or p == pat.size()) {
#ifdef TEST
		cout << ">>> Case 2 (only one ends), returning 0"<< endl;
#endif
		return pat[p] == '*' ? solve(t, p+1) : 0;
	}

	int& ret = cache[t][p];
	if (ret != -1) {
#ifdef TEST
		cout << ">>> Case cached, returns : " << ret << endl;
#endif
		return ret;
	}

	if (pat[p] == '*') {
#ifdef TEST
		cout << ">>> Case '*', calling (" << t+1 << "," << p << ") and (" << t << "," << p+1 << ")" << endl;
#endif
		return ret = max(solve(t+1, p), solve(t, p+1));
	}
	else if (pat[p] == '?') {
#ifdef TEST
		cout << ">>> Case '?', calling (" << t+1 << "," << p+1 << ")" << endl;
#endif
		return ret = solve(t+1, p+1);
	}
	else return ret = (txt[t] == pat[p] ? solve(t+1, p+1) : 0);
}
