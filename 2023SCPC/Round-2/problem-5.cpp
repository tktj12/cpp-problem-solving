#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
using ll = long long;

ll PopCount(int bit)
{
	bit = ((bit >> 1) & 0x55555555) + (bit & 0x55555555);
	bit = ((bit >> 2) & 0x33333333) + (bit & 0x33333333);
	bit = ((bit >> 4) & 0x0F0F0F0F) + (bit & 0x0F0F0F0F);
	bit = ((bit >> 8) & 0x00FF00FF) + (bit & 0x00FF00FF);
	return (bit >> 16) + (bit & 0x0000FFFF);
}

vector<vector<int>> edge;
int possible_value[21][21][21];
ll cache[21][1 << 21];
void FillPossibleValue(int n, int k)
{
	int fill = (1 << 21) - 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			for (int k =1; k <= n; k++)
				possible_value[i][j][k] = fill;

	for (int here = 1; here <= n; here++)
		for (int apart = 1; apart <= n; apart++)
			for (int there : edge[here])
				for (int their_apart = 1; their_apart <= n; their_apart++)
					if (apart + their_apart > k || apart == their_apart)
						possible_value[here][apart][there] & ~(1 << their_apart);
}

ll DP(int here, int n, int k, vector<int> possible)
{
	ll& ret = cache[here][possible[here]];

	if (here == n) return PopCount(possible[n]);


}

ll Solve(int n, int k)
{

}

int main(int argc, char** argv)
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);
	int T, test_case;
	cin >> T;

	for (test_case = 0; test_case < T; test_case++)
	{
		memset(cache, -1, sizeof(cache));

		ll answer = 0;
		int n, k;
		cin >> n >> k;

		int edge_sz;
		cin >> edge_sz;
		edge = vector<vector<int>>(edge_sz);
		for (int i = 0; i < edge_sz; i++) {
			int u, v;
			cin >> u >> v;
			if (u > v) swap(u, v); // 항상 u가 작음
			edge[u].push_back(v);
		}

		FillPossibleValue(n,k);

		cout << "Case #" << test_case + 1 << '\n';
	}

	return 0;
}