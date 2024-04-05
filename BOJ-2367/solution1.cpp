#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int SOURCE = 0,SINK = 1,INF = 987654321;
int N,K,D;
int remain[302][302];
vector<int> edge[302];
int NetworkFlow(const int source,const int sink,const int sz)
{
	int total_flow = 0;
	while (true) {
		// 너비 우선 탐색으로 증가 경로 탐색
		vector<int> parent(sz,-1);
		vector<int> parent_sink;
		queue<int> q;
		parent[source] = source;
		q.push(source);
		while (!q.empty()) {
			int here = q.front(); q.pop();
			for (int there : edge[here]) {
				// 잔여 용량이 남아 있는 간선을 따라 탐색
				if (remain[here][there] > 0) {
					if (there == sink) {
						parent_sink.push_back(here);
					}
					else if (parent[there] == -1) {
						q.push(there);
						parent[there] = here;
					}
				}
			}
		}
		// 증가 경로가 없으면 종료
		if (parent_sink.empty()) break;

		for (int i : parent_sink) {
			parent[sink] = i;
			// 증가 경로를 통해 유량을 얼마나 보낼지 결정
			int amount = INF;
			for (int p = sink; p != source; p = parent[p])
				amount = min(amount,remain[parent[p]][p]);

			// 증가 경로를 통해 유량을 보낸다.
			for (int p = sink; p != source; p = parent[p]) {
				remain[parent[p]][p] -= amount;
				remain[p][parent[p]] += amount;
			}
			total_flow += amount;
		}
	}
	return total_flow;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> N >> K >> D;
	int idx = SINK + 1;
	for (int i = 0; i < D; i++) {
		int n; cin >> n;
		edge[idx].push_back(SINK);
		edge[SINK].push_back(idx);
		remain[idx++][SINK] = n;
	}
	for (int i = 0; i < N; i++) {
		edge[idx].push_back(SOURCE);
		edge[SOURCE].push_back(idx);
		remain[SOURCE][idx] = K;
		int Z; cin >> Z;
		for (int j = 0; j < Z; j++) {
			int recipe; cin >> recipe;
			recipe++;
			edge[idx].push_back(recipe);
			edge[recipe].push_back(idx);
			remain[idx][recipe] = 1;
		}
		idx++;
	}
	cout << NetworkFlow(SOURCE,SINK,idx);

	return 0;
}