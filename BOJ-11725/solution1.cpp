#include <iostream>
#include <list>
using namespace std;

list<int> edge[100010];
int answer[100010];
int N;

void DFS(int node)
{
	for (auto iter = edge[node].begin(); iter != edge[node].end(); iter++) {
		int v = *iter;
		if (answer[v] == 0) {
			answer[v] = node;
			DFS(v);
		}
	}
}


int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	answer[1] = -1;

	int n;
	cin >> n;
	n;
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	DFS(1);
	for (int i = 2; i <= n; i++)
		cout << answer[i] << '\n';

	return 0;
}