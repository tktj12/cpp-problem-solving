#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
int solve(int idx, int taken, bool less, int rest);

const int MOD = 1000000007;
string price;
int M;
vector<int> digits;
int cache[32768][2][20];
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		digits.clear();
		memset(cache, -1, sizeof(cache));

		cin >> price >> M;

		for (char e : price)
			digits.push_back(e);
		sort(digits.begin(), digits.end());

		cout << solve(0, 0, false, 0) << '\n';
	}
	return 0;
}

int solve(int idx, int taken, bool is_less, int rest)
{
	int& ret = cache[taken][is_less][rest];
	if (ret != -1) return ret;
	ret = 0;

	if (idx == price.size()) {
		if (rest == 0 && is_less)
			ret = 1;
		return ret;
	}

	for (int i = 0; i < digits.size(); i++) {
		if (!is_less && digits[i] > price[idx]) break;
		if (taken & (1 << i) ||
			i > 0 && !(taken & (1 << (i-1))) && digits[i - 1] == digits[i])
			continue;

		bool next_less = is_less || digits[i] < price[idx];
		int next_rest = (10*rest + digits[i]-'0') % M;
		ret += solve(idx + 1, taken | (1<<i), next_less, next_rest);
		ret %= MOD;
	}
	return ret;
}