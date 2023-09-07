#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ull = unsigned long long;

const int MAXN = 300'000, MOD = 1'000'000'007;
ull arr[MAXN + 1];
ull epsum[MAXN];

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n; cin >> n;
	for (int i = 0; i < n; i++) cin >> arr[i];
	sort(arr, arr + n);

	epsum[0] = 1;
	int e = 1;
	arr[0] %= MOD;
	for (int i = 1; i < n; i++) {
		arr[i] %= MOD;
		e = (e << 1) % MOD;
		epsum[i] = (e + epsum[i - 1]) % MOD;
	}

	ull ans = 0;
	for (int i = 1; i < n; i++)
		ans = (ans + arr[i] * epsum[i-1]) % MOD;

	for (int i = 0; i < n - 1; i++)
		ans = (ans + MOD - (arr[i] * epsum[n-i-2]) % MOD) % MOD;

	cout << ans;
	
	return 0;
}