#include <iostream>
using namespace std;

int ranking[1002], num_of_students[1002];
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cout << fixed;
	cout.precision(15);

	int tc;
	cin >> tc;
	while (tc--) {
		int subject_size, limit;
		cin >> subject_size >> limit;
		int dividend(0), divisor(0);
		for (int i = 0; i < subject_size; ++i) {
			cin >> ranking[i] >> num_of_students[i];
			dividend += ranking[i];
			divisor += num_of_students[i];
		}
		bool chosen[1000] = { 0, };

		for (int i = 0; i < subject_size - limit; ++i) {
			double best = 64.;
			int choice = -1;
			for (int j = 0; j < subject_size; ++j) {
				if (chosen[j]) continue;
				double top = dividend - ranking[j];
				double bottom = divisor - num_of_students[j];
				if (top / bottom < min(best, double(dividend)/divisor)) {
					best = top / bottom;
					choice = j;
				}
			}
			if (choice == -1) break;
			chosen[choice] = true;
			dividend -= ranking[choice];
			divisor -= num_of_students[choice];
		}

		cout << (double)dividend / divisor << '\n';
	}
	return 0;
}