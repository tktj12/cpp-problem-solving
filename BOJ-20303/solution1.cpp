#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MX = 30001;
int candy[MX];
class UnionFind {
public:
	int parent[MX], size[MX], height[MX];
	UnionFind() {
		for (int i = 1; i < MX; i++)
			parent[i] = i, size[i] = 1, height[i]=1;
	}

	int Find(int u) {
		if (parent[u] == u) return u;
		else return parent[u] = Find(parent[u]);
	}

	void Merge(int u, int v) {
		u = Find(u);
		v = Find(v);
		if (u == v) return;
		if (height[u] < height[v]) swap(u, v);
		else if (height[u] == height[v]) height[u]++;
		parent[v] = u;
		size[u] += size[v];
		candy[u] += candy[v];
	}
}dset;

int group[MX], group_candy[MX], DP[3000];
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) cin >> candy[i];
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		dset.Merge(u, v);
	}

	int group_cnt = 0;
	bool found[MX] = { 0, };
	for (int i = 1; i <= n; i++) {
		int p = dset.Find(i);
		if (found[p] == false) {
			found[p] = true;
			group[group_cnt] = dset.size[p];
			group_candy[group_cnt++] = candy[p];
		}
	}

	for (int i = 0; i < group_cnt; i++)
		for (int cry = k-1; cry >= group[i]; cry--)
			DP[cry] = max(DP[cry], DP[cry - group[i]] + group_candy[i]);

	cout << DP[k - 1];

	return 0;
}