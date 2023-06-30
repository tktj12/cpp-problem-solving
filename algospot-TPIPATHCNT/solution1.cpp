#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

struct Data {
	int v;
	int cnt;
};
Data DP(int, int);

int N;
int tree[100][100];
Data cache[100][100];
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		cin >> N;
		for (int i = 0; i < N; ++i)
			for (int j = 0; j <= i; ++j)
				cin >> tree[i][j];

		memset(cache, -1, sizeof(cache));
		cout << DP(0, 0).cnt << '\n';
	}
	return 0;
}

Data DP(int y, int x)
{
	Data& ret = cache[y][x];
	if (ret.v != -1) return ret;
	if (y == N - 1) return ret = { tree[y][x], 1 };

	ret = DP(y + 1, x);
	Data cand = DP(y + 1, x + 1);
	if (cand.v > ret.v) ret = cand;
	else if (cand.v == ret.v) ret.cnt += cand.cnt;

	ret.v += tree[y][x];
	return ret;
}