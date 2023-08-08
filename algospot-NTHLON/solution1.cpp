#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

int Solve(vector<pair<int,int>>& estimate)
{
	// -200 ~ 200 범위의 dif에 대해서 최소의 sum을 저장
	vector<int> min_sum(401,0x7FFFFFFF);

	// (두 선수 예상 기록의 합, A기록 - B기록)
	priority_queue<pair<int, int> > pq;
	pq.push({ 0,0 });
	while (!pq.empty()) {
		int sum = -pq.top().first;
		int dif = pq.top().second;
		pq.pop();
		if (min_sum[dif + 200] < sum) continue;

		if (sum != 0 && dif == 0) return sum/2;
		
		for (pair<int, int>& e : estimate) {
			if (dif > 0 && e.second > 0 || dif < 0 && e.second < 0) continue;
			int next_sum = sum + e.first;
			int next_dif = dif + e.second;

			if (min_sum[next_dif + 200] > next_sum) {
				min_sum[next_dif + 200] = next_sum;
				pq.push({ -next_sum,next_dif });
			}
		}
	}
	return -1;
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int event_size;
		cin >> event_size;
		// (두 선수 예상 기록의 합, A기록 - B기록)
		vector<pair<int, int>> estimate;
		map<int, int> history;
		for (int i = 0; i < event_size; i++) {
			int a, b;
			cin >> a >> b;
			if (history.count(a - b) == 0 || history[a - b] > a + b)
				history[a - b] = a + b;
			//estimate.push_back({ a + b,a - b });
		}
		
		for (auto iter = history.begin(); iter != history.end(); iter++)
			estimate.push_back({ iter->second, iter->first });

		bool impossible = false;
		if (estimate[0].second > 0) {
			impossible = true;
			for (int i = 1; i < estimate.size(); i++)
				if (estimate[i].second <= 0) {
					impossible = false;
					break;
				}
		}
		else if (estimate[0].second < 0) {
			impossible = true;
			for (int i = 1; i < estimate.size(); i++)
				if (estimate[i].second >= 0) {
					impossible = false;
					break;
				}
		}

		if (impossible) {
			cout << "IMPOSSIBLE\n";
			continue;
		}

		cout << Solve(estimate) << '\n';
	}
	return 0;
}