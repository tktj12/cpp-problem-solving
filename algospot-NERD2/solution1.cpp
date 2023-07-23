#include <iostream>
#include <set>
using namespace std;


int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int n;
		cin >> n;

		set<pair<int,int>> nerd;
		nerd.insert({ -1, 100001 });
		nerd.insert({ 100001, -1 });

		int ans = 0;
		for (int i = 0; i < n; i++) {
			int p, q;
			cin >> p >> q;
			nerd.insert({ p,q });
			auto iter = nerd.find({ p,q });
			int left = (++iter)->second;
			--iter;
			int right = (--iter)->second;

			// ������ ������ ���
			if (q < left)
				nerd.erase(++iter);
			// �ٸ� ����� �������ϴ� ���
			while (right < q) {
				nerd.erase(iter--);
				right = (iter)->second;
			}

			ans += nerd.size() - 2;
		}

		cout << ans << '\n';
	}
	return 0;
}