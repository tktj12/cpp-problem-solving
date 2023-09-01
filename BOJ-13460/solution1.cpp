#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int ans = 20, H, W;
int dy[4] = { -1,1,0,0 }, dx[4] = { 0,0,-1,1 };

int Incline(vector<string>& now, vector<string>& next, const int mode)
{
	bool changed = false;
	pair<int, int> B, R;
	for (int i = 1; i < H - 1; i++)
		for (int j = 1; j < W - 1; j++)
			if (now[i][j] == 'B')
				B.first = i, B.second = j;
			else if(now[i][j] == 'R')
				R.first = i, R.second = j;

	while (next[B.first + dy[mode]][B.second + dx[mode]] == '.') {
		next[B.first][B.second] = '.';
		B.first += dy[mode], B.second += dx[mode];
		next[B.first][B.second] = 'B';
		changed = true;
	}
	while (next[R.first + dy[mode]][R.second + dx[mode]] == '.') {
		next[R.first][R.second] = '.';
		R.first += dy[mode], R.second += dx[mode];
		next[R.first][R.second] = 'R';
		changed = true;
	}
	while (next[B.first + dy[mode]][B.second + dx[mode]] == '.') {
		next[B.first][B.second] = '.';
		B.first += dy[mode], B.second += dx[mode];
		next[B.first][B.second] = 'B';
		changed = true;
	}

	if (next[B.first + dy[mode]][B.second + dx[mode]] == 'O') return false;
	if (next[R.first + dy[mode]][R.second + dx[mode]] == 'O') {
		if (next[B.first + dy[mode]][B.second + dx[mode]] == 'R') return false;
		else return 2;
	}
	if (!changed) return false;

	next[B.first][B.second] = 'B';
	next[R.first][R.second] = 'R';
	return 1;
}

void DFS(vector<string>& now, int depth)
{
	if (ans <= depth || depth == 10) return;

	for (int i = 0; i < 4; i++) {
		vector<string> next = now;
		int det = Incline(now, next, i);
		if (det == 2) {
			ans = min(ans, depth + 1);
			return;
		}
		else if (det == 1)
			DFS(next, depth + 1);
	}
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> H >> W;
	vector<string> map(H);
	for (int i = 0; i < H; i++)
		cin >> map[i];

	DFS(map, 0);

	if (ans == 20) cout << -1;
	else cout << ans;
	
	return 0;
}