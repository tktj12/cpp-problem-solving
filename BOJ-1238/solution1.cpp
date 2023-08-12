#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int INF = 987654321;
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n, m, x;
	cin >> n >> m >> x;
	vector<vector<int> > path(n+1, vector<int>(n+1, INF));
	
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		path[u][v] = w;
	}

	for (int i = 1; i <= n; i++)
		path[i][i] = 0;

	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				path[i][j] = min(path[i][j], path[i][k] + path[k][j]);

	int ans = 0;
	for (int i = 1; i <= n; i++)
		ans = max(ans, path[i][x] + path[x][i]);

	cout << ans;

	return 0;
}