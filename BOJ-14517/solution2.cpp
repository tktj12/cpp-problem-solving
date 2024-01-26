#include <iostream>
#include <cstring>
using namespace std;

string S;
int cache[1000][1000];
const int MOD = 10007;

int DP(int begin, int end)
{
	int& ret = cache[begin][end];
	if (ret != -1) return ret;

	if (begin > end)
		ret = 0;
	else if (begin == end)
		ret = 1;
	else {
		ret = DP(begin, end - 1) + DP(begin + 1, end) - DP(begin + 1, end - 1);
		if (S[begin] == S[end])
			ret += DP(begin + 1, end - 1) + 1;
	}

	return ret = (MOD + ret) % MOD;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	memset(cache, -1, sizeof(cache));
	cin >> S;
	cout << DP(0, S.size() - 1);

	return 0;
}