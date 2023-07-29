#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main(int argc, char** argv)
{
	cin.tie(nullptr), cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int T, test_case;

	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		long long n, d, ans(0);
		map<long long, long long> neg, pos;
		cin >> n >> d;
		for (int i = 0; i < n; i++) {
			int x;
			cin >> x;
			if (x == 0) ans++;
			else if (x < 0) neg[-x]++;
			else pos[x]++;
		}

		{
			auto it = pos.begin();
			for (int i = 1; i < pos.size(); i++) {
				auto prev = it;
				it++;
				it->second += prev->second;
			}

			it = neg.begin();
			for (int i = 1; i < neg.size(); i++) {
				auto prev = it;
				it++;
				it->second += prev->second;
			}
		}

		pos[-2000000002] = 0;
		pos[2000000002] = 0;

		neg[-2000000002] = 0;
		neg[2000000002] = 0;

		long long cand = ans;
		for (int i = 0; i < 2; i++) {

			long long x = 0;
			auto pos_end = (--pos.upper_bound(d));
			auto neg_end = (--neg.upper_bound(d));

			auto it = ++pos.begin();
			x = it->first;
			while (1) {
				// 더 이상 반대로는 못 간다면
				if (d - 2 * x - (++neg.begin())->first < 0) {
					ans += pos_end->second;
					break;
				}

				// 반대쪽으로 가는 게 더 나은 경우
				auto other_hand = (--neg.upper_bound(d - 2 * x))->second;
				if (other_hand > pos_end->second - it->second) {
					ans += it->second + other_hand;
					break;
				}

				// 끝까지 왔다면
				if (it == pos_end) {
					ans += it->second;
					break;
				}

				it++;
				x = it->first;
			}

			if (i == 1) break;
			swap(cand, ans);
			swap(pos, neg);
		}
		ans = max(ans, cand);
		cout << "Case #" << test_case + 1 << '\n';
		cout << ans << '\n';
	}

	return 0;
}