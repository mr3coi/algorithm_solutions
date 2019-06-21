#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <vector>

#define MAX_BRANCH 4

using namespace std;

void flip(string& str, int start, int end);
void parse(string& str, vector<int>& info, int start, int end);

int main() {
	int C;
	string str;

	cin >> C;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int c=0; c<C;c++) {
		getline(cin, str);

		flip(str, 0, str.size());
		cout << endl;
	}
}

/* end-exclusive */
void flip(string& str, int start, int end) {
#ifdef DEBUG
	cout << ">>> called for [" << start << ", " << end << ")" << endl;
#endif
	vector<int> info;

	cout << str[start];

	if (start < end-1) {
		vector<int> info;

		parse(str, info, start, end);
#ifdef DEBUG
		cout << "\tParsing result: ";
		for (int i=0; i<MAX_BRANCH; i++) cout << info[i] << ' ';
		cout << endl;
#endif

		flip(str, info[2], info[3]);
		flip(str, info[3], end);
		flip(str, info[0], info[1]);
		flip(str, info[1], info[2]);
	}
}

void parse(string& str, vector<int>& info, int start, int end) {
	int remain = MAX_BRANCH;
	int checkpt = MAX_BRANCH - 1;

	for (int i=start+1; i<end; i++) {
		if (--remain == checkpt) {
			info.push_back(i);
			checkpt--;
		}

		if (str[i] == 'x') remain += MAX_BRANCH;
	}

	return;
}
