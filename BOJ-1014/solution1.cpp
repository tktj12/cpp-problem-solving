#include <iostream>
#include <cstring>
using namespace std;

int N, M;
char map[11][10];
int cache[11][10][2048];
int dx[6] = { -1,-1,-1,1,1,1 };
int dy[6] = { -1,0,1,-1,0,1 };
bool Valid(int y,int x)
{
	if (map[y][x] != '.') return false;
	for (int i = 0; i < 6; i++) {
		int r = y + dy[i];
		int c = x + dx[i];
		if (r < 0 || N<r || c < 0 || M <= c)
			continue;

		if (map[r][c] == 'm')
			return false;
	}
	return true;
}

int DP(int y,int x,int bitmask)
{
	if (y > N) return 0;

	int& ret = cache[y][x][bitmask];
	if (ret != -1) return ret;

	int ny = y;
	int nx = x + 1;
	if (nx == M) {
		ny = y + 1;
		nx = 0;
	}

	bitmask = 0;
	for (int i = max(0,nx-1); i < M; i++) {
		bitmask <<= 1;
		if (map[ny - 1][i] == 'm')
			bitmask++;
	}
	for (int i = 0; i < nx; i++) {
		bitmask <<= 1;
		if (map[ny][i] == 'm')
			bitmask++;
	}

	ret = DP(ny,nx,bitmask);
	if (Valid(y,x)) {
		map[y][x] = 'm';
		ret = max(ret,1 + DP(ny,nx,bitmask+1));
		map[y][x] = '.';
	}

	return ret;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	memset(map,'x',sizeof(map));
	int tc;
	cin >> tc;
	while (tc--) {
		memset(cache,-1,sizeof(cache));
		cin >> N >> M;
		for (int i = 1; i <= N; i++)
			for (int j = 0; j < M; j++)
				cin >> map[i][j];

		cout << DP(1,0,0) << '\n';
	}
	return 0;
}