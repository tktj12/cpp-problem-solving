#include <iostream>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;

const double PI = atan(1) * 4;

struct Data {
	double mid;
	double start;
	double end;
	double theta;
};

bool compare_size(const Data& a, const Data& b) {
	return a.theta > b.theta;
}
bool compare_pos(const Data& a, const Data& b) {
	return a.mid < b.mid;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cout.fixed;
	cout.precision(30);

	int tc;
	cin >> tc;
	while (tc--) {
		int n, ans(0);
		cin >> n;
		vector<Data> guard(n);
		for (int i = 0; i < n; ++i) {
			double x, y, r;
			cin >> y >> x >> r;
			if (r >= 16. || ans == 1) {
				ans = 1;
				continue;
			}

			double center_rad = atan(y/x);
			if (center_rad >= 0. && (y < 0. || x < 0.)) {
				center_rad += PI;
			}
			else if (center_rad < 0.) {
				if (y > 0. || x < 0.)
					center_rad += PI;
				else if (y < 0. || x > 0.)
					center_rad += 2 * PI;
			}
			guard[i].mid = center_rad;
			
			double theta_half = 2 * asin(r / 16);
			guard[i].theta = 2 * theta_half;
			guard[i].start = guard[i].mid - theta_half;
			guard[i].end = guard[i].mid + theta_half;

		}
		if (ans == 1) {
			cout << ans << '\n';
			continue;
		}

		sort(guard.begin(), guard.end(), compare_size);
		for (int i = 0; i < guard.size(); ++i) {
			for (int j = i + 1; j < guard.size(); ++j) {
				double mid_distance = guard[i].mid - guard[j].mid;
				if (mid_distance < 0.) {
					if (mid_distance < -PI)
						mid_distance += 2 * PI;
					else
						mid_distance = -mid_distance;
				}
				else if (mid_distance > PI)
					mid_distance = -(mid_distance - 2 * PI);

				if (mid_distance + guard[j].theta / 2 <= guard[i].theta / 2) {
					guard.erase(guard.begin() + j);
					j--;
				}
			}
		}
		
		sort(guard.begin(), guard.end(), compare_pos);
		bool impossible = true;
		ans = 200;
		for (int s = 0; s < guard.size(); ++s) {
			vector<Data> on_duty = {guard[s]};
			if (on_duty[0].start > 0. && on_duty[0].end < 2 * PI)
				continue;

			bool seek = false, find=false;
			double start = on_duty[0].start;
			for (int i = 1; i < guard.size(); ++i) {
				double end = on_duty.back().end;

				if (on_duty[0].mid < on_duty.back().mid) {
					if (end >= start + 2 * PI) {
						impossible = false;
						find = true;
						break;
					}
				}
				else if (on_duty[0].mid > on_duty.back().mid && end >= start) {
					impossible = false;
					find = true;
					break;
				}

				Data& next = guard[(s + i) % guard.size()];
				double next_start = next.start;
				if (on_duty.back().mid > next.mid)
					next_start += 2 * PI;

				if (seek) {
					if (next_start <= end)
						continue;
					else {
						on_duty.push_back(guard[(s+i-1)%guard.size()]);
						seek = false;
						--i;
					}
				}
				else {
					if (next_start <= end)
						seek = true;
					else break;
				}
			}
			if (seek) {
				on_duty.push_back(guard[(s-1+guard.size())%guard.size()]);
				if (on_duty.back().mid > on_duty[0].mid)
					start += 2 * PI;
				if (on_duty.back().end >= start) {
					impossible = false;
					find = true;
				}

			}

			if (find && on_duty.size() > 2) {
				start = on_duty[1].start;
				if (on_duty.back().mid > on_duty[1].mid)
					start += 2 * PI;
				if(on_duty.back().end >= start)
					on_duty.erase(on_duty.begin());
			}

			if (find)
				ans = min<int>(ans, on_duty.size());
		}

		if (impossible) {
			cout << "IMPOSSIBLE\n";
			continue;
		}

		cout << ans << '\n';
	}
	return 0;
}