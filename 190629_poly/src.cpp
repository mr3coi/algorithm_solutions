/* Source: https://www.algospot.com/judge/problem/read/POLY */

#include <iostream>
#include <cstring>
using namespace std;

#define MOD 10000000
#define MAXLEN 100

int cache[MAXLEN+1][MAXLEN+1];

int solve(int lastlen, int remain) {
	if (remain == 0) return 1;

	int& ret = cache[lastlen][remain];
	if (ret != -1) return ret;
	ret = 0;
	for (int curr=1;curr<=remain;++curr) ret = (ret + (curr + lastlen - 1) * solve(curr, remain-curr)) % MOD;
	return ret;
}

int main() {
	int C, len;
	cin >> C;
	while (C--) {
		memset(cache,-1,sizeof(int)*(MAXLEN+1)*(MAXLEN+1));
		cin >> len;
		int out = 0;
		for (int firstlen=1;firstlen<=len;++firstlen)
			out = (out + solve(firstlen, len-firstlen)) % MOD;
		cout << out << endl;
	}
}
