#include <iostream>
#include <cstring>
using namespace std;

int N;
const int MOD = 1'000'000'007;

// A = A*B
void MatrixMul(int A[20][20], int B[20][20])
{
	int result[20][20] = { 0, };
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			for (int k = 0; k < N; k++)
				result[i][j] = (result[i][j] + (long long)A[i][k] * B[k][j]) % MOD;

	memcpy(A, result, sizeof(result));
}

// A = A^e
void DAQ(int A[20][20], int e)
{
	if (e <= 1) return;
	else if (e % 2 == 1) {
		int B[20][20];
		memcpy(B, A, sizeof(B));
		DAQ(A, e - 1);
		MatrixMul(A, B);
	}
	else {
		DAQ(A, e / 2);
		int B[20][20];
		memcpy(B, A, sizeof(B));
		MatrixMul(A, B);
	}
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);
	
	int T, D;
	cin >> T >> N >> D;
	int r = D % T;

	int one_cycle_multiple[20][20] = { 0, };
	int r_multiple[20][20];
	for (int i = 0; i < N; i++)
		one_cycle_multiple[i][i] = 1;

	for (int t = 0; t < min(T,D); t++) {
		int M; cin >> M;
		int table[20][20] = { 0, };
		while (M--) {
			int u, v, k;
			cin >> u >> v >> k;
			table[u-1][v-1] = k;
		}

		MatrixMul(one_cycle_multiple, table);

		if (t == r - 1)
			memcpy(r_multiple, one_cycle_multiple, sizeof(one_cycle_multiple));
	}

	DAQ(one_cycle_multiple, D / T);
	if (D >= T && r > 0)
		MatrixMul(one_cycle_multiple, r_multiple);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			cout << one_cycle_multiple[i][j] << ' ';
		cout << '\n';
	}

	return 0;
}