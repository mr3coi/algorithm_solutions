/* Source: https://www.algospot.com/judge/problem/read/TILING2 */

#include <iostream>
#include <cstring>

#define MOD 1000000007
#define MAXLEN 100

using namespace std;

int cache[MAXLEN+1];

// len: remaining length
int solve(int len) {
	if (len <= 1) return 1;

	int& ret = cache[len];
	if (ret != -1) return ret;

	return ret = (solve(len-1) + solve(len-2)) % MOD;
}

int main() {
	int C, len;
	cin >> C;
	while (C--) {
		memset(cache, -1, sizeof(int) * (MAXLEN+1));
		cin >> len;
		cout << solve(len) << endl;
	}

	return 0;
}
