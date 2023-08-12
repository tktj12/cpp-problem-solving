// ¡æ∏∏∫œ «Æ¿Ã O(|V|^3)

#include <iostream>
#include <vector>
using namespace std;

vector<int> aMatch, bMatch;
bool DFS(int a_num, vector<vector<int>>& adj, vector<bool>& visited)
{
	if (visited[a_num]) return false;
	visited[a_num] = true;

	for (int b_num : adj[a_num]) {
		if (bMatch[b_num] == -1 || DFS(bMatch[b_num], adj, visited)) {
			bMatch[b_num] = a_num;
			aMatch[a_num] = b_num;
			return true;
		}
	}

	return false;
}

int BipartiteMatch(vector<vector<int>>& adj)
{
	int ret = 0;
	for (int i = 0; i < adj.size(); i++) {
		vector<bool> visited(adj.size(),false);
		if (DFS(i, adj, visited)) ret++;
	}
	return ret;
}

vector<bool> aChosen, bChosen;
int H, W;
int dx[4] = { 1,-1,0,0 }, dy[4] = { 0,0,1,-1 };
int SetTrap(vector<string>& map)
{
	int a = 0, b = 0, vertex_size = 0;
	vector<vector<int> > id(H, vector<int>(W, -1));
	for(int i=0;i<H;i++)
		for (int j = 0; j < W; j++) {
			if (map[i][j] != '.') continue;

			vertex_size++;
			if ((i + j) % 2 > 0)
				id[i][j] = a++;
			else
				id[i][j] = b++;
		}

	vector<vector<int>> adj(a);
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++) {
			if (map[i][j] != '.') continue;
			
			if ((i + j) % 2 > 0) {
				int a_num = id[i][j];
				for (int k = 0; k < 4; k++) {
					int y = i + dy[k];
					int x = j + dx[k];
					if (y < 0 || H <= y || x < 0 || W <= x || id[y][x] == -1) continue;

					adj[a_num].push_back(id[y][x]);
				}
			}
		}

	aMatch = vector<int>(a,-1);
	bMatch = vector<int>(b,-1);
	int ret = vertex_size - BipartiteMatch(adj);

	aChosen = vector<bool>(a,true);
	bChosen = vector<bool>(b,false);

	for (int i = 0; i < b; i++)
		if (bMatch[i] == -1) bChosen[i] = true;

	while (true) {
		bool changed = false;
		for (int i = 0; i < a; i++) {
			if (aChosen[i] == false) continue;
			for (int b_num : adj[i])
				if (bChosen[b_num]) {
					aChosen[i] = false;
					bChosen[aMatch[i]] = true;
					changed = true;
					break;
				}
		}

		if (!changed) break;
	}

	for(int i=0;i<H;i++)
		for (int j = 0; j < W; j++) {
			if (map[i][j] != '.') continue;

			int _id = id[i][j];
			if ((i + j) % 2 > 0 && aChosen[_id] || (i + j) % 2 == 0 && bChosen[_id])
				map[i][j] = '^';
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
		cin >> H >> W;
		vector<string> map(H);
		for (int i = 0; i < H; i++) cin >> map[i];

		cout << SetTrap(map) << '\n';
		for (int i = 0; i < H; i++)
			cout << map[i] << '\n';
	}
	return 0;
}