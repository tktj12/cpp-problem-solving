#include <iostream>
#include <vector>
using namespace std;

const int MAXN = 4'000'000;
class UnionFind {
public:
	int parent[MAXN + 1];
	UnionFind() {
		for (int i = 1; i <= MAXN; i++)
			parent[i] = i;
	}

	int Find(int n) {
		if (parent[n] == n) return n;
		else return parent[n] = Find(parent[n]);
	}

	void Merge(int u, int v) {
		parent[Find(u)] = Find(v);
	}
}dset;

bool mark[MAXN + 1];
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i < m; i++) {
		int num; cin >> num;
		mark[num] = true;
	}

	for (int i = MAXN - 1; i > 0; i--)
		if (!mark[i]) dset.Merge(i, i + 1);

	for (int i = 0; i < k; i++) {
		int his_hand; cin >> his_hand;
		int my_hand = dset.Find(his_hand + 1);
		dset.Merge(my_hand, my_hand + 1);

		cout << my_hand << '\n';
	}

	return 0;
}