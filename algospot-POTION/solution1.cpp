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
	while (tc--) {
		int n;
		cin >> n;
		vector<int> recipe(n), added(n);
		for (int i = 0; i < n; ++i) cin >> recipe[i];
		for (int i = 0; i < n; ++i) cin >> added[i];

		double max_r=0.;
		int largest_ratio = -1;
		for (int i = 0; i < n; ++i) {
			double ratio = double(added[i]) / recipe[i];
			if (ratio > max_r) {
				max_r = ratio;
				largest_ratio = i;
			}
		}

		int standard = recipe[largest_ratio];	// 비율이 가장 큰 놈이 기준
		int k = added[largest_ratio]-1;
		bool end_flag = false;
		while (!end_flag) {
			k++;
			end_flag = true;
			for (int i = 0; i < n; ++i)
				if ((k*recipe[i]) % standard) { // 나누어 떨어지지 않으면
					end_flag = false;
					break;
				}
		}

		for (int i = 0; i < n; ++i)
			cout << k * recipe[i] / standard - added[i] << ' ';
		cout << '\n';
	}

	return 0;
}