#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int INF = 987654321;
char map[100001][3];
int N;

int GetMaxScore()
{
	int floor = N-1;
	int score[2][3];

	for (int i = 0; i < 3; i++)
		score[floor % 2][i] = map[floor][i];
	while (--floor >= 0) {
		bool now = floor % 2, prev = !now;

		for (int i = 0; i < 3; i++) {
			int max_score = 0;
			for (int j = 0; j < 3; j++) {
				if (abs(i - j) > 1) continue;
				max_score = max(max_score, score[prev][j]);
			}
			score[now][i] = max_score + map[floor][i];
		}
	}

	int ret = 0;
	for (int i = 0; i < 3; i++)
		ret = max(ret, score[0][i]);
	return ret;
}

int GetMinScore()
{
	int floor = N - 1;
	int score[2][3];

	for (int i = 0; i < 3; i++)
		score[floor % 2][i] = map[floor][i];
	while (--floor >= 0) {
		bool now = floor % 2, prev = !now;

		for (int i = 0; i < 3; i++) {
			int min_score = INF;
			for (int j = 0; j < 3; j++) {
				if (abs(i - j) > 1) continue;
				min_score = min(min_score, score[prev][j]);
			}
			score[now][i] = min_score + map[floor][i];
		}
	}

	int ret = INF;
	for (int i = 0; i < 3; i++)
		ret = min(ret, score[0][i]);
	return ret;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> map[i][j];
			map[i][j] -= '0';
		}
	}
	cout << GetMaxScore() << ' ' << GetMinScore();

	return 0;
}