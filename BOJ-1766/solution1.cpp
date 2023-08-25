#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int cnt_turn[32001];
vector<int> children[32001];

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n, m;
	cin >> n >> m;
	while (m--) {
		int u, v;
		cin >> u >> v;
		children[u].push_back(v);
		cnt_turn[v]++;
	}

	priority_queue<int> pq;
	for (int i = 1; i <= n; i++)
		if (cnt_turn[i] == 0) pq.push(-i);

	while (!pq.empty()) {
		int now = -pq.top(); pq.pop();
		cout << now << ' ';
		for (int e : children[now])
			if (--cnt_turn[e] == 0)
				pq.push(-e);
	}

	return 0;
}