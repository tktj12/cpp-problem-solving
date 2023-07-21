#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct seg {
	int start, end;

	bool operator<(const seg& rhs) {
		return start < rhs.start;
	}
};

inline int count(long long n) {
	return (n * (n + 1) / 2) % 20091101ll;
}

vector<pair<int,int> > psum_mod_k;
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int n, k;
		cin >> n >> k;
		psum_mod_k.clear();
		psum_mod_k.resize(n + 1);
		psum_mod_k[0] = { 0,0 };
		// 구간 합을 k로 나눈 나머지 구하기
		for (int i = 1; i <= n; i++) {
			int num;
			cin >> num;
			psum_mod_k[i] = { (psum_mod_k[i - 1].first + num) % k, i };
		}
		sort(psum_mod_k.begin(), psum_mod_k.end());

		// 인형을 살 수 있는 구간을 구하고, 가능한 주문 방법의 개수를 센다.
		vector<seg> segment;
		int answer1 = 0;
		int series_num_cnt=0;
		for (int i = 1; i <= n; i++) {
			vector<pair<int,int> >::iterator now = psum_mod_k.begin()+i;
			if (now->first == (now-1)->first) { // 인형을 살 수 있는 구간 발견
				segment.push_back({ (now - 1)->second + 1, now->second });
				series_num_cnt++;
			}
			else {
				if (series_num_cnt > 0)
					answer1 = (answer1 + count(series_num_cnt)) % 20091101;
				series_num_cnt = 0;
			}
		}
		if (series_num_cnt > 0)
			answer1 = (answer1 + count(series_num_cnt)) % 20091101;

		// 겹치지 않는 구간만 골랐을 때 구간의 개수의 최댓값 구하기
		// 그리디로 더 빨리 끝나는 구간만 선택
		sort(segment.begin(), segment.end());
		int answer2 = 0;
		int end = 0;
		for (int i = 0; i < segment.size(); i++) {
			if (segment[i].start <= end)
				end = min(end, segment[i].end);
			else {
				answer2++;
				end = segment[i].end;
			}
		}

		cout << answer1 << ' ' << answer2 << '\n';
	}
	return 0;
}