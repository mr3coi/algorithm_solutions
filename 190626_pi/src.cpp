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

using namespace std;

string str;
int cache[MAXLEN];

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

int solve(int start) {
#ifdef TEST
	cout << "> start = " << start << endl;
#endif
	if (start == str.size()) return 0;
	if (start > str.size() - 3) return INF;

	int& ret = cache[start];
	if (ret != -1) return ret;
	ret = INF;

	/* This code + `find_min` instead of the code chunk below */
	for (int len=3; len<=5; ++len)
		if (start+len <= str.size())
			ret = min(ret, find_min(start, len) + solve(start+len));

	/* Below chunk has not been debugged
	int nums[5];
	for (int i=0; i<5; ++i)
		if (start + i < str.size()) nums[i] = str[start+i] - '0';

	int diff12 = nums[1] - nums[0], diff23 = nums[2] - nums[1];
	if (diff12 == 0 and diff23 == 0) { // Case 1
#ifdef TEST
		cout << ">>> case 1"<< endl;
#endif
		ret = min(ret, C1 + solve(start+3));
		if (start <= str.size() - 4 and nums[3] == nums[2]) {
			ret = min(ret, C1 + solve(start+4));
			if (start <= str.size() - 5 and nums[4] == nums[3])
				ret = min(ret, C1 + solve(start+5));
		}
	}
	else if (diff12 == diff23) {
		if (diff12 == 1 or diff12 == -1) { // Case 2
#ifdef TEST
			cout << ">>> case 2"<< endl;
#endif
			ret = min(ret, C2 + solve(start+3));
			if (start <= str.size() - 4 and nums[3] - nums[2] == diff12) {
				ret = min(ret, C2 + solve(start+4));
				if (start <= str.size() - 5 and nums[4] - nums[3] == diff12)
					ret = min(ret, C2 + solve(start+5));
			}
		}
		else { // Case 4
#ifdef TEST
			cout << ">>> case 4"<< endl;
#endif
			ret = min(ret, C4 + solve(start+3));
			if (start <= str.size() - 4 and nums[3] - nums[2] == diff12) {
				ret = min(ret, C4 + solve(start+4));
				if (start <= str.size() - 5 and nums[4] - nums[3] == diff12)
					ret = min(ret, C4 + solve(start+5));
			}
		}
	}
	else if (diff12 + diff23 == 0) { // Case 3
#ifdef TEST
		cout << ">>> case 3"<< endl;
#endif
		ret = min(ret, C3 + solve(start+3));
		if (start <= str.size() - 4 and nums[3] == nums[1]) {
			ret = min(ret, C3 + solve(start+4));
			if (start <= str.size() - 5 and nums[4] == nums[2])
				ret = min(ret, C3 + solve(start+5));
		}
	}
	else {
		ret = min(ret, C5 + solve(start+3));
		if (start <= str.size() - 4)
			ret = min(ret, C5 + solve(start+4));
		if (start <= str.size() - 5)
			ret = min(ret, C5 + solve(start+5));
	}
	*/

	return ret;
}

int main() {
	int C;
	cin >> C;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	while (C--) {
		str.clear();
		getline(cin, str);
#ifdef IOTEST
		cout << str << endl;
#endif
		memset(cache, -1, sizeof(int) * MAXLEN);

		cout << solve(0) << endl;

		/*
#ifdef TEST
		cout << ">>>>> Cache : ";
		for (int i=0; i<str.size(); ++i) cout << cache[i] << ' ';
		cout << endl;
#endif
*/
	}
	return 0;
}
