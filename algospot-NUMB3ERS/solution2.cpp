#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
double DP(int now, int village, int remaining_day);

vector<int> path[50];
double cache[50][100];
int N;
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cout << fixed;
	cout.precision(8);

	int tc;
	cin >> tc;
	while (tc--) {
		int day, prison;
		cin >> N >> day >> prison;
		for (int i = 0; i < N; ++i) {
			path[i].clear();
			for (int j = 0; j < N; ++j) {
				bool is_connected;
				cin >> is_connected;
				if (is_connected) path[i].push_back(j);
			}
		}

		int t;
		cin >> t;
		while (t--) {
			int village;
			cin >> village;
			memset(cache, -1, sizeof(cache));
			cout << DP(prison, village, day) << ' ';
		}
		cout << '\n';
	}

	return 0;
}

double DP(int now, int village, int remaining_day)
{
	double& ret = cache[now][remaining_day];
	if (!_isnan(ret)) return ret;
	if (remaining_day == 0) {
		if (now == village)	return ret = 1.;
		else return ret = 0.;
	}

	ret = 0.;
	for (int i = 0; i < path[now].size(); ++i)
		ret += DP(path[now][i], village, remaining_day - 1) / path[now].size();

	return ret;
}