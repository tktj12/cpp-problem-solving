#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Student {
public:
	vector<int> brain;
	int level=0;

	bool operator<(Student& rhs) const {
		return level < rhs.level;
	}
}s[100000];

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int cnt[31] = {};
	int N,K,D;
	
	cin >> N >> K >> D;
	for (int i = 0; i < N; i++) {
		int alg,lev; cin >> alg >> lev;
		s[i].level = lev;
		for (int j = 0; j < alg; j++) {
			int num; cin >> num;
			s[i].brain.push_back(num);
		}
	}
	sort(s,s + N);

	int l = 0,r = -1,ans=0;
	while (r < N-1) {
		r++;
		for (int e : s[r].brain)
			cnt[e]++;

		while (l < r && s[r].level - s[l].level > D) {
			for (int e : s[l].brain)
				cnt[e]--;
			l++;
		}
		while (r < N-1 && s[r + 1].level - s[l].level <= D) {
			r++;
			for (int e : s[r].brain)
				cnt[e]++;
		}
		int a = 0, sz=r-l+1;
		for (int i = 1; i <= K; i++)
			if (0<cnt[i]&&cnt[i]<sz) a++;
		ans = max(ans,a * sz);
	}
	cout << ans;

	return 0;
}