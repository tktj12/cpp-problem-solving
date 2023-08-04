#include <iostream>
#include <cstring>
using namespace std;

int N;
int cache[100001][3];
int score[100001][2];

// idx�� ĭ�� action �ൿ�� ���� ���
// idx�� ĭ���� N�� ĭ���� ���� �� �ִ� ������ �ִ�
// 0 : ��ĭ ����, 1 : �Ʒ�ĭ ����, 2 : �� ����
// �̹� ĭ�� �� ���µ�  ���� ĭ�� �� ���� �� ���ش�.
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