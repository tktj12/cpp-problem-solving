#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int solve(int, int);

vector<int> board;
int cache[52][52];
int main()
{
	cin.tie(nullptr);
	cout.tie(nullptr);
	ios::sync_with_stdio(false);

	int tc;
	cin >> tc;
	while (tc--) {
		memset(cache, 0x80, sizeof(cache)); // ¾à -21¾ï

		int n;
		cin >> n;
		board = vector<int>(n, 0);
		for (int i = 0; i < n; ++i) cin >> board[i];

		cout << solve(0, n - 1) << '\n';
	}
	return 0;
}

int solve(int left, int right)
{
	int& ret = cache[left][right];
	if (ret > -987654321) return ret;

	if (left > right) return ret = 0;
	else if (left == right) return ret = board[left];

	ret = -987654321;

	ret = max(ret, -solve(left + 2, right));
	ret = max(ret, -solve(left, right-2));
	ret = max(ret, board[left] -solve(left + 1, right));
	ret = max(ret, board[right] -solve(left, right-1));

	return ret;
}