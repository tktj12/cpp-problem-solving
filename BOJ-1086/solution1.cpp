#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
using ll = long long;

vector<string> S;
ll cache[1<<15][100], cache_str[15], cache_r[100][51];
int K;
ll DP(int used, int remainder)
{
	ll& ret = cache[used][remainder];
	if (ret != -1) return ret;

	ret = 0;
	if (used == (1 << S.size()) - 1) {
		if (remainder == 0)
			ret = 1;
	}
	else
		for (int i = 0; i < S.size(); i++)
			if (!(used & (1 << i)))
				ret += DP(used | (1 << i), (cache_r[remainder][S[i].size()] + cache_str[i]) % K);

	return ret;
}

ll GCD(ll p, ll q)
{
	if (q == 0) return p;
	return GCD(q, p%q);
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	memset(cache, -1, sizeof(cache));
	int n; cin >> n;
	S = vector<string>(n);
	for (int i = 0; i < n; i++) {
		cin >> S[i];
		for (int j = 0; j < S[i].size(); j++)
			S[i][j] -= '0';
	}
	cin >> K;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < S[i].size(); j++)
			cache_str[i] = (cache_str[i] * 10 + S[i][j]) % K;

	for (int i = 0; i < K; i++) {
		int nr = i;
		for (int j = 1; j <= 50; j++) {
			nr = (nr * 10) % K;
			cache_r[i][j] = nr;
		}
	}

	ll divisible = DP(0, 0);

	if (divisible == 0)
		cout << "0/1";
	else {
		ll all_case = 1;
		for (int i = 2; i <= n; i++)
			all_case *= i;

		ll gcd = GCD(divisible, all_case);
		cout << divisible/gcd << '/' << all_case/gcd;
	}

	return 0;
}