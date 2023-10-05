// 모든 간선의 중간에 새 노드를 만든다.
// 기존 노드들마다 다익스트라 알고리즘을 수행한다.
// 다익스트라 결과 가장 긴 최단거리가 가장 짧은 노드를 시작점으로 선택한다.
// 이 시작점을 시작으로 시뮬레이션을 돌려서 모든 그래프를 태우는 시간을 구한다.

// 예외 1. 마지막 노드에 도착했지만 다른 간선이 아직도 타고 있는 경우.

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 987654321;
int origin_node, all_node;
vector<vector<pair<int, int>>> adj(20201);

int Dijkstra(int s)
{
	vector<int> arrival_time(all_node, INF);
	arrival_time[s] = 0;

	priority_queue<pair<int, int>> pq;
	pq.push({ 0,s });

	int ret = 0;
	while (!pq.empty()) {
		int here = pq.top().second;
		int d = -pq.top().first;
		pq.pop();

		if (arrival_time[here] < d) continue;

		for (pair<int, int>& e : adj[here]) {
			int there = e.first;
			int to_there = d + e.second;

			if (arrival_time[there] > to_there) {
				arrival_time[there] = to_there;
				ret = max(ret, to_there);
				pq.push({ -to_there,there });
			}
			else {
				ret = max(ret, arrival_time[here] + (e.second - arrival_time[here] + arrival_time[there]) / 2);
			}
		}
	}

	return ret;
}

int main()
{
	cin.tie(0), cout.tie(0);
	ios::sync_with_stdio(0);

	int origin_node, edge_cnt;
	cin >> origin_node >> edge_cnt;

	all_node = origin_node + 1;
	for (int i = 0; i < edge_cnt; i++) {
		int u, v, l;
		cin >> u >> v >> l;

		adj[u].push_back({ all_node, l });
		adj[all_node].push_back({ u, l });

		adj[v].push_back({ all_node, l });
		adj[all_node].push_back({ v, l });

		all_node++;
	}
	// 간선의 최대 개수는 80,000개

	int ans = INF;
	for (int i = 1; i <= origin_node; i++) {
		ans = min(ans, Dijkstra(i));
	}

	cout << fixed;
	cout.precision(1);
	cout << ans / 2.;

	return 0;
}