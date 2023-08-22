#include <iostream>
#include <vector>
using namespace std;

int Z[100000];
int cnt[100001];
void MakeZArray(string& S, vector<int>& presuffix)
{
	int n = S.size();
	int l = 0, r = 0;
	for (int i = 1; i < n; i++) {
		if (i >= r) {
			l = r = i;
			while (r < n && S[r-l] == S[r]) r++;
			Z[i] = r-l;
			if (r == n) presuffix.push_back(r - i);
		}
		else {
			if (Z[i - l] < r - i) {
				Z[i] = Z[i - l];
			}
			else {
				l = i;
				while (r < n && S[r - l] == S[r]) r++;
				Z[i] = r - l;
				if (r == n) presuffix.push_back(r - i);
			}
		}
		cnt[Z[i]]++;
	}
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	string S; cin >> S;

	vector<int> presuffix;
	presuffix.push_back(S.size());
	MakeZArray(S, presuffix);

	cnt[S.size()] = 1;
	for (int i = S.size(); i > 0; i--)
		cnt[i] += cnt[i + 1];

	cout << presuffix.size() << '\n';
	for (int i = presuffix.size() - 1; i >= 0; i--)
		cout << presuffix[i] << ' ' << cnt[presuffix[i]] << '\n';

	return 0;
}