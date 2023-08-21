#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class UnionFind {
public:
	int parent[100001], size[100001];
	UnionFind() {
		for (int i = 0; i < 100001; i++)
			parent[i] = i, size[i] = 1;
	}

	int Find(int u) {
		if (parent[u] == u) return u;
		else return parent[u] = Find(parent[u]);
	}

	void Merge(int u, int v) {
		u = Find(u);
		v = Find(v);
		if (size[u] < size[v]) swap(u, v);
		parent[v] = u;
		if (size[u] == size[v]) size[u]++;
	}
};

queue<pair<int,int>> bucket[1002];
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int v_sz, e_sz;
	cin >> v_sz >> e_sz;
	for (int i = 0; i < e_sz; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		bucket[w].push({ u,v });
	}

	int cur = 1, ans = 0, last_w=0;
	UnionFind dset;
	while (1) {
		while (bucket[cur].empty() && cur <= 1000) cur++;
		if (cur > 1000) break;

		pair<int, int> fr = bucket[cur].front(); bucket[cur].pop();
		int u = fr.first, v = fr.second;
		if (dset.Find(u) == dset.Find(v)) continue;

		dset.Merge(u, v);
		last_w = cur;
		ans += cur;
	}

	cout << ans-last_w;

	return 0;
}