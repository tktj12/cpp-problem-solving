#include <iostream>
#include <vector>
using namespace std;

const int INF = 987654321;
int depth[100001];
int anc_table[100001][17], max_road[100001][17], min_road[100001][17];
vector<vector<pair<int,int>>> adj;

void MakeTree(int n,int root,int len, int d)
{
	depth[n] = d;
	anc_table[n][0] = root;
	max_road[n][0] = min_road[n][0] = len;

	for (pair<int,int>& e : adj[n])
		if (e.first != root)
			MakeTree(e.first,n,e.second,d+1);
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);
	
	int N,K;
	cin >> N;
	adj = vector<vector<pair<int,int>>>(N + 1);
	for (int i = 1; i < N; i++) {
		int u,v,d;
		cin >> u >> v >> d;
		adj[u].push_back({ v,d });
		adj[v].push_back({ u,d });
	}

	MakeTree(1,0,0,0);

	for(int e=1;e<17;e++)
		for (int i = 1; i <= N; i++) {
			anc_table[i][e] = anc_table[anc_table[i][e - 1]][e - 1];
			min_road[i][e] = min(min_road[i][e - 1],min_road[anc_table[i][e - 1]][e - 1]);
			max_road[i][e] = max(max_road[i][e - 1],max_road[anc_table[i][e - 1]][e - 1]);
		}

	cin >> K;
	while (K--) {
		int u,v; cin >> u >> v;
		int min_ans = INF,max_ans = -INF;

		if (depth[u] < depth[v]) swap(u,v);
		for (int e = 16; e >= 0; e--) {
			if (depth[u] == depth[v]) break;
			
			int anc = anc_table[u][e];
			if (anc == 0 || depth[anc] < depth[v]) continue;

			min_ans = min(min_ans,min_road[u][e]);
			max_ans = max(max_ans,max_road[u][e]);
			u = anc;
		}

		if (u != v) {
			for (int e = 16; e >= 0; e--) {
				int anc_u = anc_table[u][e];
				int anc_v = anc_table[v][e];
				if (anc_u == anc_v) continue;

				min_ans = min(min_ans,min(min_road[u][e],min_road[v][e]));
				max_ans = max(max_ans,max(max_road[u][e],max_road[v][e]));
				u = anc_u;
				v = anc_v;
			}
			min_ans = min(min_ans,min(min_road[u][0],min_road[v][0]));
			max_ans = max(max_ans,max(max_road[u][0],max_road[v][0]));
		}

		cout << min_ans << ' ' << max_ans << '\n';
	}
	
	return 0;
}