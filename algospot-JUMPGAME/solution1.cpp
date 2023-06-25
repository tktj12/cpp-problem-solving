#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

bool IsEscapable(int, int, int);

int map[110][110];
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		memset(map, -1, 12100);
		int n;
		cin >> n;
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				cin >> map[i][j];
		if (IsEscapable(0, 0, n)) cout << "YES\n";
		else cout << "NO\n";
	}
	return 0;
}

bool IsEscapable(int y, int x, int n)
{
	if (map[y][x] < 0) return false;
	if (y == (n-1) && x == (n-1)) return true;

	int cur_num = map[y][x];
	map[y][x] = -1;

	return IsEscapable(y + cur_num, x, n) || IsEscapable(y, x + cur_num, n);
}