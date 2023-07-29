#include <iostream>
#include <vector>
#include <map>
#include <list>

using namespace std;

struct Data {
	int val;
	int cnt;

	bool operator==(const Data& rhs) {
		return val == rhs.val && cnt == rhs.cnt;
	}
	bool operator!=(const Data& rhs) {
		return !(*this == rhs);
	}
};

// 정리된 배열 spread가 있을 때 2의 거듭제곱으로 똑같이 나눌 수 있는 경우의 최대 횟수를 2의 거듭제곱으로 반환
void Divide(vector<Data>& spread, int& divisor)
{
	if (spread.size() % 2 > 0) return;

	int mid = spread.size() / 2;
	int i = 0;
	while (mid < spread.size()) {
		if (spread[i] != spread[mid]) return;
		i++, mid++;
	}
	divisor *= 2;
	mid = spread.size() / 2;
	vector<Data> next(spread.begin(), spread.begin()+mid);
	Divide(next, divisor);
}

int main(int argc, char** argv)
{
	//setbuf(stdout, NULL);
	cin.tie(nullptr), cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int T, test_case;

	cin >> T;
	for (test_case = 0; test_case < T; test_case++)
	{
		cout << "Case #" << test_case + 1 << '\n';

		int n;
		long long total(0);
		cin >> n;

		typedef list<Data>::iterator Ptr;
		vector<pair<int, Ptr> > piles;
		map<int, Ptr> blanks;
		list<Data> arr;

		int bead;
		cin >> bead;
		total += bead;
		arr.push_back({bead, 1});
		if (bead == 0)
			blanks[-int(arr.size() - 1)] = (--arr.end());
		else if (bead > 1)
			piles.push_back({ arr.size() - 1, --arr.end() });

		for (int i = 1; i < n; i++) {
			cin >> bead;
			total += bead;
			if (bead <= 1 && bead == arr.back().val)
				arr.back().cnt++;
			else {
				arr.push_back({ bead,1 });
				if (bead == 0)
					blanks[-int(arr.size() - 1)] = (--arr.end());
				else if (bead > 1)
					piles.push_back({ arr.size() - 1, --arr.end() });
			}
		}
		if (total >= n || total == 0) {
			cout << 1 << '\n';
			continue;
		}

		// 빈 공간에 구슬 할당
		for (int i = 0; i < piles.size(); i++) {
			pair<int, Ptr>& e = piles[i];

			map<int, Ptr>::iterator closest_blank = blanks.upper_bound(-e.first);
			if (closest_blank == blanks.end())
				closest_blank = blanks.upper_bound(-int(arr.size()));

			if (closest_blank->second->cnt + 1 <= e.second->val) {
				closest_blank->second->val = 1;
				e.second->val -= closest_blank->second->cnt;
				blanks.erase(closest_blank);
				if (e.second->val > 1) i--;
			}
			else {
				auto insert_pos = closest_blank->second;
				arr.insert(++insert_pos, { 1, e.second->val - 1 });
				closest_blank->second->cnt -= e.second->val - 1;
				e.second->val = 1;
			}

		}

		// arr 다시 정리
		vector<Data> spread;
		spread.reserve(arr.size());
		auto iter = arr.begin();
		spread.push_back({ iter->val, iter->cnt });
		
		for (int i = 1; i < arr.size(); i++) {
			++iter;
			if (iter->val == spread.back().val)
				spread.back().cnt += iter->cnt;
			else
				spread.push_back({ iter->val, iter->cnt });
		}

		// spread는 0과 1로만 이루어져있음
		// 끝부분 이어주기
		if (spread.size()>1 && spread[0].val == spread.back().val) {
			spread[0].cnt += spread.back().cnt;
			spread.erase(spread.end() - 1);
		}

		int divisor = 1;
		Divide(spread, divisor);
		cout << n / divisor << '\n';
	}

	return 0;
}