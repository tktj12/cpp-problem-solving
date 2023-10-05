#include <iostream>
#include <vector>
#include <stack>
using namespace std;


int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n; cin >> n;
	long long ans = 0;

	// height, count
	stack<pair<int,int>> st;
	for (int i = 0; i < n; i++) {
		int h; cin >> h;

		while (1) {
			if (st.empty()) {
				st.push({ h,1 });
				break;
			}
			else if (st.top().first < h) {
				pair<int, int> t = st.top(); st.pop();
				if (!st.empty())
					ans += t.second;
				ans += t.second;
				ans += (long long)t.second * (t.second - 1) / 2;
			}
			else if (st.top().first == h) {
				st.top().second++;
				break;
			}
			else {
				st.push({ h,1 });
				break;
			}
		}
	}

	while (1) {
		pair<int, int> t = st.top(); st.pop();
		ans += (long long)t.second * (t.second - 1) / 2;
		if (st.empty()) break;

		ans += t.second;
	}

	cout << ans;

	return 0;
}