#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int N, M, a_match[1000],b_match[1001];
bool visited[1000];
vector<int> adj[1000];

bool DFS(int a) {
	if (visited[a]) return false;
	visited[a] = true;

	for (int b : adj[a]) {
		if (b_match[b] == -1 || DFS(b_match[b])) {
			a_match[a] = b;
			b_match[b] = a;
			return true;
		}
	}

	return false;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		int k; cin >> k;
		adj[i].resize(k);
		for (int j = 0; j < k; j++)
			cin >> adj[i][j];
	}

	memset(a_match,-1,sizeof(a_match));
	memset(b_match,-1,sizeof(b_match));
	int size = 0;
	for (int start = 0; start < N; ++start) {
		memset(visited,0,sizeof(visited));
		//dfs를 이용해 start에서 시작하는 증가 경로를 찾는다.
		if (DFS(start))
			++size;
	}
	cout << size;
	return 0;
}