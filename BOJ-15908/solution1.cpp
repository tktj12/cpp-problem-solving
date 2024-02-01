#include <iostream>
#include <vector>
using namespace std;

int N, dat[100000], p[100000];

bool Det(int ceiling) {
	vector<bool> restore(N + 1, false);
	vector<int> unremovable_psum(100001, 0), true_psum(100002, 0);
	restore[N] = true;
	true_psum[N] = 1;

	for (int i = N - 1; i >= 0; i--) {
		if (p[i] <= ceiling && restore[i + 1] == true) {
			restore[i] = true;
		}
		else {
			int lo = i + dat[i], hi = N + 1;
			while (lo + 1 < hi) {
				int mid = (lo + hi) / 2;
				if (unremovable_psum[i + 1] - unremovable_psum[mid] < dat[i])
					lo = mid;
				else
					hi = mid;
			}

			if (lo <= N && true_psum[i + dat[i]] - true_psum[lo + 1])
				restore[i] = true;
		}

		true_psum[i] = restore[i] + true_psum[i + 1];
		unremovable_psum[i] = unremovable_psum[i + 1] + (p[i] > ceiling);
	}

	return restore[0];
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> N;
	for (int i = 0; i < N; i++) cin >> dat[i];
	for (int i = 0; i < N; i++) cin >> p[i];

	int lo = -1, hi = N;
	while (lo + 1 < hi) {
		int mid = (lo + hi) / 2;
		if (Det(mid) == true)
			hi = mid;
		else
			lo = mid;
	}

	cout << hi;
	return 0;
}