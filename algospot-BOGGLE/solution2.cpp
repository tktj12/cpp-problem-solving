#include <iostream>
#include <cstring>

using namespace std;

bool Find(string& str, int, int, int);

char board[7][7] = { 0, };
bool cache[6][6][9];

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		for (int i = 1; i <= 5; ++i)
			cin >> board[i] + 1;

		int n;
		cin >> n;
		while (n--) {
			string str;
			cin >> str;
			cout << str << ' ';

			memset(cache, 0, sizeof(cache));
			bool is_found = false;
			for (int i = 1; i <= 5; ++i) {
				for (int j = 1; j <= 5; ++j)
					if (Find(str, i, j, 0)) {
						is_found = true;
						break;
					}
				if (is_found) break;
			}
			if (is_found) cout << "YES\n";
			else cout << "NO\n";
		}
	}
	return 0;
}

int dx[8] = { 0, 1, 1, 1, 0,-1, -1, -1 };
int dy[8] = { -1,-1, 0, 1, 1, 1,  0, -1 };
bool Find(string& str, int y, int x, int idx)
{
	if (board[y][x] < 'A') return false;
	
	if (str[idx] != board[y][x]) return false;
	else if (idx+1 == str.size()) return true;

	if (cache[y][x][idx]) return false;
	else cache[y][x][idx] = true;

	for (int i = 0; i < 8; ++i)
		if (Find(str, y + dy[i], x + dx[i], idx + 1))
			return true;

	return false;
}