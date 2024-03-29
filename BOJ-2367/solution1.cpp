#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int SOURCE = 0,SINK = 1, INF=987654321;
int N,K,D;
int capacity[302][302],flow[302][302];
int NetworkFlow(int source,int sink, int sz)
{
	int total_flow = 0;
	while (true) {
		// 너비 우선 탐색으로 증가 경로 탐색
		vector<int> parent(sz,-1);
		queue<int> q;
		parent[source] = source;
		q.push(source);
		while (!q.empty() && parent[sink] == -1) {
			int here = q.front(); q.pop();
			for (int there = 0; there < sz; ++there) {
				// 잔여 용량이 남아 있는 간선을 따라 탐색
				if (capacity[here][there] - flow[here][there] > 0 && parent[there] == -1) {
					q.push(there);
					parent[there] = here;
				}
			}
		}
		// 증가 경로가 없으면 종료
		if (parent[sink] == -1) break;
		// 증가 경로를 통해 유량을 얼마나 보낼지 결정
		int amount = INF;
		for (int p = sink; p != source; p = parent[p])
			amount = min(amount,capacity[parent[p]][p] - flow[parent[p]][p]);

		// 증가 경로를 통해 유량을 보낸다.
		for (int p = sink; p != source; p = parent[p]) {
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
		}
		total_flow += amount;
	}
	return total_flow;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> N >> K >> D;
	int idx = SINK+1;
	for (int i = 0; i < D; i++) {
		int n; cin >> n;
		capacity[idx++][SINK] = n;
	}
	for (int i = 0; i < N; i++) {
		capacity[SOURCE][idx] = K;
		int Z; cin >> Z;
		for (int j = 0; j < Z; j++) {
			int recipe; cin >> recipe;
			capacity[idx][recipe+1] = 1;
		}
		idx++;
	}
	cout << NetworkFlow(SOURCE,SINK,idx);

	return 0;
}