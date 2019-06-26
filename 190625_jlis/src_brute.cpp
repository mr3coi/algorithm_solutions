#include <iostream>
#include <vector>

#define MAXLEN 100

using namespace std;

int solve(vector<int>& M, vector<int>& N) {
	if (M.empty() and N.empty()) return 0;

	int ret = 0;
	vector<int> M_new = vector<int>(), N_new = vector<int>();
	M_new.reserve(MAXLEN);
	N_new.reserve(MAXLEN);

	for (int i=0; i<M.size(); ++i) {
		M_new.clear(), N_new.clear();
		int cand = M[i];
		for (int j=i+1; j<M.size(); ++j)
			if (M[j] > cand) M_new.push_back(M[j]);
		for (int j=0; j<N.size(); ++j)
			if (N[j] != cand) N_new.push_back(N[j]);
		ret = max(ret, 1+solve(M_new, N_new));
	}
	for (int i=0; i<N.size(); ++i) {
		M_new.clear(), N_new.clear();
		int cand = N[i];
		for (int j=i+1; j<N.size(); ++j)
			if (N[j] > cand) N_new.push_back(N[j]);
		for (int j=0; j<M.size(); ++j)
			if (M[j] != cand) M_new.push_back(M[j]);
		ret = max(ret, 1+solve(M_new, N_new));
	}
	return ret;
}

int main() {
	int C, m, n;
	cin >> C;
	while (C--) {
		cin >> m >> n;
		vector<int> M = vector<int>(m,0);
		vector<int> N = vector<int>(n,0);
		for (int i=0; i<m; i++) cin >> M[i];
		for (int i=0; i<n; i++) cin >> N[i];
#ifdef IOTEST
		for (int i=0; i<m; i++) cout << M[i] << ' ';
		cout << endl;
		for (int i=0; i<n; i++) cout << N[i] << ' ';
		cout << endl;
#endif

		cout << solve(M,N) << endl;
	}
	return 0;
}
