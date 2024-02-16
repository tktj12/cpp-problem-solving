// 구종만, 『프로그래밍 대회에서 배우는 알고리즘 문제해결 전략』 (서울:인사이트, 2012), 996-997
// 포드-풀커슨 알고리즘

#include <cstring>
#include <vector>
#include <queue>
using namespace std;

const int INF = 987654321, MAX_V = 100;
int V;

// capacity[u][v] : u에서 v로 보낼 수 있는 용량
int capacity[MAX_V][MAX_V]; 
// flow[u][v] : u에서 v로 흘러가는 유량 (반대 방향인 경우 음수)
int flow[MAX_V][MAX_V];		

// flow[][]를 계산하고 총 유량을 반환한다.
int NetworkFlow(int source, int sink)
{
	//flow 배열 0으로 초기화
	memset(flow, 0, sizeof(flow));
	int total_flow = 0;
	while (true) {
		// 너비 우선 탐색으로 증가 경로 탐색
		vector<int> parent(MAX_V, -1);
		queue<int> q;
		parent[source] = source;
		q.push(source);
		while (!q.empty() && parent[sink] == -1) {
			int here = q.front(); q.pop();
			for (int there = 0; there < V; ++there) {
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
			amount = min(amount, capacity[parent[p]][p] - flow[parent[p]][p]);

		// 증가 경로를 통해 유량을 보낸다.
		for (int p = sink; p != source; p = parent[p]) {
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
		}
		total_flow += amount;
	}
	return total_flow;
}