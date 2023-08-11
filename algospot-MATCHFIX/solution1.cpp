#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

const int INF = 987654321;
int NetworkFlow(vector<vector<int> >& capacity, int source, int sink)
{
	int n = capacity.size();
	vector<vector<int> > flow(n, vector<int>(n));

	int total_flow = 0;
	while (true) {
		vector<int> parent(n, -1);
		queue<int> q;

		parent[source] = source;
		q.push(source);
		while (!q.empty() && parent[sink] == -1) {
			int here = q.front(); q.pop();

			for (int there = 0; there < n; there++) {
				int remain = capacity[here][there] - flow[here][there];
				if (remain > 0 && parent[there] == -1) {
					parent[there] = here;
					q.push(there);
				}
			}
		}

		if (parent[sink] == -1) break;

		int amount = INF;
		for (int p = sink; p != source; p = parent[p])
			amount = min(amount, capacity[parent[p]][p] - flow[parent[p]][p]);

		for (int p = sink; p != source; p = parent[p]) {
			flow[parent[p]][p] += amount;
			flow[p][parent[p]] -= amount;
		}
		total_flow += amount;
	}

	return total_flow;
}

int Solve(int begin, int end, int total_score, vector<vector<int> >& capacity)
{
	// X의 최대 승점이 다른 선수의 현재 승점 이하라면 X가 단독 우승할 수 없음
	if(begin > end) return -1;

	int n = capacity.size();
	for (int now_x = begin; now_x <= end; now_x++) {
		capacity[2][1] = now_x;
		for (int i = 3; i < n; i++)
			capacity[i][1] = now_x - 1;

		if (NetworkFlow(capacity, 0, 1) == total_score)
			return now_x;
	}
	return -1;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int n, match;
		cin >> n >> match;
		// 0번이 source, 1번이 sink
		vector<vector<int> > capacity(n+2, vector<int>(n+2,0));

		int max_score = 0, total_score=0;
		for (int i = 0; i < n; i++) {
			int win;
			cin >> win;
			// source에서 i번 선수한테 win만큼 승점을 줌
			capacity[0][i + 2] = win;
			if(i>0)	max_score = max(max_score, win);
			total_score += win;
		}
		int x = capacity[0][2];

		for (int i = 0; i < match; i++) {
			int a, b;
			cin >> a >> b;
			if (a > b) swap(a, b); // 항상 a가 더 작음

			// 일단 a한테 승점 주고 간선 (a,b)의 용량을 1 늘림
			capacity[0][a + 2]++;
			capacity[a+2][b + 2]++;
		}

		cout << Solve(max(max_score + 1, x), capacity[0][2], total_score + match, capacity) << '\n';
	}
	return 0;
}