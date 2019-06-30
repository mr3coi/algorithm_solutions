/* Source: https://www.algospot.com/judge/problem/read/NUMB3RS */

#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>

using namespace std;

#define MAXN 100
#define MAXD 100
#define FOR(v,lo,hi) for(int v=(lo);v<(hi);++v)

double markov[MAXN][MAXN], mat1[MAXN], mat2[MAXN];

void gemv(double (&from)[MAXN], double (&with)[MAXN][MAXN], double (&to)[MAXN], int N) {
	memset(to, 0, sizeof(double)*N);
	FOR(j,0,N) FOR(k,0,N) to[k] += from[j] * with[j][k];
}

double (&solve(int days, int N, int P))[MAXN] {
	memcpy(mat1,markov[P],sizeof(double)*N);
	
	for (int i=1;i<days;++i) {
		if (i % 2 == 1) gemv(mat1,markov,mat2,N);
		else gemv(mat2,markov,mat1,N);
	}
	return (days % 2 == 1 ? mat1 : mat2);
}

int main() {
	int C, N, D, P, T, sum, tmp;
	cin >> C;
	cout << setprecision(8) << fixed;
	while (C--) {
		cin >> N >> D >> P;
		FOR(i,0,N) {
			sum = 0;
			FOR(j,0,N) {
				cin >> tmp;
				markov[i][j] = tmp;
				sum += tmp;
			}
			FOR(j,0,N) markov[i][j] /= sum;
		}
		cin >> T;
		vector<int> targets = vector<int>(T,0);
		FOR(i,0,T) cin >> targets[i];

		double (&out)[MAXN] = solve(D,N,P);
		FOR(tgt,0,T-1) cout << out[targets[tgt]] << ' ';
		cout << out[targets[T-1]] << endl;
	}
	return 0;
}
