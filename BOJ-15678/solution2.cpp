#include <iostream>
#include <deque>
using namespace std;

int N, D;
const long long NEGATIVE_INF = 0x8000000000000000LL;

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> N >> D;
	long long ans = NEGATIVE_INF;
	deque<pair<int, long long>> deq;
	for (int i = 0; i < N; i++) {
		int x; cin >> x;
		ans = max<long long>(ans, x);

		if (deq.empty()) {
			if (x > 0) deq.push_front({ i,x });
		}
		else {
			if (deq.back().first < i - D)
				deq.pop_back();

			long long e = deq.empty() ? x : x + deq.back().second;
			if (e <= 0) continue;

			while (!deq.empty() && deq.front().second <= e)
				deq.pop_front();

			deq.push_front({ i,e });
			ans = max(ans, e);
		}
	}

	cout << ans;
	return 0;
}