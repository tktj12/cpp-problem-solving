#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;

vector<int> FlipSection(vector<int> arr, int begin, int end)
{
	while (begin < end)
		swap(arr[begin++], arr[end--]);
	return arr;
}

map<vector<int>, int> dist[8];
void BfsPreCalcDistance(int n) {
	map<vector<int>, int>& make_dist = dist[n-1];
	vector<int> arr(n);
	for (int i = 0; i < n; i++) arr[i] = i;
	// 수열, 이동거리
	queue<vector<int> > q;
	make_dist[arr] = 0;
	q.push(arr);
	while (!q.empty()) {
		vector<int> here = q.front(); q.pop();
		int d = make_dist[here] + 1;

		for (int begin = 0; begin < n-1; begin++) {
			for (int end = begin + 1; end < n; end++) {
				vector<int> there = FlipSection(here, begin, end);
				if (make_dist.count(there) == 0) {
					make_dist[there] = d;
					q.push(there);
				}
			}
		}
	}
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	for (int i = 1; i <= 8; i++)
		BfsPreCalcDistance(i);

	int tc;
	cin >> tc;
	while (tc--) {
		int n;
		cin >> n;
		vector<pair<int, int>> arr(n);
		for (int i = 0; i < n; i++) {
			cin >> arr[i].first;
			arr[i].second = i;
		}

		sort(arr.begin(), arr.end());
		vector<int> equivalence(n);
		for (int i = 0; i < n; i++)
			equivalence[arr[i].second] = i;

		cout << dist[n-1][equivalence] << '\n';
	}
	return 0;
}