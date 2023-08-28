#include <cstdio>
#include <vector>
using namespace std;

int N, M;
char map[1002][1002];
int group[1002][1002], cnt[1000000];
int group_cnt;
bool visited[1002][1002];

int dx[4] = { 1,-1,0,0 }, dy[4] = { 0,0,1,-1 };
int DFS(int y, int x)
{
	if (map[y][x] != '0' || visited[y][x])return 0;
	visited[y][x] = true;
	group[y][x] = group_cnt;

	int ret = 1;
	for (int i = 0; i < 4; i++)
		ret += DFS(y + dy[i], x + dx[i]);
	return ret;
}

int main()
{
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++)
		scanf("%s", map[i] + 1);

	for(int i=1;i<=N;i++)
		for(int j=1;j<=M;j++)
			if (map[i][j] == '0' && visited[i][j] == false) {
				cnt[group_cnt] = DFS(i, j);
				group_cnt++;
			}

	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			if (map[i][j] == '1') {
				vector<int> adj;
				for (int k = 0; k < 4; k++) {
					int y = i + dy[k];
					int x = j + dx[k];
					if (map[y][x] == '0' && visited[y][x])
						adj.push_back(group[y][x]);
				}

				for (int i = 0; i < adj.size(); i++)
					for (int j = i + 1; j < adj.size(); j++)
						if (adj[i] == adj[j])
							adj.erase(adj.begin() + j--);

				int sum = 0;
				for (int i = 0; i < adj.size(); i++)
					sum += cnt[adj[i]];
				sum = (sum + 1) % 10;
				map[i][j] = sum + '0';
			}

	for (int i = 1; i <= N; i++)
		printf("%s\n", map[i] + 1);

	return 0;
}