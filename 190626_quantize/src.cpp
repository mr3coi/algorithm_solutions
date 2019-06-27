#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

#define INF 987654321
#define MAXLEN 100
#define MAXQUANT 10

using namespace std;

vector<int> seq, cumsum, sq_cumsum;
int cache[MAXLEN][MAXQUANT];

/* End-exclusive */
int min_MSE(int start, int end) {
	if (end == start+1) return 0;

	int sum = (start == 0 ? cumsum[end-1] : cumsum[end-1] - cumsum[start-1]);
	float mean = (float)sum / (float)(end-start);
	int mean2 = (int)mean + ((int)(mean *10) % 10 >= 5);

	int sq_sum = (start == 0 ? sq_cumsum[end-1] : sq_cumsum[end-1] - sq_cumsum[start-1]);

	return sq_sum - 2*mean2*sum + mean2 * mean2 * (end-start);
}

int solve(int start, int remain) {
	// Base case: 0 or fail if underused quants
	if (start == seq.size()) return 0;
	
	// Overused quants => fail
	if (remain == 0 and start < seq.size()) return INF;

	int& ref = cache[start][remain];
	if (ref != -1) return ref;
	ref = INF;

	for (int end=start+1; end<=seq.size(); ++end)
		ref = min(ref, min_MSE(start,end) + solve(end, remain-1));

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
