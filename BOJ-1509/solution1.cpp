#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int N, palin[5001];
char s[5001];

void Manacher()
{
	int r=0, p;
	for (int i = 0; i < N; i++) {
		if (i >= r) {
			p = i;
			while (r < N && r <= 2 * p && s[r] == s[2 * p - r]) r++;
			palin[i] = r - p-1;
		}
		else {
			int j = 2 * p - i;
			if (palin[j] < r - i - 1)
				palin[i] = palin[j];
			else if (palin[j] > r - i - 1)
				palin[i] = r - i - 1;
			else {
				p = i;
				while (r < N && r <= 2 * p && s[r] == s[2 * p - r]) r++;
				palin[i] = r - p - 1;
			}
		}
	}
}

const int INF = 987654321;
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	char str[2501];
	cin >> str;
	
	int i = 0;
	while (str[i] > 0)
		s[2 * i + 1] = str[i], i++;

	N = 2 * strlen(str) + 1;
	Manacher();
	
	N = (N - 1)/2;
	vector<int> dp(N, INF);
	dp[0] = 1;
	for (int i = 1; i < N; i++) {
		dp[i] = min(dp[i], dp[i - 1]+1);

		int p = palin[2 * i];
		int l = i - 1;
		int r = i;
		for (; r < i + p / 2;) {
			if (l - 1 < 0) dp[r] = 1;
			else dp[r] = min(dp[r], dp[l - 1] + 1);

			l--; r++;
		}

		p = palin[2 * i+1];
		l = i - 1;
		r = i + 1;

		for (; r <= i + p / 2;) {
			if (l - 1 < 0) dp[r] = 1;
			else dp[r] = min(dp[r], dp[l - 1] + 1);

			l--; r++;
		}
	}

	cout << dp[N - 1];

	return 0;
}