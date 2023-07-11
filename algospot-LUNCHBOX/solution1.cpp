#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;


int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int n;
		cin >> n;

		vector<pair<int, int>> lunch(n);
		for (int i = 0; i < n; ++i) cin >> lunch[i].second; // heating time
		for (int i = 0; i < n; ++i) cin >> lunch[i].first;  // eating time
		sort(lunch.rbegin(), lunch.rend());
		
		int ans = 0;
		int time = 0;
		for (int i = 0; i < n; ++i) {
			time += lunch[i].second;
			ans = max(ans, time + lunch[i].first);
		}
		cout << ans << '\n';
	}
	return 0;
}