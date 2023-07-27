#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

const int MAXN = 1000001;
int fenwick[MAXN];

int sum(int end)
{
	end++;
	int ret = 0;
	while (end > 0) {
		ret += fenwick[end];
		end &= end - 1;
	}
	return ret;
}

void add(int end)
{
	end++;
	while (end < MAXN) {
		fenwick[end]++;
		end += (end & -end);
	}
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		int n, ans(0);
		cin >> n;
		memset(fenwick, 0, sizeof(fenwick));
		for (int i = 0; i < n; i++) {
			int num;
			cin >> num; 
			ans += i - sum(num);
			add(num);
		}
		cout << ans << '\n';
	}
	return 0;
}