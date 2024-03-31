#include <iostream>
using namespace std;

int main()
{
	int N; cin >> N;
	int D[101][101] = {},C[101][101] = {};
	for (int i = 0; i < N; i++) {
		int a,b; cin >> a >> b;
		if (a > b) swap(a,b);
		D[a][b] = C[a][b] = 1;
	}

	for (int k = 2; k < 100; k++)
		for (int i = 1; i <= 100-k; i++)
			for (int j = i; j < i + k; j++)
				D[i][i + k] = max(D[i][i + k],D[i][j] + D[j + 1][i + k] + C[i][i + k]);

	cout << D[1][100];
	
	return 0;
}