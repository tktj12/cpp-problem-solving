#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

int H, W;
int map[102][102];
int dy[4] = { 1,-1,0,0 }, dx[4] = { 0,0,1,-1 };
bool BfsSearchCheeze()
{
	bool discovered[102][102] = { 0, };
	discovered[1][1] = true;
	queue<pair<int, int> > q;
	q.push({ 1,1 });

	bool found_cheeze = false;
	while (!q.empty()) {
		pair<int, int> here = q.front(); q.pop();
		for (int i = 0; i < 4; i++) {
			int y = here.first + dy[i];
			int x = here.second + dx[i];
			if (map[y][x] == -1) continue;
			else if (map[y][x] == 1) {
				found_cheeze = true;
				if (discovered[y][x]) map[y][x] = 0;
				else discovered[y][x] = true;
			}
			else if (!discovered[y][x]) {
				discovered[y][x] = true;
				q.push({ y,x });
			}
		}
	}

	return found_cheeze;
}

int RemoveAllCheeze()
{
	int ret = 0;
	while (BfsSearchCheeze()) ret++;
	return ret;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	memset(map, -1, sizeof(map)); // 가장자리는 -1
	cin >> H >> W;
	for (int i = 1; i <= H; i++)
		for (int j = 1; j <= W; j++)
			cin >> map[i][j];

	cout << RemoveAllCheeze();
	
	return 0;
}