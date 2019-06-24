// Reference: https://www.algospot.com/judge/submission/detail/607951

#include <iostream>
#include <vector>

using namespace std;

auto ds = []() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	return 0;
}();

vector<vector<bool>> visited;

int main() {
	int C, size, jmp;
	cin >> C;

	while (C--) {
		cin >> size;
		visited = vector<vector<bool>>(size, vector<bool>(size, false));
		visited[0][0] = true;

		for (int r=0; r<size; ++r)
			for (int c=0; c<size; ++c) {
				cin >> jmp;
				if (visited[r][c]) {
					if (r+jmp<size) visited[r+jmp][c] = true;
					if (c+jmp<size) visited[r][c+jmp] = true;
				}
			}

		cout << (visited[size-1][size-1] ? "YES" : "NO") << endl;
	}

	return 0;
}
