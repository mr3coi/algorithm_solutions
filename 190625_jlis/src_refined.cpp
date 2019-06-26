#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <limits>

#define MAXLEN 100
#define FOR(v,lo,hi) for (int v=(lo);v<(hi);++v)

using namespace std;

const long long NEGINF = numeric_limits<long long>::min();
int M[MAXLEN], N[MAXLEN], cache[MAXLEN+1][MAXLEN+1], m, n;

inline int solve(int i1, int i2, long long head) {
	int& ret = cache[i1+1][i2+1];
	if (ret != -1) return ret;
	ret = 2;
	FOR(j1,i1+1,m) if (M[j1] > head) ret = max(ret, 1 + solve(j1, i2, M[j1]));
	FOR(j2,i2+1,n) if (N[j2] > head) ret = max(ret, 1 + solve(i1, j2, N[j2]));
	return ret;
}

int main() {
	int C;
	cin >> C;
	while (C--) {
		cin >> m >> n;
		for (int i=0; i<m; i++) cin >> M[i];
		for (int i=0; i<n; i++) cin >> N[i];
		memset(cache, -1, sizeof(int) * (MAXLEN+1) * (MAXLEN+1));
		cout << solve(-1,-1, NEGINF)-2 << endl;
	}
	return 0;
}
