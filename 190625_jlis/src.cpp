#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <limits>

#define MAXLEN 100

using namespace std;

const long long NEGINF = numeric_limits<long long>::min();
int M[MAXLEN];
int N[MAXLEN];
int cache[MAXLEN+1][MAXLEN+1];

inline int solve(int i1, int i2, int m, int n) {
	int& ret = cache[i1+1][i2+1];
	if (ret != -1) return ret;

	long long M_head = i1 == -1 ? NEGINF : M[i1];
	long long N_head = i2 == -1 ? NEGINF : N[i2];
	long long head = max(M_head, N_head);

	ret = 2;
	for (int j1=i1+1; j1<m; ++j1)
		if (M[j1] > head)
			ret = max(ret, 1 + solve(j1, i2, m, n));
	for (int j2=i2+1; j2<n; ++j2)
		if (N[j2] > head)
			ret = max(ret, 1 + solve(i1, j2, m, n));
	return ret;
}

int main() {
	int C, m, n;
	cin >> C;
	while (C--) {
		cin >> m >> n;
		for (int i=0; i<m; i++) cin >> M[i];
		for (int i=0; i<n; i++) cin >> N[i];
		memset(cache, -1, sizeof(int) * (MAXLEN+1) * (MAXLEN+1));
		cout << solve(-1,-1,m,n)-2 << endl;
	}
	return 0;
}
