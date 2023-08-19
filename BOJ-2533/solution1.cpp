#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int NOTADAPTOR = 0, ADAPTOR = 1;
vector<vector<int>> edge;
vector<bool> visit;
int answer;

int DFS(int here)
{
	visit[here] = true;

	bool not_adaptor = false;
	for (int e : edge[here])
		if (!visit[e] && DFS(e) == NOTADAPTOR)
			not_adaptor = true;
			
	if (not_adaptor) {
		answer++;
		return ADAPTOR;
	}
	else return NOTADAPTOR;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n;
	cin >> n;
	edge = vector<vector<int>>(n + 1);
	visit = vector<bool>(n + 1);
	for (int i = 1; i < n; i++) {
		int u, v;
		cin >> u >> v;
		edge[u].push_back(v);
		edge[v].push_back(u);
	}
	DFS(1);
	cout << answer;

	return 0;
}