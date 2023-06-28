#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>

using namespace std;
int LenOfJLIS(int, int);

int cache[101][101];
vector<long long> A, B;
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		memset(cache, 0, sizeof(cache));
		int n, m;
		cin >> n >> m;
		A = vector<long long>(n+1);
		B = vector<long long>(m+1);
		A[0] = B[0] = -0xFFFFFFFFLL;
		for (int i = 1; i <= n; ++i) cin >> A[i];
		for (int i = 1; i <= m; ++i) cin >> B[i];
		cout << LenOfJLIS(0, 0)-1 << '\n';
	}
	return 0;
}

int LenOfJLIS(int a, int b)
{
	int& ret = cache[a][b];
	if (ret) return ret;
	
	long long tail = max(A[a], B[b]);
	for (int i = a + 1; i < A.size(); ++i)
		if (A[i] > tail)
			ret = max(ret, LenOfJLIS(i, b));

	for (int i = b + 1; i < B.size(); ++i)
		if (B[i] > tail)
			ret = max(ret, LenOfJLIS(a, i));
	
	return ++ret;
}
