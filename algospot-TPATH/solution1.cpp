#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class UnionFind {
public:
	vector<int> parent, size;
	UnionFind(int n) : parent(n), size(n,1) {
		for (int i = 0; i < n; i++) parent[i] = i;
	}

	int Find(int u) {
		if (parent[u] == u) return u;
		else return parent[u] = Find(parent[u]);
	}

	void Merge(int u, int v) {
		u = Find(u);
		v = Find(v);
		if (u == v) return;

		if (size[u] < size[v]) swap(u, v); // 항상 size[u]가 더 크거나 같음
		parent[v] = u;
		if (size[u] == size[v]) size[u]++;
	}
};

const int INF = 987654321;
int Kruskal(int vertex_size, int begin, vector<pair<int, pair<int, int> > >& edge)
{
	UnionFind dset(vertex_size);
	for (int i = begin; i < edge.size(); i++) {
		dset.Merge(edge[i].second.first, edge[i].second.second);
		if (dset.Find(0) == dset.Find(vertex_size-1))
			return edge[i].first;
	}
	return INF;
}

int FindMinGap(int vertex_size, vector<pair<int, pair<int, int> > >& edge)
{
	sort(edge.begin(), edge.end());

	int ret = INF;
	for (int i = 0; i < edge.size(); i++) {
		ret = min(ret, Kruskal(vertex_size, i, edge) - edge[i].first);
	}
	return ret;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int vertex_size, edge_size;
		cin >> vertex_size >> edge_size;

		vector<pair<int, pair<int, int> > > edge(edge_size);
		for (int i = 0; i < edge_size; i++)
			cin >> edge[i].second.first >> edge[i].second.second >> edge[i].first;

		cout << FindMinGap(vertex_size, edge) << '\n';
	}
	return 0;
}