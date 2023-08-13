#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

class SuffixComparator {
public:
	int t;
	vector<int> group;
	SuffixComparator(int t, vector<int>& group) : t(t), group(group) {}

	bool operator()(int a, int b) {
		if (group[a] != group[b]) return group[a] < group[b];
		else return group[a + t] < group[b + t];
	}
};

vector<int> perm;
void ManberMyers(string& str)
{
	int n = str.size();
	vector<int> group(n+1);
	for (int i = 0; i < n; i++) group[i] = str[i];
	group[n] = -1;

	perm = vector<int>(n);
	for (int i = 0; i < n; i++) perm[i] = i;
	int t = 1;
	while (true) {
		SuffixComparator compare_using_2t(t, group);
		sort(perm.begin(), perm.end(), compare_using_2t);
		t *= 2;
		if (t >= n) break;

		vector<int> new_group(n + 1);
		new_group[n] = -1;

		new_group[perm[0]] = 0;
		for (int i = 1; i < n; i++) {
			if (compare_using_2t(perm[i - 1], perm[i])) {
				new_group[perm[i]] = new_group[perm[i - 1]] + 1;
			}
			else {
				new_group[perm[i]] = new_group[perm[i - 1]];
			}
		}
		group = new_group;
	}

	// return perm;
}

inline void IntToChar(string& ans, int num)
{
	if (num == 0) {
		ans += '0';
		ans += '\n';
		return;
	}

	stack<char> st;
	while (num) {
		st.push(num % 10 + '0');
		num /= 10;
	}

	while (!st.empty())
		ans += st.top(), st.pop();
	ans += '\n';
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	if (freopen("C:\\Users\\123au\\cpp-problem-solving\\input.txt", "r", stdin) == nullptr)
		return 1;

	string str;
	cin >> str;
	ManberMyers(str);

	int n = str.size();
	string ans;
	ans.reserve(10 * n);
	for (int i = 0; i < n; i++)
		IntToChar(ans, perm[i]);
	cout << ans;

	return 0;
}