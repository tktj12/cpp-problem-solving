#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;
int DP(int, int);
int square(int n) {
	return n * n;
}

vector<int> numbers;
int cache_variance[100][100];
int cache_result[10][100];
int N, S;
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		cin >> N >> S;
		numbers = vector<int>(N);
		for (int i = 0; i < N; ++i) cin >> numbers[i];
		if (S >= N) {
			cout << 0 << '\n';
			continue;
		}
		
		sort(numbers.begin(), numbers.end());
		for (int i = 0; i < N; ++i) {
			int sum(0);
			for (int j = i; j < N; ++j) {
				sum += numbers[j];
				int avr = int(0.5+(double)sum / (j - i + 1));
				int variance(0);
				for (int k = i; k <= j; ++k)
					variance += square(numbers[k] - avr);

				cache_variance[i][j] = variance;
			}
		}

		memset(cache_result, -1, sizeof(cache_result));
		cout << DP(0, 0) << '\n';
	}
	return 0;
}

const int INF = 987654321;
int DP(int s, int left)
{
	int& ret = cache_result[s][left];
	if (ret != -1) return ret;
	if (s == S - 1) return ret = cache_variance[left][N - 1];
	ret = INF;

	int until = N - S + s;
	for (int i = left; i <= until; ++i) {
		int variance = cache_variance[left][i];
		ret = min(ret, variance+DP(s + 1, i + 1));
	}
	return ret;
}