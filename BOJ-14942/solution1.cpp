#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int energy[100001], depth[100001];
int ancestor_table[100001][17];
vector<vector<pair<int, int>>> edges;

bool visited[100001];
void DFS(int node, int d)
{
	visited[node] = true;
	depth[node] = d;
	for (auto e : edges[node]) {
		int no = e.first;
		if (visited[no]) continue;
		int dist = e.second;

		ancestor_table[no][0] = node;
		DFS(no, d + dist);
	}
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> energy[i];

	edges = vector<vector<pair<int, int>>>(n + 1);
	for (int i = 1; i < n; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		edges[u].push_back({ v,c });
		edges[v].push_back({ u,c });
	}

	DFS(1, 0);

	//fill table
	for (int j = 1; j < 17; j++)
		for (int i = 1; i <= n; i++)
			ancestor_table[i][j] = ancestor_table[ancestor_table[i][j - 1]][j - 1];

	for (int i = 1; i <= n; i++) {
		int now_no = i;
		int now_depth = depth[i];
		int now_energy = energy[i];
		for (int j = 16; j >= 0; j--) {
			if (now_no == 1) break;

			int ancestor = ancestor_table[now_no][j];
			if (ancestor == 0) continue;

			if (now_depth - depth[ancestor] <= now_energy) {
				now_energy -= now_depth - depth[ancestor];
				now_depth = depth[ancestor];
				now_no = ancestor;
			}
		}
		cout << now_no << '\n';
	}

	return 0;
}