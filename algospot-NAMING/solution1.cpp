#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> getPartialMatch(const string& str)
{
	vector<int> ret(str.size(),0);
	int begin(1), matched(0);
	while (begin + matched < str.size()) {
		if (str[begin + matched] == str[matched]) {
			matched++;
			ret[begin + matched-1] = matched;
		}
		else {
			if (matched == 0) {
				begin++;
			}
			else {
				begin += matched - ret[matched-1];
				matched = ret[matched-1];
			}
		}
	}
	return ret;
}

vector<int> GetPreSuffix(const string& str)
{
	vector<int> p = getPartialMatch(str);
	vector<int> ret;
	int size = p.size();
	while (size > 0) {
		ret.push_back(p[size - 1]);
		size = p[size - 1];
	}

	return ret;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	string a, b;
	cin >> a >> b;
	string name = a + b;

	vector<int> result = GetPreSuffix(name);
	for (int i = result.size() - 2; i >= 0; i--)
		cout << result[i] << ' ';
	cout << name.size();

	return 0;
}