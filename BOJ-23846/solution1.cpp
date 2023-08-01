#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


int main()
{
	cout.precision(10);

	int n, k;
	cin >> n >> k;

	vector<double> prob_one(3001,0); // i번째 징검다리가 1칸이고 i+1~n번째 징검다리는 모두 3칸일 확률
	vector<double> prob_two(3001, 0); // i번째 징검다리가 2칸이고 i+1~n번째 징검다리는 모두 3칸일 확률

	prob_one[0] = 1.;
	for (int who = 0; who < k; who++) {
		vector<double> prob_two_buf(3001, 0);
		for (int i = 0; i <= n; i++) {
			double prob_two_now = prob_two[i];
			double prob_one_now = prob_one[i];
			prob_one[i] = prob_two[i] / 2;

			for (int j = i+1; j <= n; j++) {
				prob_two_now /= 3;
				prob_one_now /= 3;
				prob_two_buf[j] += prob_two_now + 2*prob_one_now;
			}
		}
		prob_two = prob_two_buf;
	}

	double ans = 1.;
	for (int i = 0; i <= n; i++) {
		ans -= prob_one[i] + prob_two[i];
	}
	cout << ans << endl;

	return 0;
}