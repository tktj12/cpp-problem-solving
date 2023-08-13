#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 87654321;
int N, E;

vector<int> Dijkstra(int start, vector<vector<pair<int,int> > >& edge)
{
	vector<int> dist(N + 1, INF);
	dist[start] = 0;

	priority_queue<pair<int, int> > pq;
	pq.push({ 0,start });

	while (!pq.empty()) {
		int here = pq.top().second;
		int d = -pq.top().first;
		pq.pop();
		if (dist[here] < d) continue;

		for (pair<int, int>& e : edge[here]) {
			int there = e.first;
			int to_there = d + e.second;
			if (dist[there] > to_there) {
				dist[there] = to_there;
				pq.push({ -to_there, there });
			}
		}
	}
	return dist;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> N >> E;
	vector<vector<pair<int,int> > > edge(N+1);
	for (int i = 0; i < E; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		edge[u].push_back({ v,w });
		edge[v].push_back({ u,w });
	}

	int v1, v2;
	cin >> v1 >> v2;

	vector<int> dist_v1 = Dijkstra(v1,edge);
	vector<int> dist_v2 = Dijkstra(v2,edge);

	int ans = min(dist_v1[1] + dist_v1[v2] + dist_v2[N],
		dist_v2[1] + dist_v1[v2] + dist_v1[N]);
	if (ans >= INF)
		cout << -1;
	else cout << ans;

	return 0;
}