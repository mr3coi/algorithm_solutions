/* Source: https://www.algospot.com/judge/problem/read/TRIPATHCNT */

#include <iostream>
#include <cstring>

#define MAXLEN 100

using namespace std;

int tri[MAXLEN][MAXLEN];
int sumcache[MAXLEN][MAXLEN];
int countcache[MAXLEN][MAXLEN];

int solve(int row, int col, int height) {
	int& ret = countcache[row][col];
	int& sum = sumcache[row][col];
	if (row == height-1) {
		sum = tri[row][col];
		return ret = 1;
	}

	// Memoization
	if (ret != -1) return ret;

	// Recursive call here - `sumcache`, `countcache` filled in
	int leftcount = solve(row+1,col,height);
	int rightcount = solve(row+1,col+1,height);

	int leftsum = sumcache[row+1][col];
	int rightsum = sumcache[row+1][col+1];

	if (leftsum > rightsum) {
		sum = leftsum + tri[row][col];
		return ret = leftcount;
	}
	else if (leftsum < rightsum) {
		sum = rightsum + tri[row][col];
		return ret = rightcount;
	}
	else {
		sum = leftsum + tri[row][col];
		return ret = leftcount + rightcount;
	}
}

int main() {
	int C, N;
	cin >> C;
	while (C--) {
		cin >> N;
		memset(tri, 0, sizeof(int) * MAXLEN * MAXLEN);
		memset(sumcache, -1, sizeof(int) * MAXLEN * MAXLEN);
		memset(countcache, -1, sizeof(int) * MAXLEN * MAXLEN);
		for (int row=0; row<N; ++row)
			for (int col=0; col<=row; ++col)
				cin >> tri[row][col];
		cout << solve(0,0,N) << endl;
	}

	return 0;
}
