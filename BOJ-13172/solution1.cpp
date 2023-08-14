#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int M = 1000000007;

long long BigPower(long long n, long long e)
{
	if (e == 1) return n;
	else if (e % 2 > 0) return (n*BigPower(n, e - 1))%M;

	long long ret = BigPower(n, e / 2);
	return ret * ret % M;
}

inline int ModInv(int n)
{
	return BigPower(n, M - 2);
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n;
	long long ans(0);
	cin >> n;
	for (int i = 0; i < n; i++) {
		long long dice, sum;
		cin >> dice >> sum;
		if (sum % dice == 0) ans = (ans + sum / dice) % M;
		else ans = (ans + sum * ModInv(dice)) % M;
	}
	cout << ans;

	return 0;
}