/* Source: https://www.algospot.com/judge/problem/read/ASYMTILING */

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
		cin >> len;
		memset(cache, -1, sizeof(int) * (MAXLEN+1));
#ifdef TEST
		int out_full = solve(len);
		int out_half = solve(len/2);
		cout << "solve(len) = " << out_full << endl;
		cout << "solve(len/2) = " << out_half << endl;
#endif
		if (len % 2) cout << (solve(len) + MOD - solve(len/2)) % MOD << endl;
		else {
			int out = (solve(len) + MOD - solve(len/2)) % MOD;
			out = (out + MOD - solve(len/2-1)) % MOD;
			cout << out << endl;
		}
	}

	return 0;
}
