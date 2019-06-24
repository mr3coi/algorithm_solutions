#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

using namespace std;

vector<vector<int>> tile;
vector<vector<bool>> visited;

bool solve(int size, int row, int col);

int main() {
	int C, size;

	cin >> C;

	for (int c=0; c<C; c++) {
		cin >> size;
		tile = vector<vector<int>>(size, vector<int>(size, 0));
		visited = vector<vector<bool>>(size, vector<bool>(size, false));

		for (int row=0; row<size; ++row)
			for (int col=0; col<size; ++col)
				cin >> tile[row][col];

		cout << (solve(size, 0, 0) ? "YES" : "NO") << endl;
	}

	return 0;
}

bool solve(int size, int row, int col) {
	// Base case: arrived at destination
	if (row == size-1 and col == size-1) return true;

	// Cached; already visited, meaningless to re-visit
	if (visited[row][col]) return false;

	visited[row][col] = true;
	int jumpsize = tile[row][col];
	bool ret = false;
	if (col + jumpsize < size) ret |= solve(size, row, col+jumpsize); // East
	if (row + jumpsize < size) ret |= solve(size, row+jumpsize, col); // South

	return ret;
}
