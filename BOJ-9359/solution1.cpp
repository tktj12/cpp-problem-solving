#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
using ll = long long;

// inclusion and exclusion
void IAE(vector<int>& S, int depth, int choose, ll num, ll a, ll b, ll& res)
{
	if (depth == S.size()) {
		if (choose > 0) {
			ll tp = b / num - (a - 1) / num;
			if (choose % 2 > 0) res -= tp;
			else res += tp;
		}
		return;
	}

	IAE(S, depth + 1, choose, num, a, b, res);
	IAE(S, depth + 1, choose + 1, num*S[depth], a, b, res);
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc; cin >> tc;
	for (int _tc = 1; _tc <= tc; _tc++) {
		ll a, b, ans=0;
		int n;
		cin >> a >> b >> n;
		ans = b - a + 1;

		if (n == 1) {
			cout << "Case #" << _tc << ": " << ans << '\n';
			continue;
		}

		int sqrtn = sqrt(n);
		vector<int> S;
		for (int i = 2; i <= sqrtn; i++) {
			if (n % i == 0) S.push_back(i);

			while (n % i == 0) n /= i;

			if (n == 1) break;
		}
		if (n > 1) S.push_back(n);

		IAE(S, 0, 0, 1, a, b, ans);

		cout << "Case #" << _tc << ": " << ans << '\n';
	}
	
	return 0;
}