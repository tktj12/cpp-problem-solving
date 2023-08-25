#include <iostream>
#include <vector>
using namespace std;

const int UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3;
int N, ans;
inline void Init(int& y, int& x, const int mode)
{
	switch (mode) {
	case UP:
		y = x = 0;
		break;
	case DOWN:
		y = x = N - 1;
		break;
	case LEFT:
		y = N - 1, x = 0;
		break;
	case RIGHT:
		y = 0, x = N - 1;
		break;
	}
}

inline void NextStack(int& y, int& x, const int mode)
{
	switch (mode) {
	case UP:
		x++;
		y = 0;
		break;
	case DOWN:
		x--;
		y = N - 1;
		break;
	case LEFT:
		x = 0;
		y--;
		break;
	case RIGHT:
		x = N - 1;
		y++;
		break;
	}
}

inline void NextPointer(int& y, int& x, const int mode)
{
	switch (mode) {
	case UP:
		y++;
		break;
	case DOWN:
		y--;
		break;
	case LEFT:
		x++;
		break;
	case RIGHT:
		x--;
		break;
	}
}

int Slide(const vector<vector<int>>& now, vector<vector<int>>& next, const int mode)
{
	int ret = 0;
	int stack_y, stack_x;
	int pointer_y, pointer_x;
	Init(stack_y, stack_x, mode);
	Init(pointer_y, pointer_x, mode);

	bool changed = false;
	for (int i = 0; i < N; i++) {
		int last_y = stack_y;
		int last_x = stack_x;
		for (int j = 0; j < N; j++) {
			int& next_pos = next[stack_y][stack_x];
			const int& now_pos = now[pointer_y][pointer_x];

			if (now_pos > 0) {
				if (next_pos == 0) {
					next_pos = now_pos;
					ret = max(ret, now_pos);
				}
				else {
					if (next_pos == now_pos) {
						next_pos <<= 1;
						ret = max(ret, next_pos);
						NextPointer(stack_y, stack_x, mode);
						changed = true;
					}
					else {
						NextPointer(stack_y, stack_x, mode);
						next[stack_y][stack_x] = now_pos;
						ret = max(ret, now_pos);
					}
				}
				last_y = pointer_y;
				last_x = pointer_x;
			}
			NextPointer(pointer_y, pointer_x, mode);
		}
		if (stack_y != last_y || stack_x != last_x)
			changed = true;

		NextStack(stack_y, stack_x, mode);
		NextStack(pointer_y, pointer_x, mode);
	}

	if (changed) return ret;
	else return -1;
}

void DFS(const vector<vector<int>>& now, int depth)
{
	if (depth == 10)return;
	for (int i = 0; i < 4; i++) {
		vector<vector<int>> next(N, vector<int>(N));
		int top = Slide(now, next, i);
		if (top > 0) {
			ans = max(ans, top);
			for (int i = depth; i < 9; i++)
				top <<= 1;
			if (top > ans)
				DFS(next, depth + 1);
		}
	}
}

int main()
{
	cin >> N;

	vector<vector<int>> map(N, vector<int>(N));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
			ans = max(ans, map[i][j]);
		}

	DFS(map, 0);
	cout << ans;

	return 0;
}