#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int LYING = 0, DIAGONAL = 1, STAND = 2;
int map[16][16];
int N;
int cache[3][16][16];

pair<int,int> CanGo(int state, int y, int x)
{
	if (state == LYING) {
		if (x + 1 < N && map[y][x + 1] == 0) return {y,x+1};
		else return {-1,-1};
	}
	else if (state == DIAGONAL) {
		if (x + 1 < N && y + 1 < N && 
			map[y][x + 1] == 0 &&
			map[y + 1][x] == 0 &&
			map[y + 1][x + 1] == 0)
			return { y+1,x + 1 };
		else return { -1,-1 };
	}
	else {
		if (y + 1 < N && map[y+1][x] == 0) return { y+1,x };
		else return { -1,-1 };
	}
}

vector<vector<int>> trans = { {LYING,DIAGONAL},{LYING,DIAGONAL,STAND},{DIAGONAL,STAND} };
int DP(int state, int y, int x)
{
	if (y == N - 1 && x == N - 1) return 1;

	int& ret = cache[state][y][x];
	if (ret != -1) return ret;
	ret = 0;
	for (int next_state : trans[state]) {
		pair<int, int> next_coord = CanGo(next_state, y, x);
		if (next_coord.first != -1)
			ret += DP(next_state, next_coord.first, next_coord.second);
	}
	return ret;
}

int main()
{
	memset(cache, -1, sizeof(cache));

	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> map[i][j];

	cout << DP(LYING, 0, 1);

	return 0;
}