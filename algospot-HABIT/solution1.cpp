#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

class Comparator {
	const vector<int>& group;
	int t;
public:
	Comparator(const vector<int>& _group, int _t) : group(_group), t(_t) {}

	bool operator()(int a,int b) const {
		if (group[a] != group[b])
			return group[a] < group[b];
		else 
			return group[a + t] < group[b + t];
	}
};

vector<int> GetSuffixArray(const string& s)
{
	int n = s.size();
	vector<int> group(n + 1);
	for (int i = 0; i < n; i++) group[i] = s[i];
	group[n] = -1;

	vector<int> perm(n);
	for (int i = 0; i < n; i++) perm[i] = i;

	int t = 1;
	while (t < n) {
		Comparator compare(group, t);
		sort(perm.begin(), perm.end(), compare);
		t *= 2;
		if (t >= n) break;

		vector<int> new_group(n + 1);
		new_group[perm[0]] = 0;
		new_group[n] = -1;
		for (int i = 1; i < n; i++) {
			if (compare(perm[i-1],perm[i])) {
				new_group[perm[i]] = new_group[perm[i - 1]] + 1;
			}
			else {
				new_group[perm[i]] = new_group[perm[i - 1]];
			}
		}
		group = new_group;
	}

	return perm;
}

int CommonPrefix(int i, int j, const string& s)
{
	int ret = 0;
	while (i < s.size() && j < s.size() && s[i] == s[j])
		i++, j++, ret++;

	return ret;
}

int Solve(const string& s, int k)
{
	if (k == 1) return s.size();

	vector<int> suffix = GetSuffixArray(s);
	int ret = 0, n = s.size();
	list<pair<int, int>> len;
	len.push_back({ n - suffix[0], 1});

	for (int i = 1; i < n; i++) {
		int common_prefix = CommonPrefix(suffix[i], suffix[i - 1], s);

		pair<int, int> l(common_prefix, 1);
		if (common_prefix == 0) {
			len.clear();
			l.first = n - suffix[i];
			l.second = 0;
		}
		else {
			while (!len.empty() && len.back().first >= common_prefix) {
				l.second = len.back().second;
				len.erase(--len.end());
			}
		}

		len.push_back(l);
		for (pair<int, int>& e : len) e.second++;

		if (len.front().second >= k) {
			ret = max(ret, len.front().first);
			len.erase(len.begin());
		}
	}

	return ret;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int k;
		string s;
		cin >> k >> s;
		cout << Solve(s, k) << '\n';
	}
	return 0;
}