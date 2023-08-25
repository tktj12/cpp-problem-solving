#include <iostream>
#include <vector>
using namespace std;

const int UP=0, DOWN=1, LEFT=2, RIGHT=3;
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

void Slide(const vector<vector<int>>& now, vector<vector<int>>& next, const int mode)
{
	int stack_y, stack_x;
	int pointer_y, pointer_x;
	Init(stack_y, stack_x, mode);
	Init(pointer_y, pointer_x, mode);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int& next_pos = next[stack_y][stack_x];
			const int& now_pos = now[pointer_y][pointer_x];
			if (next_pos == 0)
				next_pos = now_pos;
			else if (now_pos > 0){
				if (next_pos == now_pos) {
					next_pos<<=1;
					ans = max(ans, next_pos);
					NextPointer(stack_y, stack_x, mode);
				}
				else {
					NextPointer(stack_y, stack_x, mode);
					next[stack_y][stack_x] = now_pos;
				}
			}
			NextPointer(pointer_y, pointer_x, mode);
		}
		NextStack(stack_y, stack_x, mode);
		NextStack(pointer_y, pointer_x, mode);
	}
}

void DFS(const vector<vector<int>>& now, int depth)
{
	if (depth == 5)return;
	for (int i = 0; i < 4; i++) {
		vector<vector<int>> next(N, vector<int>(N));
		Slide(now, next, i);
		DFS(next, depth + 1);
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