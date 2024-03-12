#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int M[4'000'010];
void Manacher(string& S)
{
	int n = S.size();
	int r = 0,p = 0;
	for (int i = 1; i < n; i++) {
		if (i > r) {
			p = r = i;
			while (r < n && r <= 2 * p && S[2 * p - r] == S[r]) r++;
			r--;
			M[i] = r - p;
		}
		else {
			int j = 2 * p - i;
			if (M[j] < r - i)
				M[i] = M[j];
			else if (M[j] > r - i)
				M[i] = r - i;
			else {
				p = i;
				while (r < n && r <= 2 * p && S[2 * p - r] == S[r]) r++;
				r--;
				M[i] = r - p;
			}
		}
	}
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	string a,b;
	cin >> a;
	b.reserve(a.size() * 2 + 10);
	b.push_back('.');
	int n = a.size();
	for (int i = 0; i < n; i++) {
		b.push_back(a[i]);
		b.push_back('.');
	}
	Manacher(b);

	n = b.size();
	long long ans = 0;
	for (int i = 1; i < n; i++) {
		ans += (M[i] + 1) / 2;
	}
	cout << ans;

	return 0;
}