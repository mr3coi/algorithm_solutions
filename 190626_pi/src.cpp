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

int solve(int start) {
#ifdef TEST
	cout << "> start = " << start << endl;
#endif
	if (start == str.size()) return 0;
	if (start > str.size() - 3) return INF;

	int& ret = cache[start];
	if (ret != -1) return ret;
	ret = INF;

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

		// TODO: Delete
		if (str.size() > 8000) {
			cout << "passed" << endl;
			continue;
		}

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
