#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> edge;
vector<pair<int, int>> ans;
vector<int> discovered;
int discover_cnt;

int DFS(int parent, int now)
{
	int ret = discovered[now] = discover_cnt++;

	for (int e : edge[now]) {
		if (e == parent) continue;
		else if (discovered[e] == -1) {
			int cand = DFS(now, e);
			if (cand > discovered[now]) {
				int u = now, v = e;
				if (u > v) swap(u, v);
				ans.push_back({ u,v });
			}
			else
				ret = min(ret, cand);
		}
		else
			ret = min(ret, discovered[e]);
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
	edge = vector<vector<int>>(v + 1);
	discovered = vector<int>(v + 1, -1);
	ans.reserve(e);

	for (int i = 0; i < e; i++) {
		int u, v;
		cin >> u >> v;
		edge[u].push_back(v);
		edge[v].push_back(u);
	}

	DFS(0, 1);
	sort(ans.begin(), ans.end());
	cout << ans.size() << '\n';
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i].first << ' ' << ans[i].second << '\n';

	
	return 0;
}