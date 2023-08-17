#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

vector<vector<int>> edge, scc_group;
vector<int> discovered, scc_id;
int scc_cnt, discover_cnt;
stack<int> st;

int DFS(int here)
{
	int ret = discovered[here] = discover_cnt++;
	st.push(here);

	for (int there : edge[here]) {
		if (discovered[there] == -1)
			ret = min(ret, DFS(there));
		else if (scc_id[there] == -1)
			ret = min(ret, discovered[there]);
	}

	if (ret == discovered[here]) {
		scc_group.push_back({});
		while (1) {
			int t = st.top(); st.pop();
			scc_group.back().push_back(t);
			scc_id[t] = scc_cnt;
			if (t == here) break;
		}
		scc_cnt++;
	}

	return ret;
}

void GroupToScc(int vertex_sz)
{
	scc_cnt = discover_cnt = 0;
	discovered = scc_id = vector<int>(vertex_sz,-1);

	for (int i = 1; i < vertex_sz; i++)
		if (discovered[i] == -1)
			DFS(i);

	for (int i = 0; i < scc_group.size(); i++)
		sort(scc_group[i].begin(), scc_group[i].end());
	sort(scc_group.begin(), scc_group.end());
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int vertex_sz, edge_sz;
	cin >> vertex_sz >> edge_sz;
	edge = vector<vector<int>>(vertex_sz+1);

	for (int i = 0; i < edge_sz; i++) {
		int u, v;
		cin >> u >> v;
		edge[u].push_back(v);
	}
	GroupToScc(vertex_sz+1);

	cout << scc_cnt << '\n';
	for (int i = 0; i < scc_group.size(); i++) {
		for (int j : scc_group[i])
			cout << j << ' ';
		cout << "-1\n";
	}

	return 0;
}