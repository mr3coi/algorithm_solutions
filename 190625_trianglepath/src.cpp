/* Source: https://www.algospot.com/judge/problem/read/TRIANGLEPATH */

#include <iostream>
#include <cstring>

using namespace std;

#define MAXLEN 100

int tri[MAXLEN][MAXLEN];
int cache[MAXLEN][MAXLEN]; // Initialized as -1

int solve(int N, int r, int c) {
	// Base case: arrived at top of triangle => return the value
	if (r==0 and c==0) return tri[r][c];

	int& ret = cache[r][c];
	if (ret != -1) return ret;

	return ret = tri[r][c] + max(c > 0 ? solve(N, r-1,c-1) : -1, c < r ? solve(N, r-1,c) : -1);
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

		int ret = -1;
		for (int c=0; c<N; ++c) ret = max(ret, solve(N, N-1, c));
		cout << ret << endl;
	}

	return 0;
}
