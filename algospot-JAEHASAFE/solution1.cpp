#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

vector<int> getPartialMatch(const string& str)
{
	vector<int> ret(str.size(), 0);
	int begin(1), matched(0);
	while (begin + matched < str.size()) {
		if (str[begin + matched] == str[matched]) {
			matched++;
			ret[begin + matched - 1] = matched;
		}
		else {
			if (matched == 0) {
				begin++;
			}
			else {
				begin += matched - ret[matched - 1];
				matched = ret[matched - 1];
			}
		}
	}
	return ret;
}

int rotate(const string& head, const string& tail)
{
	vector<int> p = getPartialMatch(tail);
	int begin(1), matched(0);
	while (matched < tail.size()) {
		if (head[(begin + matched)%head.size()] == tail[matched]) {
			matched++;
		}
		else {
			if (matched == 0) {
				begin = (begin+1)%head.size();
			}
			else {
				begin = (begin + matched - p[matched - 1])%head.size();
				matched = p[matched - 1];
			}
		}
	}

	return begin;
}

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
		vector<string> strings(n+1);
		for (int i = 0; i <= n; i++)
			cin >> strings[i];

		int ans = 0, length = strings[0].size();
		bool ccw = true;
		for (int i = 0; i < n; i++) {
			if (ccw)
				ans += rotate(strings[i + 1], strings[i]);
			else
				ans += rotate(strings[i], strings[i+1]);

			ccw = !ccw;
		}
		cout << ans << '\n';
	}
	return 0;
}