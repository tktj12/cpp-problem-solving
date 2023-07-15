#include <iostream>
using namespace std;

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		long long play, win;
		cin >> play >> win;

		int origin = int(double(win*100) / play);
		long long lo = 0, hi = 0xFFFFFFFF;
		while (lo+1<hi) {
			long long mid = (lo+hi) / 2;
			int ratio = int(double(win + mid) * 100. / (play + mid));
			if (ratio > origin)
				hi = mid;
			else
				lo = mid;
		}
		
		int ratio = int(double(win + hi) * 100./ (play + hi));
		if (ratio == origin) cout << -1 << '\n';
		else cout << hi << '\n';
	}
	return 0;
}