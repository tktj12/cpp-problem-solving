#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


double dp[500][3001];
int main()
{
	cout.precision(10);

	int n, k;
	cin >> n >> k;

	dp[1+1][0] = 1.;

	dp[1+1][1] = 1. / 3.;
	dp[2+1][1] = 1. / 3.;
	dp[3+1][1] = 1. / 3.;

	for (int j = 1; j <= n; j++) {
		for (int i = 1; i <= k; i++) {
			int idx = i + 1;
			dp[idx][j] = (dp[idx][j-1] + dp[idx - 1][j-1] + dp[idx - 2][j-1]) / 3;
		}
	}

	double ans = 0;
	for (int i = 1; i <= k; i++) {
		int idx = i + 1;
		ans += dp[idx][n];
	}

	cout << ans;

	return 0;
}