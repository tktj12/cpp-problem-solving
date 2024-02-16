#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

int N,M;
char map[10][10];
int dy[6] = { -1,0,1,-1,0,1 };
int dx[6] = { -1,-1,-1,1,1,1 };
pair<int,int> aMatch[10][10],bMatch[10][10];

int group_num[10][10];
void FindGroupA(int y,int x, int g_num)
{
	group_num[y][x] = g_num;
	for (int i = 0; i < 6; i++) {
		int yy = y + dy[i];
		int xx = x + dx[i];
		if (yy < 0 || N <= yy || xx < 0 || M <= xx || map[yy][xx] != '.' || group_num[yy][xx])
			continue;
		
		FindGroupA(yy,xx,-g_num);
	}
}

bool visited[10][10];
bool DFS(int y,int x)
{
	if (visited[y][x]) return false;
	visited[y][x] = true;
	for (int i = 0; i < 6; i++) {
		int yy = y + dy[i];
		int xx = x + dx[i];
		if (yy < 0 || N <= yy || xx < 0 || M <= xx || map[yy][xx] != '.')
			continue;

		pair<int,int>& b = bMatch[yy][xx];
		if (b.first == -1 || DFS(b.first,b.second)) {
			aMatch[y][x] = b;
			b = { y,x };
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

	int tc;
	cin >> tc;
	while (tc--) {
		int flag = true;
		cin >> N >> M;
		int size = 0;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++) {
				cin >> map[i][j];
				size += map[i][j] == '.';
			}

		memset(group_num,0,sizeof(group_num));
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				if (map[i][j] == '.' && group_num[i][j] == 0)
					FindGroupA(i,j,1);

		memset(aMatch,-1,sizeof(aMatch));
		memset(bMatch,-1,sizeof(bMatch));
		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++) {
				if (map[i][j] != '.' || group_num[i][j] == -1)
					continue;

				memset(visited,0,sizeof(visited));
				if (DFS(i,j))
					--size;
			}
		cout << size << '\n';
	}
	return 0;
}