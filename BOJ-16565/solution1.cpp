#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int M = 10'007;
int cache[53][53];
int C(int n, int r)
{
	int& ret = cache[n][r];
	if (ret != -1) return ret;
	
	if (r > n / 2) r = n - r;
	if (r == 0) return ret = 1;
	if (r == 1) return ret = n;

	return ret = (C(n - 1, r) + C(n - 1, r - 1)) % M;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);
	memset(cache, -1, sizeof(cache));

	int N; cin >> N;
	int ans = 0;
	for (int i = 1; i <= N / 4; i += 2)
		ans = (ans + (C(13, i) * C(52 - 4 * i, N - 4 * i))) % M;

	for (int i = 2; i <= N / 4; i += 2)
		ans = (ans + M - (C(13, i) * C(52 - 4 * i, N - 4 * i)) % M) % M;

	cout << ans;
	
	return 0;
}