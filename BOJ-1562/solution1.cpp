#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MOD = 1'000'000'000;
int N;
int cache[1 << 10][10][100];

int DP(int bm, int num, int cur)
{
	bm |= 1 << num;

	if (cur == N) {
		if (bm == (1 << 10) - 1) return 1;
		else return 0;
	}

	int& ret = cache[bm][num][cur];
	if (ret != -1) return ret;
	ret = 0;

	if(num < 9)
		ret += DP(bm, num + 1, cur + 1);
	
	if(num > 0)
		ret += DP(bm, num - 1, cur + 1);

	return ret %= MOD;
}

int main()
{
	cin >> N;
	memset(cache, -1, sizeof(cache));

	int ans = 0;
	for (int i = 1; i <= 9; i++)
		ans = (ans + DP(0, i, 1)) % MOD;

	cout << ans;

	return 0;
}