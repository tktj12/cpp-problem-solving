#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class UnionFind {
public:
	vector<int> parent;
	UnionFind(int n) : parent(n) {
		for (int i = 0; i < n; i++) parent[i] = i;
	}

	int Find(int u) {
		if (parent[u] == u) return u;
		else return parent[u] = Find(parent[u]);
	}

	void Merge(int u, int v) {
		parent[Find(v)] = Find(u);
	}
};

int main()
{
	int n, m;
	cin >> n >> m;
	UnionFind dset(n+1);

	int knowers, knower;
	cin >> knowers;
	for (int i = 0; i < knowers; i++) {
		int who;
		cin >> who;
		if (i > 0) dset.Merge(knower, who);
		knower = who;
	}

	vector<int> party(m);
	for (int i = 0; i < m; i++) {
		int entry;
		cin >> entry;
		int prev;
		for (int j = 0; j < entry; j++) {
			int who;
			cin >> who;
			if (j > 0) dset.Merge(prev, who);
			prev = who;
		}
		party[i] = prev;
	}

	if (knowers == 0) {
		cout << m;
		return 0;
	}

	int ans = 0;
	for (int i = 0; i < m; i++)
		ans += dset.Find(party[i]) == dset.Find(knower);
	cout << m - ans;

	return 0;
}