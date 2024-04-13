#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

// 각 접미사들의 첫 t글자를 기준으로 한 그룹 번호가 주어질 때,
// 주어진 두 접미사를 첫 2*t글자를 기준으로 비교한다.
// group[]은 길이가 0인 접미사도 포함한다.
class Comparator {
public:
	const vector<int>& group;
	int t;
	Comparator(const vector<int>& _group,int _t) : group(_group),t(_t) {}
	bool operator() (int a,int b) {
		// 첫 t글자가 다르면 이들을 이용해 비교한다.
		if (group[a] != group[b]) return group[a] < group[b];
		// 아니라면 S[a+t..]와 S[b+t..]의 첫 t글자를 비교한다.
		return group[a + t] < group[b + t];
	}
};

// s의 접미사 배열을 계산한다.
vector<int> GetSuffixArray(const string& s) {
	int n = s.size();
	// group[i] = 접미사들을 첫 t글자를 기준으로 정렬했을 때, S[i..]가 들어가는 그룹 번호
	int t = 1;
	vector<int> group(n + 1);
	for (int i = 0; i < n; ++i) group[i] = s[i];
	group[n] = -1;
	// 결과적으로 만들어질 접미사 배열
	vector<int> perm(n);
	for (int i = 0; i < n; i++) perm[i] = i;
	while (t < n) {
		// 첫 2t 글자를 기준으로 perm을 다시 정렬한다.
		Comparator compare(group,t);
		sort(perm.begin(),perm.end(),compare);
		t *= 2;
		if (t >= n) break;

		// 2t 글자를 기준으로 한 그룹을 만든다.
		vector<int> new_group(n + 1);
		new_group[n] = -1;
		new_group[perm[0]] = 0;
		for (int i = 1; i < n; i++) {
			new_group[perm[i]] = new_group[perm[i - 1]];
			if (compare(perm[i - 1],perm[i]))
				new_group[perm[i]]++;
		}
		group = new_group;
	}
	return perm;
}

vector<int> BuildLCP(vector<int>& sa,const string& s) {
	int n = s.size(),k = 0;
	vector<int> lcp(n),isa(n);
	for (int i = 0; i < n; ++i) isa[sa[i]] = i;

	for (int i = 0; i < n; ++i) {
		if (isa[i] > 0) {
			int j = sa[isa[i] - 1];
			while (s[i + k] == s[j + k]) k++;
			lcp[isa[i]] = k;
			k = k > 0 ? k - 1 : 0;
		}
	}

	return lcp;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	string s;
	cin >> s;
	vector<int> sa = GetSuffixArray(s);
	vector<int> lcp = BuildLCP(sa,s);

	int n = s.size();
	long long ans = 0;
	for (int i = 0; i < n; i++) {
		ans += n - sa[i] - lcp[i];
	}
	cout << ans;

	return 0;
}