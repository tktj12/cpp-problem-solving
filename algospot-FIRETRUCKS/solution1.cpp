#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

int dist[1001];
void Dijkstra(vector<vector<pair<int, int> > >& adj, vector<int>& stations)
{
	// 거리, 정점 쌍
	priority_queue<pair<int, int> > pq;

	for (int station : stations) {
		dist[station] = 0;
		pq.push({ 0, station });
	}
	
	while (!pq.empty()) {
		int here = pq.top().second;
		int station_to_here = -pq.top().first;
		pq.pop();
		if (dist[here] < station_to_here) continue;

		// 인접 정점 검사
		for (pair<int, int>& e : adj[here]) {
			int there = e.first;
			int station_to_there = station_to_here + e.second;

			if (dist[there] > station_to_there) {
				dist[there] = station_to_there;
				pq.push({ -station_to_there, there });
			}
		}
	}
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int vertex_size, edge_size, fired, station;
		cin >> vertex_size >> edge_size >> fired >> station;
		vector<vector<pair<int, int> > > adj(vertex_size+1);
		for (int i = 0; i < edge_size; i++) {
			int u, v, w;
			cin >> u >> v >> w;
			adj[u].push_back({ v,w });
			adj[v].push_back({ u,w });
		}
		//dist 배열의 모든 원소를 int max 값으로 초기화
		for (int i = 0; i <= vertex_size; i++)
			dist[i] = 0x7FFFFFFF;

		vector<int> fired_place(fired);
		for (int i = 0; i < fired; i++)
			cin >> fired_place[i];

		vector<int> stations(station);
		for (int i = 0; i < station; i++)
			cin >> stations[i];
		
		Dijkstra(adj, stations);
		
		int ans = 0;
		for (int e : fired_place)
			ans += dist[e];
		cout << ans << '\n';
	}
	return 0;
}