/* Source: https://www.algospot.com/judge/problem/read/ASYMTILING */

#include <iostream>
#include <cstring>

#define MOD 1000000007
#define MAXLEN 100

using namespace std;

int cache[MAXLEN+1];

// len: remaining length
void solve(int len) {
	cache[0] = cache[1] = 1;
	for (int i=2;i<=len;++i) cache[i] = (cache[i-1] + cache[i-2]) % MOD;
}

int main() {
	int C, len;
	cin >> C;
	while (C--) {
		cin >> len;
		memset(cache, -1, sizeof(int) * (MAXLEN+1));
		solve(len);
		if (len % 2) cout << (cache[len] + MOD - cache[len/2]) % MOD << endl;
		else {
			int out = (cache[len] + MOD - cache[len/2]) % MOD;
			out = (out + MOD - cache[len/2-1]) % MOD;
			cout << out << endl;
		}
	}

	return 0;
}
