#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n;
	cin >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; i++) cin >> arr[i];

	int left=0, right=n-1;
	pair<int, int> ans;
	int min_sum = 0x7FFFFFFF;

	while (left != right) {
		int sum = arr[left] + arr[right];
		if (abs(sum) < abs(min_sum)) {
			min_sum = sum;
			ans = { arr[left], arr[right] };
		}

		if (abs(arr[left]) > abs(arr[right])) left++;
		else right--;
	}

	cout << ans.first << ' ' << ans.second;

	return 0;
}