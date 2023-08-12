#include <iostream>
#include <algorithm>
using namespace std;

string a, b, ans;
int dp[1001][1001];

void LcsDp()
{
	for (int i = 1; i <= a.size(); i++) {
		char a_now = a[i-1];
		for (int j = 1; j <= b.size(); j++) {
			char b_now = b[j - 1];
			if (a_now == b_now)
				dp[i][j] = dp[i-1][j - 1] + 1;
			else
				dp[i][j] = max(dp[i-1][j], dp[i][j - 1]);
		}
	}

	if (dp[a.size()][b.size()] == 0) return;

	int j = b.size();
	for (int i = a.size(); i > 0; i--) {
		int len = dp[i][j];
		if (len == 0) break;
		while (dp[i][j - 1] == len)
			j--;
		while (dp[i - 1][j] == len)
			i--;
		ans += a[i - 1];
	}
	reverse(ans.begin(), ans.end());
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> a >> b;
	LcsDp();
	cout << ans.size() << '\n';
	if(ans.size() > 0)
		cout << ans;

	return 0;
}