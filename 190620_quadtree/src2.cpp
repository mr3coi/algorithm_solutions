#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <vector>

#define MAX_BRANCH 4

using namespace std;

string flip(string::iterator& it);

int main() {
	int C;
	string str;

	cin >> C;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	for (int c=0; c<C;c++) {
		getline(cin, str);

		string::iterator it = str.begin();

		string output = flip(it);
		cout << output << endl;
	}
}

/* end-exclusive */
string flip(string::iterator& it) {
	char head = *(it++);

	if (head == 'x') {
		string topleft  = flip(it);
		string topright = flip(it);
		string botleft  = flip(it);
		string botright = flip(it);

		return "x" + botleft + botright + topleft + topright;
	}
	else {
		return string(1, head);
	}
}
