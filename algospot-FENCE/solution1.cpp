#include <iostream>
#include <vector>

using namespace std;

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
		vector<int> fence(n,0);
		for (int i = 0; i < n; ++i)
			cin >> fence[i];

		int max(0), sum(0);
		for (int h = 1; h <= 10000; ++h) {
			for (int i = 0; i < n; ++i) {
				if (fence[i] >= h) sum += h;
				else {
					if (sum >= max) max = sum;
					sum = 0;
				}
			}
			if (sum > max) max = sum;
		}

		cout << max << '\n';
	}

	return 0;
}