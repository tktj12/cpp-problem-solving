#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int H, W, T;
int map[2][50][50];
int dy[4] = { 1,-1,0,0 }, dx[4] = { 0,0,1,-1 };
void Spread(bool now, bool next)
{
	for(int i=0;i<H;i++)
		for (int j = 0; j < W; j++) {
			if (map[now][i][j] == -1) {
				map[next][i][j] = -1;
				continue;
			}

			int spread = map[now][i][j] / 5;
			for (int k = 0; k < 4; k++) {
				int y = i + dy[k];
				int x = j + dx[k];
				if (y < 0 || H <= y || x < 0 || W <= x || map[now][y][x] == -1) continue;

				map[next][y][x] += spread;
				map[now][i][j] -= spread;
			}
			map[next][i][j] += map[now][i][j];
		}
}

void Purify(bool now, int pos, bool ccw)
{
	int y = pos;
	if (ccw) {
		--y;
		for (; y > 0; y--)
			map[now][y][0] = map[now][y - 1][0];
		int x = 0;
		for (; x < W - 1; x++)
			map[now][0][x] = map[now][0][x+1];
		for(y=0;y<pos;y++)
			map[now][y][x] = map[now][y + 1][x];
		for (x = W-1; x > 1; x--)
			map[now][pos][x] = map[now][pos][x - 1];
		map[now][pos][1] = 0;
	}
	else {
		++y;
		for (; y < H-1; y++)
			map[now][y][0] = map[now][y + 1][0];
		int x = 0;
		for (; x < W - 1; x++)
			map[now][y][x] = map[now][y][x + 1];
		for (; y > pos; y--)
			map[now][y][x] = map[now][y - 1][x];
		for (; x > 1; x--)
			map[now][pos][x] = map[now][pos][x - 1];
		map[now][pos][1] = 0;
	}
}

int Solve()
{
	int top, bottom;

	for (int i = 0; i < H; i++) {
		if (map[0][i][0] == -1) {
			top = i;
			bottom = i + 1;
			break;
		}
	}

	for (int i = 0; i < T; i++) {
		bool now = i % 2, next = !now;
		Spread(now, next);
		memset(map + now, 0, sizeof(map[0]));

		Purify(next, top, true);
		Purify(next, bottom, false);
	}

	bool now = T % 2;
	int ret = 0;
	for(int i=0;i<H;i++)
		for (int j = 0; j < W; j++)
			if (map[now][i][j] > 0)
				ret += map[now][i][j];
	
	return ret;
}

int main()
{
	cin >> H >> W >> T;
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			cin >> map[0][i][j];

	cout << Solve();

	return 0;
}