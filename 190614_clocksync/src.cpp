#include <iostream>
#include <limits>
#include <string>
#include <vector>

#define NUM_CLOCKS 16
#define NUM_SWITCHES 10
#define FAIL 31
#define MIN(x,y) ((x) <= (y) ? (x) : (y))

using namespace std;

vector<vector<int>> each_switch = {
	{0, 1, 2},
	{3, 7, 9, 11},
	{4, 10, 14, 15},
	{0, 4, 5, 6, 7},
	{6, 7, 8, 10, 12},
	{0, 2, 14, 15},
	{3, 14, 15},
	{4, 5, 7, 14, 15},
	{1, 2, 3, 4, 5},
	{3, 4, 5, 9, 13}
};

vector<vector<int>> each_clock = {
	{0,3,5},
	{8},
	{},
	{1,6,9},
	{2,7},
	{},
	{4}
};

int sync_clock(int status[NUM_CLOCKS], int curr, int num_press);
void press(int status[NUM_CLOCKS], int swtch, bool press);

int sync_clock2(int status[NUM_CLOCKS], int curr, int num_press);
void press2(int status[NUM_CLOCKS], int swtch, int press);

int main() {
	int C, status[NUM_CLOCKS], tmp;

	cin >> C;

	for (int c=0; c<C; c++) {
		/* ================= I/O =============== */
		for (int i=0; i<NUM_CLOCKS; i++) {
			cin >> tmp;
			status[i] = (tmp / 3) % 4;
		}

		/* ================= Algorithm =============== */
		int output = sync_clock2(status, 0, 0);
		cout << (output == FAIL ? -1 : output) << endl;
	}

	return 0;
}

int sync_clock(int status[NUM_CLOCKS], int curr, int num_press) {
#ifdef DEBUG
	cout << ">>> curr = " << curr << ", num_press = " << num_press << endl;
	cout << ">>> [status] ";
	for (int i=0; i<NUM_CLOCKS; i++) cout << status[i] << " ";
	cout << endl;
#endif

	if (num_press > 30) { // Base case 4
#ifdef DEBUG
		cout << ">>> Arrived at base case 4 => FAIL" << endl;
#endif
		return FAIL;
	}

	if (curr >= 7) { // Base case 1, 2
		int sum = 0;
		for (int i=7; i<16; i++) sum += status[i];
#ifdef DEBUG
		cout << ">>> Arrived at base case 1/2, sum = " << sum << endl;
#endif
		return sum == 0 ? num_press : FAIL;
	}

	if (status[curr] == 0) {
		return sync_clock(status, curr+1, num_press);
	}
	else { // if status[curr] > 0
		int ret = 31; // Large value

		if (each_clock[curr].size() == 0) { // Base case 3
#ifdef DEBUG
			cout << ">>> Arrived at base case 3 => FAIL" << endl;
#endif
			return FAIL;
		}

		for (int swtch: each_clock[curr]) {
#ifdef DEBUG
			cout << ">>> Pressing switch " << swtch << endl;
#endif
			press(status, swtch, true);
			num_press += 1;
			int out = sync_clock(status, curr, num_press);
			ret = MIN(ret, out);
			num_press -= 1;
			press(status, swtch, false);
		}

		return ret;
	}
}

void press(int status[NUM_CLOCKS], int swtch, bool press) {
	for (int target: each_switch[swtch])
		status[target] = (status[target] + static_cast<int>(press) * 2 - 1 + 4) % 4;

	return;
}

void press2(int status[NUM_CLOCKS], int swtch, int press) {
	for (int target: each_switch[swtch])
		status[target] = (status[target] + press + 4) % 4;

	return;
}

int sync_clock2(int status[NUM_CLOCKS], int curr, int num_press) {
	if (curr >= NUM_SWITCHES) {		// Base case: pressed all switches
		int sum = 0;
		for (int i=0; i<NUM_CLOCKS; i++) sum += status[i];
		return sum == 0 ? num_press : FAIL;
	}

	int ret = sync_clock2(status, curr+1, num_press);	// No-press case

	for (int i=1; i<4; i++) {	// i: # of presses at curr
		press2(status, curr, i);
		int out = sync_clock2(status, curr+1, num_press+i);
		ret = MIN(ret, out);
		press2(status, curr, -1 * i);
	}

	return ret;
}
