#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> GetPartialArray(string& str)
{
	int n = str.size();
	vector<int> ret(n, 0);

	int begin = 1, match = 0;
	while (begin + match < n) {
		if (str[begin + match] == str[match]) {
			match++;
			ret[begin + match - 1] = max(ret[begin + match - 1], match);
		}
		else {
			if (match == 0)
				begin++;
			else {
				begin += match - ret[match - 1];
				match = ret[match - 1];
			}
		}
	}

	return ret;
}

void RemoveBomb(string& str, string& bomb, string& ret)
{
	vector<pair<int, int>> remove;
	vector<int> p = GetPartialArray(bomb);

	// start ¿Œµ¶Ω∫, matched Ω÷
	stack < pair<int, int>> st;

	int n = str.size();
	int matched = 0, start=0;
	for (int i = 0; i < n; i++) {

		while (matched > 0 && str[i] != bomb[matched]) {
			st.push({ start,matched });
			matched = p[matched - 1];
			start = i - matched;
		}

		if (str[i] != bomb[matched]) {
			st = stack < pair<int, int>>(); //stack √ ±‚»≠
			start = -1;
		}

		if (str[i] == bomb[matched]) {
			if (start == -1) start = i;
			matched++;
			if (matched == bomb.size()) {
				remove.push_back({ start,i });
				
				if (!st.empty()) {
					start = st.top().first;
					matched = st.top().second;
					st.pop();
				}
				else {
					matched = 0;
					start = -1;
				}
			}
		}
	}

	sort(remove.begin(), remove.end());
	int begin = 0, end=-1;
	for (pair<int, int>& e : remove) {
		if (e.first <= end) continue;
		else if (e.first == end + 1) {
			end = e.second;
			continue;
		}

		begin = e.first;
		ret.append(str.begin() + (end + 1), str.begin() + begin);
		end = e.second;
	}
	ret.append(str.begin() + (end + 1), str.end());
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	string str, bomb, ans;
	cin >> str >> bomb;
	RemoveBomb(str, bomb, ans);

	if (ans.empty()) cout << "FRULA";
	else cout << ans;

	return 0;
}