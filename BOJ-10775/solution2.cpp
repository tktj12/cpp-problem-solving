#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MX = 100000;
class UnionFind {
public:
	int parent[MX + 1], size[MX + 1] = { 0, };
	UnionFind() {
		for (int i = 0; i <= MX; i++)
			parent[i] = i;
	}

	int Find(int u) {
		if (parent[u] == u) return u;
		return parent[u] = Find(parent[u]);
	}

	bool Merge(int u, int v) {
		u = Find(u);
		v = Find(v);
		if (u == v) return false;
		parent[v] = u;
		size[u] += size[v];
		return true;
	}
}dset;

bool Docking(int n)
{
	n = dset.Find(n);
	while(dset.Merge(n,n - dset.size[n]));
	return ++dset.size[n] <= n;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n, p;
	cin >> n >> p;

	bool able = true;
	int ans = 0;
	for (int i = 0; i < p; i++) {
		int n; cin >> n;
		if (able) {
			able = Docking(n);
			ans += able;
		}
	}

	cout << ans;

	return 0;
}