#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MX = 100000;
int Fenwick[MX+1];

int GetSum(int n)
{
	int sum = 0;
	while (n > 0) {
		sum += Fenwick[n];
		n &= n - 1;
	}
	return sum;
}

bool Add(int n)
{
	int pos = n;
	while (pos <= MX) {
		Fenwick[pos]++;
		pos += (pos & -pos);
	}

	return GetSum(n) <= n;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n, p;
	cin >> n >> p;

	bool able = true;
	int ans = 0;
	for (int i = 0; i < p; i++) {
		int n; cin >> n;
		if (able) {
			able = Add(n);
			ans += able;
		}
	}

	cout << ans;

	return 0;
}