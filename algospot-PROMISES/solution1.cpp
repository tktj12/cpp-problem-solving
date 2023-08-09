#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int INF = 987654321;
void Floyd(vector<vector<int>>& path)
{
	int V = path.size();
	for (int k = 0; k < V; k++)
		for (int i = 0; i < V; i++)
			for (int j = 0; j < V; j++)
				path[i][j] = min(path[i][j], path[i][k] + path[k][j]);
}

// u와 v를 w길이로 잇고 바뀐 최단 길이를 전부 계산한다.
// 해당 도로가 필요 없으면 false를 반환한다.
bool Insert(int u, int v, int w, vector<vector<int>>& path)
{
	if (path[u][v] <= w) return false;
	path[u][v] = w;

	int V = path.size();
	for (int i = 0; i < V; i++)
		path[i][u] = path[u][i] = min(path[u][i], path[u][v] + path[v][i]);

	for (int i = 0; i < V; i++)
		for (int j = 0; j < V; j++)
			path[j][i] = min(path[j][i], path[j][u] + path[u][i]);
	return true;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int vertex_size, edge_size, insertion;
		cin >> vertex_size >> edge_size >> insertion;
		vector<vector<int>> path(vertex_size, vector<int>(vertex_size,INF));

		for (int i = 0; i < edge_size; i++) {
			int u, v, w;
			cin >> u >> v >> w;
			path[u][v] = path[v][u] = min(path[u][v],w);
		}
		Floyd(path);

		int ans = 0;
		for (int i = 0; i < insertion; i++) {
			int u, v, w;
			cin >> u >> v >> w;
			ans += !Insert(u, v, w, path);
		}
		cout << ans << '\n';
	}
	return 0;
}