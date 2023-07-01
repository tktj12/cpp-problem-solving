#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
double DP2(int here, int day, int prison);

vector<int> path[50];
double cache[50][101];
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

		memset(cache, -1, sizeof(cache));
		int t;
		cin >> t;
		while (t--) {
			int village;
			cin >> village;
			cout << DP2(village, day, prison) << ' ';
		}
		cout << '\n';
	}

	return 0;
}

double DP2(int here, int day, int prison)
{
	double& ret = cache[here][day];
	if (!_isnan(ret)) return ret;
	if (day == 0) {
		if (here == prison) return ret = 1.;
		else return ret = 0.;
	}

	ret = 0.;
	for (int neighbor : path[here])
		ret += DP2(neighbor, day - 1, prison)/path[neighbor].size();

	return ret;
}