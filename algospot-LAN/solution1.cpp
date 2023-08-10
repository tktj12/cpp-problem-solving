#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

class UnionFind {
public:
	vector<int> parent, size;
	UnionFind(int n) : parent(n), size(n,1) {
		for (int i = 0; i < n; i++)
			parent[i] = i;
	}

	int Find(int u) {
		if (parent[u] == u) return u;
		else return parent[u] = Find(parent[u]);
	}

	void Merge(int u, int v) {
		u = Find(u);
		v = Find(v);
		if (u == v) return;

		if (size[u] < size[v]) swap(u, v); // 항상 u가 더 크거나 같음

		parent[v] = u;
		if (size[u] == size[v]) size[u]++;
	}
};

inline double EuclDist(pair<int, int>& c1, pair<int, int>& c2) {
	return sqrt(pow(c1.first - c2.first, 2) + pow(c1.second - c2.second, 2));
}

double Kruskal(UnionFind& dset, vector<pair<double, pair<int, int> > >& edge)
{
	sort(edge.begin(), edge.end());

	double ret = 0;
	for (int i = 0; i < edge.size(); i++) {
		int u = edge[i].second.first;
		int v = edge[i].second.second;
		if (dset.Find(u) == dset.Find(v)) continue;

		dset.Merge(u, v);
		ret += edge[i].first;
	}

	return ret;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cout.precision(15);

	int tc;
	cin >> tc;
	while (tc--) {
		int n, m;
		cin >> n >> m;
		UnionFind dset(n);

		vector<pair<int, int> > coord(n);
		for (int i = 0; i < n; i++)
			cin >> coord[i].first;
		for (int i = 0; i < n; i++)
			cin >> coord[i].second;

		for (int i = 0; i < m; i++) {
			int u, v;
			cin >> u >> v;
			dset.Merge(u, v);
		}

		vector<pair<double, pair<int, int> > > edge;
		edge.reserve(n * n/2);

		for (int u = 0; u < n; u++)
			for (int v = u + 1; v < n; v++) {
				if (dset.Find(u) == dset.Find(v)) continue;

				double length = EuclDist(coord[u], coord[v]);
				edge.push_back({ length,{u,v} });
			}

		cout << Kruskal(dset, edge) << '\n';
	}
	return 0;
}