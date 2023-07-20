#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int n;
	cin >> n;
	vector<pair<int, int> > line(n);
	for (int i = 0; i < n; i++)
		cin >> line[i].first >> line[i].second;
	sort(line.begin(), line.end());

	int length = 0;
	int start = line[0].first, end = line[0].second;
	for (int i = 1; i < n; i++) {
		pair<int, int> now = line[i];
		if (now.first <= end) {
			end = max(end, now.second);
		}
		else {
			length += end - start;
			start = now.first;
			end = now.second;
		}
	}
	length += end - start;
	cout << length << '\n';

	return 0;
}