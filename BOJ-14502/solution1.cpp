#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

int map[10][10];
int dy[4] = { 1,-1,0,0 }, dx[4] = { 0,0,1,-1 };
int SpreadVirus(queue<pair<int, int> > virus)
{
	int ret = 0;
	int replica[10][10];
	memcpy(replica, map, sizeof(map));

	while (!virus.empty()) {
		pair<int, int> here = virus.front(); virus.pop();

		for (int i = 0; i < 4; i++) {
			int y = here.first + dy[i];
			int x = here.second + dx[i];

			if (replica[y][x] == 0) {
				ret++;
				replica[y][x] = 2;
				virus.push({ y,x });
			}
		}
	}

	return ret;
}

inline pair<int,int> Coord(int i) {
	pair<int, int> ret;
	ret.first = i / 8 + 1;
	ret.second = i % 8 + 1;
	return ret;
}

int ErectWall(queue<pair<int, int> > virus, int map_size)
{
	int ret = 0;
	for (int i = 0; i < 64; i++) {
		pair<int, int> w1 = Coord(i);
		if (map[w1.first][w1.second] != 0) continue;

		map[w1.first][w1.second] = 1;
		for (int j = i + 1; j < 64; j++) {
			pair<int, int> w2 = Coord(j);
			if (map[w2.first][w2.second] != 0) continue;

			map[w2.first][w2.second] = 1;
			for (int k = j + 1; k < 64; k++) {
				pair<int, int> w3 = Coord(k);
				if (map[w3.first][w3.second] != 0) continue;

				map[w3.first][w3.second] = 1;
				ret = max(ret, map_size - SpreadVirus(virus));
				map[w3.first][w3.second] = 0;
			}
			map[w2.first][w2.second] = 0;
		}
		map[w1.first][w1.second] = 0;
	}

	return ret;
}

int main()
{
	memset(map, -1, sizeof(map));
	int h, w;
	cin >> h >> w;
	int map_size=0;
	queue<pair<int, int>> virus;
	for (int i = 1; i <= h; i++)
		for (int j = 1; j <= w; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2)
				virus.push({ i,j });
			else if (map[i][j] == 0)
				map_size++;
		}

	cout << ErectWall(virus, map_size-3);

	return 0;
}