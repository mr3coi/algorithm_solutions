#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

#define INF 987654321
#define MAXLEN 100
#define MAXQUANT 10
#define FOR(v,lo,hi) for(int v=(lo);v<(hi);++v)

using namespace std;

vector<int> seq, cumsum, sq_cumsum;
int cache[MAXLEN][MAXQUANT];

/* End-inclusive */
int min_MSE(int start, int end) {
	if (end == start) return 0;

	int sum = cumsum[end];
	int sq_sum = sq_cumsum[end];
	if (start) {
		sum -= cumsum[start-1];
		sq_sum -= sq_cumsum[start-1];
	}
	int mean = (int)((float)sum / (end-start+1) + 0.5);

	return sq_sum - 2 * mean * sum + mean * mean * (end-start+1);
}

int solve(int start, int remain) {
	// Base case: 0 or fail if underused quants
	if (start == seq.size()) return 0;
	
	// Overused quants => fail
	if (remain == 0) return INF;

	int& ref = cache[start][remain];
	if (ref != -1) return ref;
	ref = INF;

	FOR(end,start,seq.size())
		ref = min(ref, min_MSE(start,end) + solve(end+1, remain-1));
	return ref;
}

int main() {
	int C, N, S, tmp, sum, sq_sum;
	cin >> C;
	seq.reserve(MAXLEN);
	cumsum.reserve(MAXLEN);
	sq_cumsum.reserve(MAXLEN);

	while(C--) {
		memset(cache, -1, sizeof(int) * MAXLEN * MAXQUANT);
		cin >> N >> S;
		seq.clear(); cumsum.clear(); sq_cumsum.clear();
		sum = sq_sum = 0;

		for (int i=0; i<N; ++i) {
			cin >> tmp;
			seq.push_back(tmp);
		}

		sort(seq.begin(), seq.end());

		for (auto it=seq.begin(); it<seq.end(); ++it) {
			sum += *it;
			cumsum.push_back(sum);
			sq_sum += (*it) * (*it);
			sq_cumsum.push_back(sq_sum);
		}

#ifdef IOTEST
		for (int i=0; i<N; ++i) cout << seq[i] << ' ';
		cout << endl;
		for (int i=0; i<N; ++i) cout << cumsum[i] << ' ';
		cout << endl;
		for (int i=0; i<N; ++i) cout << sq_cumsum[i] << ' ';
		cout << endl;
#endif

		cout << solve(0,S) << endl;
	}
	return 0;
}
