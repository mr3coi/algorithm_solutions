/* Source: https://www.algospot.com/judge/problem/read/PI */

#include <iostream>
#include <sstream>
#include <limits>
#include <string>
#include <cstring>
#define C1 1
#define C2 2
#define C3 4
#define C4 5
#define C5 10
#define INF 987654321
#define MAXLEN 10000

int find_min(int start, int len);

using namespace std;

string str;
int cache[MAXLEN+1];

int solve() {
	int seqlen = str.size();
	cache[seqlen] = 0; // This is crucial (serves as base case)
	cache[seqlen-1] = INF;
	cache[seqlen-2] = INF;
	cache[seqlen-3] = find_min(seqlen-3, 3);
	cache[seqlen-4] = find_min(seqlen-4, 4);
	for (int i = seqlen-5; i>=0; --i) {
		int& ptr = cache[i];
		ptr = INF;
		for (int len=3; len<=5; len++)
			ptr = min(ptr, find_min(i, len) + cache[i+len]);
	}
	return cache[0];
}

int find_min(int start, int len) {
	int nums[5], diffs[4];
	for (int i=0; i<len; ++i) nums[i] = str[start+i] - '0';
	for (int i=0; i<len-1; ++i) diffs[i] = nums[i+1] - nums[i];
	int ret = INF;

	bool case1 = true;
	for (int i=0; i<len-1; ++i) if (diffs[i] != 0) case1 = false;
	if (case1) return C1;

	bool case24 = true;
	for (int i=0; i<len-2; ++i) if (diffs[i] != diffs[i+1]) case24 = false;
	if (case24) {
		if (diffs[0] == 1 or diffs[0] == -1) return C2;
		else return C4;
	}

	bool case3 = true;
	for (int i=0; i<len-2; ++i) if (diffs[i] + diffs[i+1] != 0) case3 = false;
	if (case3) return C3;

	return C5;
}

int main() {
	int C;
	cin >> C;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	while (C--) {
		str.clear();
		getline(cin, str);
		memset(cache, -1, sizeof(int) * MAXLEN);

		cout << solve() << endl;
	}
	return 0;
}
