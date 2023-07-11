#include <iostream>
#include <vector>
#include <cstring>
using namespace std;


int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int n, cnt[100001] = { 0, }, sum(0);
		cin >> n;
		for (int i = 0; i < n; ++i) {
			int len;
			cin >> len;
			sum += len;
			++cnt[len];
		}

		int ans = 0;
		for (int i = 1; i < sum; ++i) {
			if (cnt[i] > 0) {
				--cnt[i];
				ans += i;
				for (int j = i; j < sum; ++j) {
					if (cnt[j] > 0) {
						--cnt[j];
						ans += j;
						++cnt[i + j];
						break;
					}
				}
				--i;
			}
		}

		cout << ans << '\n';
	}
	return 0;
}