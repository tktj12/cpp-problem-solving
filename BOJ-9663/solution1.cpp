#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

// 퀸을 놓을 수 있으면 0
int map[15][15];
int N;

bool InRange(int y, int x) {
	return 0 <= x && x < N && 0 <= y && y < N;
}

void PutQueen(int y, int x) {
	for (int i = 0; i < N; i++) {
		map[y][i]++;
		map[i][x]++;
	}

	int i = 1;
	while (true) {
		if (!InRange(y - i, x+i)) break;

		map[y - i][x + i]++;
		i++;
	}

	i = 1;
	while (true) {
		if (!InRange(y - i, x - i)) break;

		map[y - i][x - i]++;
		i++;
	}

	i = 1;
	while (true) {
		if (!InRange(y + i, x + i)) break;

		map[y + i][x + i]++;
		i++;
	}

	i = 1;
	while (true) {
		if (!InRange(y + i, x - i)) break;

		map[y + i][x - i]++;
		i++;
	}
}

void RemoveQueen(int y, int x)
{
	for (int i = 0; i < N; i++) {
		map[y][i]--;
		map[i][x]--;
	}

	int i = 1;
	while (true) {
		if (!InRange(y - i, x + i)) break;

		map[y - i][x + i]--;
		i++;
	}

	i = 1;
	while (true) {
		if (!InRange(y - i, x - i)) break;

		map[y - i][x - i]--;
		i++;
	}

	i = 1;
	while (true) {
		if (!InRange(y + i, x + i)) break;

		map[y + i][x + i]--;
		i++;
	}

	i = 1;
	while (true) {
		if (!InRange(y + i, x - i)) break;

		map[y + i][x - i]--;
		i++;
	}
}

int DFS(int row) {
	if (row == N) return 1;
	int ret = 0;
	for (int i = 0; i < N; i++) {
		if (map[row][i] == 0) {
			PutQueen(row, i);
			ret += DFS(row + 1);
			RemoveQueen(row, i);
		}
	}
	return ret;
}

int main()
{
	cin >> N;
	cout << DFS(0);

	return 0;
}