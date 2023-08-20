#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<pair<int,int>>> edge;
bool visited[10001];

int CalcMstWeight(int start)
{
	// 가중치, 정점 쌍
	priority_queue<pair<int, int>> pq;
	pq.push({ 0,start });

	int ret = 0;
	while (!pq.empty()) {
		int now = pq.top().second;
		int w = -pq.top().first;
		pq.pop();
		if (visited[now]) continue;
		visited[now] = true;
		ret += w;

		for (pair<int, int>& e : edge[now])
			if (!visited[e.first])
				pq.push({ -e.second,e.first });
	}
	return ret;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int v, e;
	cin >> v >> e;
	edge = vector<vector<pair<int,int>>>(v + 1);

	for (int i = 0; i < e; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		edge[a].push_back({ b,c, });
		edge[b].push_back({ a,c, });
	}

	cout << CalcMstWeight(1);

	return 0;
}