#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> edge;
vector<int> ans;
vector<int> discovered;
int discover_cnt;

// 간선으로 타고 갈 수 있는 노드 중 방문 순서가 가장 작은 노드를 반환
int DfsChild(int node)
{
	int ret = discovered[node] = discover_cnt++;

	bool cutting = false;
	for (int e : edge[node]) {
		if (discovered[e] == -1) {
			int cand = DfsChild(e);
			if (discovered[node] <= cand)
				cutting = true;
			ret = min(ret, cand);
		}
		else
			ret = min(ret, discovered[e]);
	}

	if (cutting) ans.push_back(node);
	return ret;
}

void DfsRoot(int node)
{
	discovered[node] = discover_cnt++;

	int child_cnt = 0;
	for (int e : edge[node])
		if (discovered[e] == -1) {
			child_cnt++;
			DfsChild(e);
		}

	if (child_cnt > 1)
		ans.push_back(node);
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int v, e;
	cin >> v >> e;
	edge = vector<vector<int>>(v + 1);
	discovered = vector<int>(v + 1, -1);
	ans.reserve(v);
	
	for (int i = 0; i < e; i++) {
		int u, v;
		cin >> u >> v;
		edge[u].push_back(v);
		edge[v].push_back(u);
	}

	for (int i = 1; i <= v; i++)
		if (discovered[i] == -1)
			DfsRoot(i);

	sort(ans.begin(), ans.end());
	cout << ans.size() << '\n';
	for (int e : ans)
		cout << e << ' ';

	return 0;
}