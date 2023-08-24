#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int r = 0, c = 1,INF = 0x7FFFFFFF;
int M[500][2], DP[500][500];

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n; cin >> n;
	for (int i = 0; i < n; i++) cin >> M[i][r] >> M[i][c];

	for(int range=1;range<n;range++)
		for (int i = 0; i < n-range; i++) {
			int j = i + range;
			int tp = M[i][r] * M[j][c];
			DP[i][j] = INF;

			for (int p = i; p < j; p++)
				DP[i][j] = min(DP[i][j], DP[i][p] + DP[p + 1][j] + tp * M[p][c]);
		}
				
	cout << DP[0][n - 1];

	return 0;
}