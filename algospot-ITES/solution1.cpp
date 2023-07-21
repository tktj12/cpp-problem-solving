#include <iostream>
#include <queue>
using namespace std;

inline long long next(long long n) {
	return (n * 214013 + 2531011) & 0xFFFFFFFF;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int k, n;
		cin >> k >> n;
		queue<int> sub;
		long long A_i = 1983;

		int sum = 0, ans = 0;
		for (int i = 0; i < n; i++) {
			int now = A_i % 10000 + 1;
			sub.push(now);
			sum += now;
			int last=0;
			while (sum >= k) {
				last = sub.front();
				sum -= last;
				sub.pop();
			}
			if (last > 0 && sum + last == k)
				ans++;

			A_i = next(A_i);
		}

		cout << ans << '\n';
	}
	return 0;
}