#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int black, white;
int dx[4] = { 1,-1,0,0 }, dy[4] = { 0,0,1,-1 };
int H, W;
void DFS(int y, int x, int mode, vector<vector<int>>& visited, vector<string>& map)
{
	if (y < 0 || H <= y || x < 0 || W <= x || map[y][x] != '.' || visited[y][x] > mode) return;
	visited[y][x] = mode+1;

	if (mode == 0) {
		if ((y + x) % 2 > 0) black++;
		else white++;
	}
	else {
		if ((y + x) % 2 > 0) {
			if(black) map[y][x] = '^';
		}
		else if(white) map[y][x] = '^';
	}

	for (int i = 0; i < 4; i++)
		DFS(y + dy[i], x + dx[i], mode, visited, map);
}

int SetTrap(vector<string>& map)
{
	vector<vector<int>> visited(H, vector<int>(W, 0));

	// blackÀº È¦¼ö, white´Â Â¦¼ö
	int ret = 0;
	black = white = 0;
	for(int y=0;y<H;y++)
		for (int x = 0; x < W; x++) {
			DFS(y, x, 0, visited, map);
			if (visited[y][x] == 1) {
				ret += max(black, white);
				if (black > white) white = 0, black = 1;
				else white = 1, black = 0;

				DFS(y, x, 1, visited, map);
				black = white = 0;
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
		cin >> H >> W;
		vector<string> map(H);
		for (int i = 0; i < H; i++) cin >> map[i];

		cout << SetTrap(map) << '\n';
		for (int i = 0; i < H; i++)
			cout << map[i] << '\n';
	}
	return 0;
}