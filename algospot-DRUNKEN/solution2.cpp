#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

inline int Max3(int a, int b, int c) {
	return max(a, max(b, c));
}

const int INF = 987654321;
int delay[501];					// i번 장소에서 걸리는 단속 시간
int path[501][501];				// path[u][v] : u에서 v로 가는 경로의 최단시간, 못 찾았다면 INF
int path_with_delay[501][501];	// path_with_delay[u][v] : u에서 v로 가는 최대 딜레이를 포함한 경로 중 최단시간

void Floyd(int vertex_size)
{
	vector<pair<int, int> > sorted_by_delay(vertex_size);
	for (int i = 1; i <= vertex_size; i++)
		sorted_by_delay[i-1] = { delay[i],i };
	sort(sorted_by_delay.begin(), sorted_by_delay.end());

	for (pair<int, int>& e : sorted_by_delay) {
		int k = e.second;
		for (int i = 1; i <= vertex_size; i++) {
			if (path[i][k] == INF) continue;
			for (int j = 1; j <= vertex_size; j++) {
				path[i][j] = min(path[i][j], path[i][k] + path[k][j]);

				path_with_delay[i][j] = min(path_with_delay[i][j],
					path[i][k] + path[k][j] + delay[k]);
			}
		}
	}
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int vertex_size, edge_size;
	cin >> vertex_size >> edge_size;
	for (int u = 1; u <= vertex_size; u++) {
		cin >> delay[u];
		for (int v = 1; v <= vertex_size; v++) {
			path_with_delay[u][v] = path[u][v] = INF;
		}
		path_with_delay[u][u] = path[u][u] = 0;
	}

	for (int i = 0; i < edge_size; i++) {
		int u, v, cost;
		cin >> u >> v >> cost;
		path[u][v] = path[v][u] = cost;
		path_with_delay[u][v] = path_with_delay[v][u] = cost;
	}
	Floyd(vertex_size);

	int tc;
	cin >> tc;
	while (tc--) {
		int u, v;
		cin >> u >> v;
		cout << path_with_delay[u][v] << '\n';
	}
	return 0;
}