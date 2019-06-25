/* Source: https://www.algospot.com/judge/problem/read/TRIANGLEPATH */

#include <iostream>
#include <cstring>

using namespace std;

#define MAXLEN 100

int tri[MAXLEN][MAXLEN];
int cache[MAXLEN][MAXLEN]; // Initialized as -1

// Returns largest sum from (r,c) to anywhere in the bottom row
int solve(int N, int r, int c) {
	// Base case: arrived at top of triangle => return the value
	if (r==N-1) return tri[r][c];

	int& ret = cache[r][c];
	if (ret != -1) return ret;

	return ret = tri[r][c] + max(solve(N, r+1,c+1), solve(N, r+1,c));
}

int main() {
	int C, N; // N: Length of edge of triangle

	cin >> C;

	while(C--) {
		cin >> N;
		for (int r=0; r<N; ++r) {
			for (int c=0; c<=r; ++c) {
				cin >> tri[r][c];
			}
		}
		memset(cache, -1, sizeof(int)*MAXLEN*MAXLEN);

		cout << solve(N, 0, 0) << endl;
	}

	return 0;
}
