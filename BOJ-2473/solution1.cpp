#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int arr[5000], N;
int LowerBound(int num)
{
	int lo = 0, hi = N;
	// arr[lo] < num, num <= arr[hi]
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (arr[mid] < num)
			lo = mid;
		else hi = mid;
	}
	return hi;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> arr[i];
	sort(arr, arr + N);

	long long min_sum = 0xFFFFFFFFFFFFFFFLL;
	int ans[3];
	for (int i = 0; i < N - 1; i++)
		for (int j = i + 1; j < N; j++) {
			long long sum = arr[i] + arr[j];
			int right = LowerBound(-sum);
			int left = right - 1;
			int third;

			while (1) {
				if (right == N) {
					while (left == i || left == j)left--;
					third = left;
					break;
				}
				else if (left == -1) {
					while (right == i || right == j) right++;
					third = right;
					break;
				}

				if (right == i || right == j) right++;
				else if (left == i || left == j) left--;
				else {
					if (abs(sum + arr[left]) > abs(sum + arr[right]))
						third = right;
					else
						third = left;
					break;
				}
			}

			sum = abs(sum + arr[third]);
			if (min_sum > sum) {
				min_sum = sum;
				ans[0] = arr[i], ans[1] = arr[j], ans[2] = arr[third];
			}
		}

	sort(ans, ans + 3);
	cout << ans[0] << ' ' << ans[1] << ' ' << ans[2];

	return 0;
}