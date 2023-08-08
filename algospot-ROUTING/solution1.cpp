#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <cmath>
using namespace std;

double Dijkstra(int vertex_size, vector<vector<pair<int, double> > >& adj)
{
	vector<double> min_noise(vertex_size, INFINITY);
	min_noise[0] = 1.;

	priority_queue<pair<double, int> > pq;
	pq.push({ -1., 0 });
	while (!pq.empty()) {
		int here = pq.top().second;
		double total_noise = -pq.top().first;
		pq.pop();

		// 인접한 정점 모두 탐색
		for (pair<int,double>& e : adj[here]) {
			int there = e.first;
			double noise = e.second * total_noise;
			if (min_noise[there] > noise) {
				min_noise[there] = noise;
				pq.push({-noise, there});
			}
		}
	}

	return min_noise.back();
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cout << fixed;
	cout.precision(10);

	int tc;
	cin >> tc;
	while (tc--) {
		int vertex_size, edge_size;
		cin >> vertex_size >> edge_size;

		// adj[i] : i번 정점의 인접 정점들의 정보, (정점 번호, 가중치) 쌍
		vector<vector<pair<int, double> > > adj(vertex_size);
		for (int i = 0; i < edge_size; i++) {
			int u, v;
			double w;
			cin >> u >> v >> w;
			adj[u].push_back({ v,w });
			adj[v].push_back({ u,w });
		}

		cout << Dijkstra(vertex_size, adj) << '\n';
	}
	return 0;
}