#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int DP(int upside_blocks, int remainder);

#define MOD_NUM 10000000

int cache[101][101];
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int n;
		cin >> n;
		memset(cache, -1, sizeof(cache));
		int res(0);
		for (int i = 1; i <= n; ++i)
			res = (res + DP(i, n - i)) % MOD_NUM;
		cout << res << '\n';
	}
	return 0;
}

int DP(int upstair_blocks, int remainder)
{
	int& ret = cache[upstair_blocks][remainder];
	if (ret != -1) return ret;
	if (remainder == 0) return ret = 1;

	ret = 0;
	for (int use = 1; use <= remainder; ++use)
		ret = (ret + (upstair_blocks + use - 1) * DP(use, remainder - use)) % MOD_NUM;
	return ret;
}