#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

const int MX = 300'001;
int N, K;
map<int,int> capacity;
// weight, price 
pair<int, int> gem[MX];

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> N >> K;
	for (int i = 0; i < N; i++)
		cin >> gem[i].second >> gem[i].first;
	for (int i = 0; i < K; i++) {
		int c; cin >> c;
		capacity[c]++;
	}
	sort(gem, gem + N, greater<>());

	long long ans = 0;
	for (int i = 0; i < N; i++) {
		auto iter = capacity.lower_bound(gem[i].second);
		if (iter != capacity.end()) {
			ans += gem[i].first;
			iter->second--;
			if (iter->second == 0) capacity.erase(iter);
		}
	}

	cout << ans;

	return 0;
}