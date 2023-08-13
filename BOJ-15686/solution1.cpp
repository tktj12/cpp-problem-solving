#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Coord {
	int y, x;
};

int PopCount(int bits)
{
	bits = ((bits >> 1) & 0x55555555) + (bits & 0x55555555);
	bits = ((bits >> 2) & 0x33333333) + (bits & 0x33333333);
	bits = ((bits >> 4) & 0x0F0F0F0F) + (bits & 0x0F0F0F0F);
	bits = ((bits >> 8) & 0x00FF00FF) + (bits & 0x00FF00FF);
	return ((bits >> 16) & 0x0000FFFF) + (bits & 0x0000FFFF);
}

int map[50][50];
vector<Coord> restaurant, house;
int N;
int BfsGetChickenDist(int choose)
{
	int dist[50][50];
	bool discovered[50][50] = { 0, };
	queue<pair<Coord, int> > q;

	for (int i = 0; i < restaurant.size(); i++)
		if (choose & (1 << i))
			q.push({ restaurant[i],0 });

	int dx[4] = { 1,-1,0,0 }, dy[4] = { 0, 0, 1, -1 };
	while (!q.empty()) {
		Coord here = q.front().first;
		int d = q.front().second + 1;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int y = here.y + dy[i];
			int x = here.x + dx[i];
			if (y < 0 || N <= y || x < 0 || N <= x || discovered[y][x]) continue;
			discovered[y][x] = true;
			dist[y][x] = d;
			q.push({ { y,x }, d });
		}
	}

	int ret = 0;
	for (int i = 0; i < house.size(); i++)
		ret += dist[house[i].y][house[i].x];
	return ret;
}

// n개 중 r개 고르는 경우에 대해 Bfs를 수행
int ChooseN(int N, int r)
{
	int ret = 987654321;
	for (int bit = (1 << N)-1; bit > 0; bit--)
		if (PopCount(bit) == r) 
			ret = min(ret, BfsGetChickenDist(bit));

	return ret;
}

int main()
{
	int m;
	cin >> N >> m;

	queue<pair<Coord, int>> q;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1)
				house.push_back({ i,j });
			else if (map[i][j] == 2)
				restaurant.push_back({ i,j });
		}

	cout << ChooseN(restaurant.size(), m);

	return 0;
}