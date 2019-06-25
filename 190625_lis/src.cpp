/* Source: https://www.algospot.com/judge/problem/read/LIS */

#include <iostream>
#include <cstring>

#define MAXLEN 500

using namespace std;

int seq[MAXLEN];
int cache[MAXLEN];

int solve(int start, int N) {
	int& ret = cache[start];
	if (ret != -1) return ret;

	ret = 1;
	int head = seq[start];
	for (int i=start+1; i<N; ++i) {
		if (head < seq[i])
			ret = max(ret, 1+solve(i,N));
	}
	return ret;
}

int main() {
	int C, N;

	cin >> C;

	while (C--) {
		cin >> N;
		for (int i=0; i<N; i++) cin >> seq[i];
		memset(cache, -1, sizeof(int) * MAXLEN);

		int ret = -1;
		for (int start=0; start<N; start++)
			ret = max(ret, solve(start,N));
		cout << ret << endl;
	}
	return 0;
}
