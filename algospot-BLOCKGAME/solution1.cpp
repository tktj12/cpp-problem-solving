#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int solve(int);
void RotateMark(int);
bool IsPossible(int, int, vector<vector<int>>&);

char cache[1 << 25];
char map[5][5];
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);
	memset(cache, -1, sizeof(cache));

	int tc;
	cin >> tc;
	while (tc--) {

		int state = 0;
		for (int i = 0; i < 5; ++i)
			for (int j = 0; j < 5; ++j) {
				cin >> map[i][j];
				state <<= 1;
				if (map[i][j] == '#')
					++state;
			}
		cout << (solve(state) ? "WINNING" : "LOSING") << '\n';
	}
	return 0;
}

vector<vector<vector<int>>> block = {
	{{0, 1}},
	{{1, 0}},
	{{0, 1},{1, 0}},
	{{0, 1},{1, 1}},
	{{1, 0},{1, 1}},
	{{1, 0},{1,-1}}
};
int solve(int state)
{
	char& ret = cache[state];
	if (ret != -1) return ret;

	// 가능한 경우 탐색
	ret = 0;
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j) {
			if (map[i][j] == '#') continue;

			map[i][j] = '#';
			for (auto e : block) {
				if (IsPossible(i, j, e) == false) continue;

				int next_state = state | 1 << (5 * (4 - i) + 4 - j);
				for (auto pos : e) {
					map[i + pos[0]][j + pos[1]] = '#';
					next_state |= 1 << (5 * (4 - i - pos[0]) + 4 - j - pos[1]);
				}

				if (solve(next_state) == 0)
					ret = 1;

				for (auto pos : e)
					map[i + pos[0]][j + pos[1]] = '.';

				if (ret) break;
			}
			map[i][j] = '.';
			if (ret) break;
		}
		if (ret) break;
	}
	
	//RotateMark(ret);
	return ret;
}

void RotateMark(int val)
{
	// 90도 돌렸을 때
	int rotate_state = 0;
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j) {
			rotate_state <<= 1;
			if (map[4 - j][i] == '#')
				++rotate_state;
		}
	cache[rotate_state] = val;

	// 180도
	rotate_state = 0;
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j) {
			rotate_state <<= 1;
			if (map[4 - i][4 - j] == '#')
				++rotate_state;
		}
	cache[rotate_state] = val;

	// 270도
	rotate_state = 0;
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j) {
			rotate_state <<= 1;
			if (map[j][4 - i] == '#')
				++rotate_state;
		}
	cache[rotate_state] = val;

	//상하 반전
	char flip_map[5][5];
	rotate_state = 0;
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j) {
			rotate_state <<= 1;
			if (map[4 - i][j] == '#') {
				flip_map[i][j] = '#';
				++rotate_state;
			}
			else flip_map[i][j] = '.';
		}
	cache[rotate_state] = val;

	// 상하 반전, 90도 돌렸을 때
	rotate_state = 0;
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j) {
			rotate_state <<= 1;
			if (flip_map[4 - j][i] == '#')
				++rotate_state;
		}
	cache[rotate_state] = val;

	// 상하 반전, 180도
	rotate_state = 0;
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j) {
			rotate_state <<= 1;
			if (flip_map[4 - i][4 - j] == '#')
				++rotate_state;
		}
	cache[rotate_state] = val;

	// 상하 반전, 270도
	rotate_state = 0;
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j) {
			rotate_state <<= 1;
			if (flip_map[j][4 - i] == '#')
				++rotate_state;
		}
	cache[rotate_state] = val;
}

bool IsPossible(int y, int x, vector<vector<int>>& e)
{
	bool ret = true;
	for (auto pos : e) {
		if (y + pos[0] < 0 || 4 < y + pos[0] || x + pos[1] < 0 || 4 < x + pos[1]) {
			ret = false;
			break;
		}
		else if (map[y + pos[0]][x + pos[1]] == '#') {
			ret = false;
			break;
		}
	}
	return ret;
}