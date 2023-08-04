#include <iostream>
using namespace std;

int cache[1000][3], cost[1000][3];
int N;

// ���� ���� house�� ���̰� color���� ĥ���� ��
// house�� ���� ������ ���� ĥ�ϴ� ����� �ּڰ��� ��ȯ
int DP(int house, int color)
{
	if (house == N) return 0;
	int& ret = cache[house][color];
	if (ret > 0) return ret;
	ret = 987654321;

	for (int i = 0; i < 3; i++)
		if (i != color)
			ret = min(ret, DP(house + 1, i));

	return ret += cost[house][color];
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> cost[i][0] >> cost[i][1] >> cost[i][2];
	
	int ans = 987654321;
	for (int i = 0; i < 3; i++)
		ans = min(ans, DP(0, i));
	cout << ans;

	return 0;
}