#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

bool BellmanFord(int vertex_size, vector<vector<pair<int, double>>>& edge)
{
	vector<double> dist(vertex_size, 0);
	dist[0] = 0;
	bool updated = false;
	for (int k = 0; k < vertex_size; k++) {
		updated = false;

		for(int i=0;i<vertex_size;i++) {
			for (int j = 0; j < edge[i].size(); j++) {
				int there = edge[i][j].first;
				double w = edge[i][j].second;

				if (dist[i] + w < dist[there]) {
					updated = true;
					dist[there] = dist[i] + w;
				}
			}
		}
		if (!updated) break;
	}
	if (updated) return false;
	else return true;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int vertex_size, edge_size, wormhall;
		cin >> vertex_size >> edge_size >> wormhall;

		
		// 인접 정점, 가중치 쌍
		vector<vector<pair<int, double> > > edge(vertex_size);
		for (int i = 0; i < edge_size; i++) {
			int u, v;
			double w;
			cin >> u >> v >> w;
			edge[u - 1].push_back({ v - 1, w });
			edge[v - 1].push_back({ u - 1, w });
		}
		for (int i = 0; i < wormhall; i++) {
			int u, v;
			double w;
			cin >> u >> v >> w;
			edge[u - 1].push_back({ v - 1, -w });
		}

		cout << (BellmanFord(vertex_size, edge) ? "NO\n" : "YES\n");
	}
	return 0;
}