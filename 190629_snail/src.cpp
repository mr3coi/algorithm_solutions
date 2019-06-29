/* Source: https://www.algospot.com/judge/problem/read/SNAIL */

#include <iostream>
#include <iomanip>

using namespace std;

#define MAXN 1000
#define MAXM 1000
#define PROB 0.75
#define FOR(v,lo,hi) for(int v=(lo);v<(hi);++v)

double cache[MAXM][MAXN];

// need: # of rainy days needed
double solve(int day, int need) {
	if (need <= 0) return 1.0f;
	if (day < need) return 0.0f;

	double& ret = cache[day][need];
	if (ret != -1) return ret;

	return ret = PROB * solve(day-1, need-1) + (1-PROB) * solve(day-1, need);
}

int main() {
	int C, M, N;
	cin >> C;
	cout << fixed << setprecision(10);
	while (C--) {
		cin >> N >> M;
		FOR(i,0,M+1) FOR(j,0,N+1) cache[i][j] = -1;
		cout << solve(M,N-M) << endl;
	}
	return 0;
}
