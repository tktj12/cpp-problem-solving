#include <iostream>
#include <vector>

using namespace std;
int solve(int, int);

vector<int> fence(20000, 0);
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;

	while (tc--)
	{
		int n;
		cin >> n;
		for (int i = 0; i < n; ++i)
			cin >> fence[i];
		cout << solve(0, n - 1) << '\n';
	}
	return 0;
}

int solve(int left, int right)
{
	if (left == right)return fence[left];
	
	int mid = (left + right) / 2;
	int ret = max(solve(left, mid), solve(mid + 1, right));
	int lo = mid, hi = mid + 1;
	int height = min(fence[lo], fence[hi]);
	ret = max(ret, height * 2);

	while (left < lo || hi < right) {
		if (hi < right && (lo == left || fence[lo - 1] < fence[hi + 1])) {
			++hi;
			height = min(height, fence[hi]);
		}
		else {
			--lo;
			height = min(height, fence[lo]);
		}
		ret = max(ret, height * (hi - lo + 1));
	}
	return ret;
}