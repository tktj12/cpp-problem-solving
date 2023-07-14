#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
int solve(int k);

int sign_size;
int loc[5000], first[5000], gap[5000];
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int k;
		cin >> sign_size >> k;
		for (int i = 0; i < sign_size; ++i)
			cin >> loc[i] >> first[i] >> gap[i];

		cout << solve(k) << '\n';
	}
	return 0;
}

bool decision(int dist, int val)
{
	int sum =0;
	for (int i = 0; i < sign_size; ++i) {
		if (loc[i] <= dist)
			sum += first[i] / gap[i] + 1;

		else if (loc[i] > dist && loc[i] - first[i] <= dist)
			sum += 1 + (dist - loc[i] + first[i]) / gap[i];
	}

	return sum < val;
}

int solve(int k)
{
	int lo = 0, hi = 8030000;

	while (lo != hi) {
		int mid = lo + (hi - lo) / 2;
		if (decision(mid, k))
			lo = mid+1;
		else
			hi = mid;
	}

	return hi;
}