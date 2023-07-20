#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int popcnt(int bit) {
	bit = ((bit >> 1) & 0x55555555) + (bit & 0x55555555);
	bit = ((bit >> 2) & 0x33333333) + (bit & 0x33333333);
	bit = ((bit >> 4) & 0x0F0F0F0F) + (bit & 0x0F0F0F0F);
	bit = ((bit >> 8) & 0x00FF00FF) + (bit & 0x00FF00FF);
	bit = ((bit >> 16) & 0x0000FFFF) + (bit & 0x0000FFFF);
	return bit;
}

int cache[10][1 << 12]; // 메모이제이션, DP() 참고
int can_take[1 << 12]; // PreProcess() 참고
// 과목 수, 들어야하는 과목 수, 남은 학기 수, 한 학기당 최대 수강 과목 수
int major_sz, K, semester_sz, limit; 
// i번 과목의 선 수강 과목, i번 학기에 열리는 과목
int pre_learning[12], open_subject[12];

// learned 에 비트마스킹된 과목들을 들었을 때
// 다음에 들을 수 있는 과목들을 미리 계산해서 can_take에 저장
void PreProcess()
{
	for (int learned = (1 << 12) - 1; learned>=0; learned--)
		for (int i = 0; i < major_sz; i++)
			if ((learned & 1 << i) == 0 && (learned & pre_learning[i]) == pre_learning[i])
				can_take[learned] |= 1 << i;
}

// 현재 학기가 semester, 들은 과목이 learned일 때 최소로 몇 학기를 더 들어야 졸업 가능한가
// 채워야 하는 과목이 K개, 한 학기에 최대 수강 과목 개수가 limit
int Graduate(int semester, int learned)
{
	if (popcnt(learned) >= K) return 0;
	else if (semester == semester_sz) return 987654321;
	
	int& ret = cache[semester][learned];
	if (ret != -1) return ret;
	ret = 987654321;

	// 이번 학기에 듣는 과목
	int take = can_take[learned] & open_subject[semester];

	// 이번 학기에 들을 수 있는 과목이 있으면
	if (take) {
		// 최대한 많은 과목을 듣는다 (그리디)
		if (popcnt(take) <= limit) 
			ret = Graduate(semester + 1, learned | take )+1;
		else {
			// take 중에서 limit개 선택
			for (int select = take; select; select = (select - 1) & take)
				if (popcnt(select) == limit)
					ret = min(ret, Graduate(semester + 1, learned | select)+1);
		}
	}

	// 이번 학기를 패스하는 경우와 비교
	return ret = min(ret, Graduate(semester + 1, learned));
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		memset(cache, -1, sizeof(cache));
		memset(can_take, 0, sizeof(can_take));
		cin >> major_sz >> K >> semester_sz >> limit;

		for (int i = 0; i < major_sz; i++) {
			pre_learning[i] = 0;
			int n;
			cin >> n;
			for (int j = 0; j < n; j++) {
				int subject;
				cin >> subject;
				pre_learning[i] |= 1 << subject;
			}
		}
		for (int i = 0; i < semester_sz; i++) {
			open_subject[i] = 0;
			int n;
			cin >> n;
			for (int j = 0; j < n; j++) {
				int subject;
				cin >> subject;
				open_subject[i] |= 1 << subject;
			}
		}

		PreProcess();
		int ans = Graduate(0, 0);
		if (ans <= semester_sz)
			cout << ans << '\n';
		else
			cout << "IMPOSSIBLE\n";
	}
	return 0;
}