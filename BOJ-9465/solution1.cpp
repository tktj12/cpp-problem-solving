#include <iostream>
#include <cstring>
using namespace std;

int N;
int cache[100001][3];
int score[100001][2];

// idx번 칸에 action 행동을 취할 경우
// idx번 칸부터 N번 칸까지 얻을 수 있는 점수의 최댓값
// 0 : 윗칸 떼기, 1 : 아랫칸 떼기, 2 : 안 떼기
// 이번 칸을 안 떼는데  다음 칸도 안 떼는 건 손해다.
int DP(int idx, int action)
{
	if (idx == N) return 0;
	int& ret = cache[idx][action];
	if (ret != -1) return ret;
	ret = 0;

	for (int i = 0; i < 3; i++)
		if (i != action)
			ret = max(ret, DP(idx + 1, i));

	if (action != 2)
		ret += score[idx][action];
	return ret;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		memset(cache, -1, sizeof(cache));
		memset(score, 0, sizeof(score));

		cin >> N;
		for (int j = 0; j < 2; j++)
			for (int i = 0; i < N; i++)
				cin >> score[i][j];

		int ans = 0;
		for (int i = 0; i < 3; i++)
			ans = max(ans, DP(0, i));
		cout << ans << '\n';
	}
}