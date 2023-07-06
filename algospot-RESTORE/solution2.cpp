#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
bool IsIncluded(const string&, const string&);
bool compare(const string&, const string&);
int Memoize(int, int, int);
string MakeAnswer(int, int, int);
int CountCoincide(string&, string&);

vector<string> substr;
int cache[15][1 << 15];
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		memset(cache, 0, sizeof(cache));
		substr.clear();

		int n;
		cin >> n;
		string s;
		for (int i = 0; i < n; i++) {
			cin >> s;
			substr.push_back(s);
		}
		sort(substr.begin(), substr.end(), compare);
		for (int i = 0; i < substr.size(); i++)
			for (int j = i + 1; j < substr.size(); j++)
				if (IsIncluded(substr[i], substr[j])) {
					substr.erase(substr.begin() + j);
					j--;
				}

		Memoize(0, 0, 0);
		cout << MakeAnswer(0, 0, 0) << '\n';
	}
	return 0;
}

bool compare(const string& a, const string& b) {
	return a.size() > b.size();
}

bool IsIncluded(const string& big, const string& small)
{
	bool ret = false;
	for (int i = 0; i < big.size() - small.size() + 1; i++) {
		ret = true;
		for (int j = 0; j < small.size(); j++) {
			if (big[i + j] != small[j]) {
				ret = false;
				break;
			}
		}
		if (ret) break;
	}

	return ret;
}

int CountCoincide(string& left, string& right)
{
	int ret = 0;
	int min_size = min(left.size(), right.size());
	for (int i = 1; i < min_size; i++) {
		ret = min_size - i;
		for (int j = 0; j < min_size - i; j++) {
			if (left[left.size() - min_size + i + j] != right[j]) {
				ret = 0;
				break;
			}
		}
		if (ret > 0) break;
	}

	return ret;
}

int Memoize(int depth, int pre_idx, int taken)
{
	if (depth == substr.size()) return 0;
	int& ret = cache[pre_idx][taken];
	if (ret > 0) return ret;
	ret = 987654321;

	for (int i = 0; i < substr.size(); i++) {
		if (taken & 1 << i) continue;

		int coincide = depth > 0 ? CountCoincide(substr[pre_idx], substr[i]) : 0;

		ret = min<int>(ret, Memoize(depth + 1, i, taken | 1 << i) + substr[i].size() - coincide);
	}
	return ret;
}

string MakeAnswer(int depth, int pre_idx, int taken)
{
	if (depth == substr.size()) return {};

	int choice, min_len = 987654321;
	for (int i = 0; i < substr.size(); i++) {
		if (taken & 1 << i) continue;
		if (cache[i][taken | 1 << i] + substr[i].size() < min_len) {
			min_len = cache[i][taken | 1 << i] + substr[i].size();
			choice = i;
		}
	}

	int coincide = depth > 0 ? CountCoincide(substr[pre_idx], substr[choice]) : 0;

	string ret(substr[choice].begin() + coincide, substr[choice].end());

	return ret + MakeAnswer(depth + 1, choice, taken | (1 << choice));
}