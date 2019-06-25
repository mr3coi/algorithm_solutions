/* Source: https://www.algospot.com/judge/problem/read/TRIANGLEPATH */

#include <iostream>

using namespace std;

#define MAXLEN 100

int tri[MAXLEN][MAXLEN];

int solve(int N) {
	for (int r=1; r<N; ++r) {
		tri[r][0] += tri[r-1][0];
		for (int c=1; c<r; ++c)
			tri[r][c] += max(tri[r-1][c], tri[r-1][c-1]);
		tri[r][r] += tri[r-1][r-1];
	}
	int ret = tri[N-1][0];
	for (int c=1; c<N; ++c) ret = max(ret, tri[N-1][c]);
	return ret;
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
#ifdef IOTEST
		for (int r=0; r<N; ++r) {
			for (int c=0; c<N; ++c) {
				cout << tri[r][c] << ' ';
			}
			cout << endl;
		}
#endif
		cout << solve(N) << endl;;
#ifdef TEST
		for (int r=0; r<N; ++r) {
			for (int c=0; c<N; ++c) {
				cout << tri[r][c] << ' ';
			}
			cout << endl;
		}
#endif
	}

	return 0;
}
