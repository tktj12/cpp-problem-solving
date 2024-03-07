#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MOD = 1'000'003;
int N,S,E,T,V;
int mat[50][50];

void MatMul(int a[][50],int b[][50]) {
	int res[50][50] = { 0, };
	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			for (int k = 0; k < V; k++)
				res[i][j] = (res[i][j] + (long long)a[i][k] * b[k][j]) % MOD;

	memcpy(a,res,sizeof(res));
}

void MatPow(int a[][50],int e) {
	int tp[50][50];
	if (e <= 1) return;
	else if (e % 2 > 0) {
		memcpy(tp,a,sizeof(tp));
		MatPow(a,e - 1);
		MatMul(a,tp);
	}
	else {
		MatPow(a,e / 2);
		memcpy(tp,a,sizeof(tp));
		MatMul(a,tp);
	}
}

int main()
{
	for (int i = 0; i < 10; i++)
		for (int j = 1; j <= 4; j++)
			mat[5 * i + j][5 * i + j - 1] = 1;

	cin >> N >> S >> E >> T;
	V = 5 * N;
	S--,E--;
	for (int i = 0; i < N; i++) {
		char s[11];
		cin >> s;
		for (int j = 0; j < N; j++) {
			int l = s[j] -= '0';
			if (0 < l && l <= 5)
				mat[5 * i][5 * j + l - 1] = 1;
		}
	}

	MatPow(mat,T);
	cout << mat[5 * S][5 * E];

	return 0;
}