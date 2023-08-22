#include <iostream>
using namespace std;

int Z[100000];
void MakeZArray(string& S)
{
	int n = S.size();
	int l = 0, r = 0;
	for (int i = 1; i < n; i++) {
		if (i >= r) {
			l = r = i;
			while (r < n && S[r - l] == S[r]) r++;
			Z[i] = r - l;
		}
		else {
			if (Z[i - l] < r - i) {
				Z[i] = Z[i - l];
			}
			else {
				l = i;
				while (r < n && S[r - l] == S[r]) r++;
				Z[i] = r - l;
			}
		}
	}
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n, k;
	cin >> n >> k;
	string S; cin >> S;
	if (n <= k) {
		cout << n;
		return 0;
	}

	MakeZArray(S);
	int pattern;
	for (pattern = (n + k) / 2; pattern > 0; pattern--) {
		bool able = true;
		for (int i = pattern; i < n; i += pattern) {
			if (n - i > pattern) {
				if (Z[i] < pattern) {
					able = false;
					break;
				}
			}
			else if (Z[i] < n - i || i + pattern > n + k) {
				able = false;
				break;
			}
		}
		if (able) break;
	}

	cout << pattern;

	return 0;
}