/* Source: https://www.algospot.com/judge/problem/read/NUMB3RS */

#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>

using namespace std;

#define MAXN 100
#define MAXD 100
#define FOR(v,lo,hi) for(int v=(lo);v<(hi);++v)

double markov[MAXN][MAXN], mat1[MAXN][MAXN], mat2[MAXN][MAXN];

#if defined TEST || defined IOTEST
// Prints top-left len X len subarray of `arr`
void printarray(double (&arr)[MAXN][MAXN], int len) {
	cout << setprecision(8) << fixed;
	FOR(i,0,len) {
		FOR(j,0,len) cout << arr[i][j] << ' ';
		cout << endl;
	}
}
#endif

void matmul(double (&from)[MAXN][MAXN], double (&with)[MAXN][MAXN], double (&to)[MAXN][MAXN], int N) {
	memset(to, 0, sizeof(double)*MAXN*MAXN);
	FOR(i,0,N) FOR(j,0,N) FOR(k,0,N) to[i][k] += from[i][j] * with[j][k];
}

// Return P^th row of matmul result M^days
double (&solve(int days, int N, int P))[MAXN] {
	memcpy(mat1,markov,sizeof(double)*MAXN*MAXN);
	
	for (int i=1;i<days;++i) {
		if (i % 2 == 1) matmul(mat1,markov,mat2,N);
		else matmul(mat2,markov,mat1,N);
	}
	return (days % 2 == 1 ? mat1 : mat2)[P];
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
#ifdef IOTEST
		printarray(markov,N);
#endif

		double (&out)[MAXN] = solve(D,N,P);
#ifdef TEST
		if (D % 2 == 1) printarray(mat1,N);
		else printarray(mat2,N);
#endif
		FOR(tgt,0,T-1) cout << out[targets[tgt]] << ' ';
		cout << out[targets[T-1]] << endl;
	}
	return 0;
}
