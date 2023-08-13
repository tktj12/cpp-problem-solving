#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 987654321;
int Dijkstra(int start, int destination, vector<vector<pair<int, int> > >& edge)
{
	vector<int> dist(edge.size(), INF);

	// 최단 거리, 정점 쌍
	priority_queue<pair<int, int> > pq;
	pq.push({ 0,start });
	dist[start] = 0;

	while (!pq.empty()) {
		int here = pq.top().second;
		int cost = -pq.top().first;  pq.pop();

		if (dist[here] < cost) continue;

		for (int i = 0; i < edge[here].size(); i++) {
			int there = edge[here][i].first;
			int to_there = cost + edge[here][i].second;

			if (dist[there] > to_there) {
				pq.push({ -to_there, there });
				dist[there] = to_there;
			}
		}
	}
	return dist[destination];
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int vertex_size, edge_size;
	cin >> vertex_size >> edge_size;

	vector<vector<pair<int, int> > > edge(vertex_size+1);

	for (int i = 0; i < edge_size; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		edge[u].push_back({ v,w });
	}
	int s, d;
	cin >> s >> d;
	cout << Dijkstra(s, d, edge);

	return 0;
}