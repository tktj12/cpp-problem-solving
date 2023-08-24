#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXM = 10'000'000;
int N;
int cache[100][10001], memory[100], cost[100];
int DP(int app, int total_cost)
{
	if (app == N) return 0;

	int& ret = cache[app][total_cost];
	if (ret != -1) return ret;
	ret = 0;

	if (total_cost >= cost[app])
		ret = max(ret, DP(app + 1, total_cost - cost[app]) + memory[app]);
	ret = max(ret, DP(app + 1, total_cost));
	return ret = min(ret, MAXM);
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	memset(cache, -1, sizeof(cache));

	int M;
	cin >> N >> M;
	for (int i = 0; i < N; i++) cin >> memory[i];
	for (int i = 0; i < N; i++) cin >> cost[i];

	int c = 0;
	while (1)
		if (DP(0, c++) >= M) break;

	cout << c-1;

	return 0;
}