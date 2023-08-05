#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

//최소로 설치해야하는 감시 카메라의 개수 반환
int GreedyInstall(int g, vector<vector<int> >& edge)
{
	int ret = 0;
	vector<bool> marked(g,false);
	queue<int> q;

	// 먼저 리프노드들의 부모노드에 감시카메라를 설치하고
	// 감시카메라를 설치하지 않은 노드들을 큐에 넣는다.
	for (int i = 0; i < g; i++) {
		if (marked[i]) continue;

		int edge_cnt = 0;
		int parent;
		for (int e  : edge[i])
			if (marked[e] == false) {
				parent = e;
				edge_cnt++;
			}

		if (edge_cnt > 1)
			q.push(i);
		else if (edge_cnt == 0)
			ret++;
		else {
			ret++;
			marked[parent] = true;
			for (int e : edge[parent])
				marked[e] = true;
		}
	}

	// 큐가 다 빌 때 까지 감시카메라를 설치한다.
	while (!q.empty()) {
		int node = q.front(); q.pop();
		if (marked[node]) continue;

		int edge_cnt = 0;
		int parent;
		for (int e : edge[node])
			if (marked[e] == false) {
				parent = e;
				edge_cnt++;
			}

		if (edge_cnt > 1)
			q.push(node);
		else if (edge_cnt == 0)
			ret++;
		else {
			ret++;
			marked[parent] = true;
			for (int e : edge[parent])
				marked[e] = true;
		}
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
		int g, h;
		cin >> g >> h;
		vector<vector<int> > edge(g);
		for (int i = 0; i < h; i++) {
			int u, v;
			cin >> u >> v;
			edge[u].push_back(v);
			edge[v].push_back(u);
		}

		cout << GreedyInstall(g, edge) << '\n';
	}
	return 0;
}