#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

bool IsMatch(string&, string&);

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		set<string> matching_strings;
		string pattern, str;
		cin >> pattern;
		
		int n;
		cin >> n;
		for (int i = 0; i < n; ++i) {
			cin >> str;
			if (IsMatch(pattern, str))
				matching_strings.insert(str);
		}
		for (auto &e : matching_strings)
			cout << e << '\n';
	}
	return 0;
}

const int NORMAL = 0, ASTERISK = 1;
bool IsMatch(string& pattern, string& str)
{
	string::iterator cur = pattern.begin();
	string::iterator last_asterisk_next = pattern.end();

	int state = NORMAL, saved_index(0);
	if (*cur == '*') {
		state = ASTERISK;
		while (1) {
			if (++cur == pattern.end()) return true;
			if (*cur != '*') break;
		}
		last_asterisk_next = cur;
	}

	for (int i = 0; i < str.size(); ++i) {
		if (*cur == '?' || *cur == str[i]) {
			if (state == ASTERISK) saved_index = i;
			++cur;
			state = NORMAL;
			if (cur == pattern.end()) {
				if (i == str.size() - 1)
					return true;
				else if (last_asterisk_next != pattern.end()) {
					i = saved_index;
					cur = last_asterisk_next;
					state = ASTERISK;
				}
				else return false;
			}
			else if (*cur == '*') {
				state = ASTERISK;
				while (1) {
					if (++cur == pattern.end()) return true;
					if (*cur != '*') break;
				}
				last_asterisk_next = cur;
			}
		}
		else if (state == ASTERISK) continue;
		else if (last_asterisk_next != pattern.end()) {
			i = saved_index;
			cur = last_asterisk_next;
			state = ASTERISK;
		}
		else return false;
	}
	return false;
}