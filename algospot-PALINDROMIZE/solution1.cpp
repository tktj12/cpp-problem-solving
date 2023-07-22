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

int solve(const string& str)
{
	string flipped(str.rbegin(), str.rend());
	vector<int> p = getPartialMatch(flipped);

	int begin(0), matched(0);
	while (begin + matched < str.size()) {
		if (str[begin + matched] == flipped[matched]) {
			matched++;
		}
		else {
			if (matched == 0) {
				begin++;
			}
			else {
				begin += matched - p[matched - 1];
				matched = p[matched - 1];
			}
		}
	}
	return 2*str.size() - matched;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		string s;
		cin >> s;
		cout << solve(s) << '\n';
	}
	return 0;
}