#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
string SearchAll(string&, int);
bool IsIncluded(const string&, const string&);

vector<string> substr;
int N;
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		substr.clear();

		cin >> N;
		for (int i = 0; i < N; i++) {
			string s;
			cin >> s;
			substr.push_back(s);
		}
		
		cout << SearchAll({}, 0) << '\n';
	}
	return 0;
}

string SearchAll(string& source, int taken)
{
	if (taken == (1 << N) - 1) return source;

	string best(601, 0), cand;
	for (int i = 0; i < N; i++) {
		if (taken & 1 << i) continue;
		int next_taken = taken | (1 << i);

		if (source.empty()) {
			cand = SearchAll(substr[i], next_taken);
			if (cand.size() < best.size())
				best = cand;
			continue;
		}

		string big, small;
		if (source.size() >= substr[i].size()) {
			big = source;
			small = substr[i];
		}
		else {
			big = substr[i];
			small = source;
		}

		if (IsIncluded(big, small)) {
			cand = SearchAll(big, next_taken);
			if (cand.size() < best.size())
				best = cand;
			continue;
		}

		int small_size = small.size();
		// small의 오른쪽 부터
		for (int loop = 0; loop < 2; loop++) {
			cand = small + big;

			for (int i = small_size-1; i >= 0; i--) {
				bool coincide;
				for (int j = i; j >= 0; j--) {
					if (small[small.size() - j - 1] == big[i - j]) {
						coincide = true;
					}
					else {
						coincide = false;
						break;
					}
				}
				if (coincide) {
					cand.assign(small.begin(), small.end() - i - 1);
					cand += big;
					break;
				}
			}
			cand = SearchAll(cand, next_taken);
			if (cand.size() < best.size())
				best = cand;
			swap(small, big);
		}
	}

	return best;
}

bool IsIncluded(const string& big, const string& small)
{
	bool ret = false;
	for (int i = 0; i < big.size() - small.size() + 1; i++) {
		if (big[i] == small[0]) {
			ret = true;
			for (int j = 1; j < small.size(); j++) {
				if (big[i + j] == small[j])
					ret = true;
				else {
					ret = false;
					break;
				}
			}
		}
		if (ret) break;
	}
	return ret;
}