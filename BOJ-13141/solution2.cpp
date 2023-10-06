#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int INF = 987654321;
int shortest[201][201], longest[201][201], N, M;

int main()
{
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);
	
	memset(shortest, 1, sizeof(shortest));

	cin >> N >> M;
	for (int i = 1; i <= N; i++) shortest[i][i] = 0;

	for (int i = 0; i < M; i++) {
		int v1, v2, l;
		cin >> v1 >> v2 >> l;
		l *= 2;
		shortest[v1][v2] = min(shortest[v1][v2], l);
		shortest[v2][v1] = min(shortest[v2][v1], l);
		longest[v1][v2] = max(longest[v1][v2], l);
		longest[v2][v1] = max(longest[v2][v1], l);
	}

	for (int k = 1; k <= N; k++)
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				shortest[i][j] = min(shortest[i][j], shortest[i][k] + shortest[k][j]);

	int ans = INF;
	for (int i = 1; i <= N; i++) {
		int burn_t = 0;
		for (int j = 1; j <= N; j++) {
			for (int k = j; k <= N; k++) {
				if (!longest[j][k]) continue;
				burn_t = max(burn_t, max(shortest[i][j], shortest[i][k]) + (longest[j][k] - abs(shortest[i][j] - shortest[i][k]) ) / 2 );
			}
		}

		ans = min(ans, burn_t);
	}

	cout << fixed;
	cout.precision(1);
	cout << ans / 2.;

	return 0;
}