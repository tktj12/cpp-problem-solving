#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
using ull = unsigned long long;
using ll = long long;

int N, prime[10];
ll M, ans;
void Solve(int depth, int choose, ull num)
{
	if (depth == N) {
		if (choose == 0) return;

		ll tp = M/num;
		if (choose % 2 == 0) tp = -tp;
		ans += tp;
		return;
	}

	Solve(depth + 1, choose + 1, num * prime[depth]);
	Solve(depth + 1, choose, num);
}

int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> N >> M;
	for (int i = 0; i < N; i++) cin >> prime[i];

	Solve(0, 0, 1);
	cout << ans;

	return 0;
}