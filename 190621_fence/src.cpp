#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <cassert>

using namespace std;

int find_largest(vector<int>& fences, int start, int end);
int find_largest3(vector<int>& h, int left, int right);

int main() {
	int C, num_fence;

	cin >> C;
	vector<int> fences(20000, 0);

	for (int c=0; c<C; ++c) {
		cin >> num_fence;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		for (int i=0; i<num_fence; i++) cin >> fences[i];
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		cout << find_largest(fences, 0, num_fence-1) << endl;
		//cout << find_largest3(fences, 0, num_fence-1) << endl;
	}

	return 0;
}

/* end-exclusive */
int find_largest(vector<int>& fences, int start, int end) {
	// Base case: fence of width 1
	if (end == start) return fences[start];

	int mid = (end + start) / 2;
	
	int curr_height = min(fences[mid], fences[mid+1]);
	int curr_width = 2;
	int center_best = curr_height * curr_width;

	int left_idx = mid, right_idx = mid+1;

	/*
	while (left_idx > start or right_idx < end) {
		int left_cand = left_idx > start ? fences[left_idx-1] : 0;
		int right_cand = right_idx < end ? fences[right_idx+1] : 0;
		if (left_cand >= right_cand) {
			curr_height = min(curr_height, left_cand);
			--left_idx;
		}
		else {
			curr_height = min(curr_height, right_cand);
			++right_idx;
		}
		center_best = max(center_best, curr_height * ++curr_width);
	}
	*/
	while (left_idx > start or right_idx < end) {
		int left_cand = left_idx > start ? fences[left_idx-1] : 0;
		int right_cand = right_idx < end ? fences[right_idx+1] : 0;

		if (right_idx < end and (left_idx == start or left_cand < right_cand)) {
			++right_idx;
			curr_height = min(curr_height, right_cand);
		}
		else {
			--left_idx;
			curr_height = min(curr_height, left_cand);
		}
		center_best = max(center_best, curr_height * ++curr_width);
	}

	int left_best = find_largest(fences, start, mid);
	int right_best = find_largest(fences, mid+1, end);

	return max(center_best, max(left_best, right_best));
}

int find_largest3(vector<int>& h, int left, int right) {
	if (left == right) return h[left];

	int mid = (left + right) / 2;

	int ret = max(find_largest3(h, left, mid), find_largest3(h, mid+1, right));

	int lo = mid, hi = mid+1;
	int height = min(h[lo], h[hi]);
	ret = max(ret, height * 2);

	while (left < lo or hi < right) {
		if (hi < right && (lo == left or h[lo-1] < h[hi+1])) {
			++hi;
			height = min(height, h[hi]);
		}
		else {
			--lo;
			height = min(height, h[lo]);
		}
		ret = max(ret, height * (hi - lo + 1));
	}
	return ret;
}
