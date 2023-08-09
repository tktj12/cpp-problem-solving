#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

const int INF = -1;
int shortest[20001];
void Dijkstra(int start, vector<vector<pair<int, int> > >& adj)
{
	memset(shortest, -1, sizeof(shortest));

	shortest[start] = 0;
	// 경로의 길이, 정점 쌍
	priority_queue<pair<int, int> > pq;
	pq.push({ 0,start });

	while (!pq.empty()) {
		int here = pq.top().second;
		int to_here = -pq.top().first;
		pq.pop();
		if (shortest[here] < to_here) continue;

		for (pair<int, int>& e : adj[here]) {
			int there = e.first;
			int to_there = to_here + e.second;
			if (shortest[there] == INF || shortest[there] > to_there) {
				shortest[there] = to_there;
				pq.push({ -to_there, there });
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
	int start;
	cin >> start;

	// 인접 정점, 가중치 쌍
	vector<vector<pair<int, int> > > adj(vertex_size+1);

	for (int i = 0; i < edge_size; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].push_back({ v,w });
	}
	Dijkstra(start, adj);

	for (int i = 1; i <= vertex_size; i++) {
		if (shortest[i] == INF)
			cout << "INF\n";
		else
			cout << shortest[i] << '\n';
	}

	return 0;
}