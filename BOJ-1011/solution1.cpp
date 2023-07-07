#include <iostream>
using namespace std;

int BinarySearch(int num, int left, int right)
{
	if (left > right) return right;

	int mid = left + (right - left) / 2;
	if (num < mid * mid)
		return BinarySearch(num, left, mid - 1);
	else // num >= mid*mid
		return BinarySearch(num, mid+1, right);
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int x, y;
		cin >> x >> y;
		int n = BinarySearch(y - x, 1, 46340); // 46340 = (int)sqrt(2^31)

		int ans;
		if (y - x > n*(n+1)) ans = 2*n + 1;
		else if (y - x > n*n) ans = 2*n;
		else ans = 2*n - 1;
		
		cout << ans << '\n';
	}
	return 0;
}