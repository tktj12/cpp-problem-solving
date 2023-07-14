#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

struct Data {
	int y;
	int x;
	int dir;
	int sum;
	int cnt;

	Data(int _y, int _x, int _dir, int _sum) {
		y = _y;
		x = _x;
		dir = _dir;
		sum = _sum;
		cnt = 0;
	}
};

bool compare(const Data& a, const Data& b) {
	return a.cnt < b.cnt;
}
void Fill(int, int, int, int, int, vector<bool>&);
void solve(int idx);

int board[21][21];
int answer[21][21];
//int hint[20][20][2];
vector<Data> hint;
int board_size;
bool complete;
vector<pair<int, int>> d = { {0,1},{1,0} };
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		cin >> board_size;
		memset(answer, 0, sizeof(answer));
		for (int i = 0; i < board_size; ++i) {
			board[board_size][i] = board[i][board_size] = 0;
			for (int j = 0; j < board_size; ++j)
				cin >> board[i][j];
		}

		int hint_size;
		cin >> hint_size;
		hint.clear();
		for (int i = 0; i < hint_size; ++i) {
			int y, x, dir, sum;
			cin >> y >> x >> dir >> sum;
			hint.push_back({ y-1,x-1,dir,sum });

			y += d[dir].first-1, x += d[dir].second-1;
			while (board[y][x]) {
				hint.back().cnt++;
				y += d[dir].first, x += d[dir].second;
			}
		}
		sort(hint.begin(), hint.end(), compare);

		complete = false;
		solve(0);
		for (int i = 0; i < board_size; ++i) {
			for (int j = 0; j < board_size; ++j)
				cout << answer[i][j] << ' ';
			cout << '\n';
		}
	}
	return 0;
}

void solve(int idx)
{
	if (idx == hint.size()) {
		complete = true;
		return;
	}

	if (idx == 16) {
		int a = 1;
	}

	Data& h = hint[idx];
	// 해당되는 줄의 숫자들의 합이 힌트의 sum보다 작은지 확인
	int y = h.y + d[h.dir].first;
	int x = h.x + d[h.dir].second;
	int sum = 0;
	vector<bool> used(10, 0);
	while (board[y][x]) {
		sum += answer[y][x];
		if (answer[y][x] > 0) {
			if (used[answer[y][x]]) return;
			else used[answer[y][x]] = true;
		}
		y += d[h.dir].first;
		x += d[h.dir].second;
	}
	if (sum > h.sum) return;
	
	// 가능한 숫자들 전부 채워봄
	Fill(h.y + d[h.dir].first, h.x + d[h.dir].second, h.sum - sum, 0, idx, used);
}

vector<pair<int, int>> off = { {1,0},{0,1},{-1,0},{0,-1} };
void Fill(int y, int x, int remain, int depth, int idx, vector<bool>& used)
{
	Data& h = hint[idx];

	if (depth == h.cnt) {
		if(remain == 0)
			solve(idx + 1);
		return;
	}

	if (answer[y][x] > 0) {
		Fill(y + d[h.dir].first, x + d[h.dir].second, remain, depth + 1, idx, used);
		return;
	}

	for (int i = 9; i >= 1; --i) {
		if (used[i]) continue;

		if (i <= remain) {
			answer[y][x] = i;
			used[i] = true;
			Fill(y + d[h.dir].first, x + d[h.dir].second, remain - i, depth + 1, idx, used);
			if (complete) return;
			answer[y][x] = 0;
			used[i] = false;

		}
	}
}