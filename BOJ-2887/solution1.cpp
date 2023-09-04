#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 100005;
class UnionFind {
public:
	int parent[MAXN];
	UnionFind(int n) {
		for (int i = 0; i < n; i++)
			parent[i] = i;
	}

	int Find(int n) {
		if (parent[n] == n) return n;
		else return parent[n] = Find(parent[n]);
	}

	bool Merge(int u, int v) {
		u = Find(u);
		v = Find(v);
		if (u == v) return false;
		parent[v] = u;
		return true;
	}
};

int N;
pair<int, int> coord[3][MAXN];
priority_queue<pair<int, pair<int, int>>> pq;

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> N;
	UnionFind dset(N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < 3; j++) {
			cin >> coord[j][i].first;
			coord[j][i].second = i;
		}

	for (int i = 0; i < 3; i++)
		sort(coord[i], coord[i] + N);

	for(int i=0;i<3;i++)
		for (int j = 1; j < N; j++)
			pq.push({ coord[i][j - 1].first - coord[i][j].first,{coord[i][j-1].second,coord[i][j].second} });

	long long ans = 0;
	while (!pq.empty()) {
		int u = pq.top().second.first;
		int v = pq.top().second.second;
		int w = -pq.top().first;
		pq.pop();

		if (dset.Merge(u, v))
			ans += w;
	}

	cout << ans;

	return 0;
}