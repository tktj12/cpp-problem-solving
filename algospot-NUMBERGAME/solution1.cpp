#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int solve();

vector<int> board;
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
		board = vector<int>(n, 0);
		for (int i = 0; i < n; ++i) cin >> board[i];
		cout << solve() << '\n';
	}
	return 0;
}

int solve()
{
	if (board.size() == 0) return 0;
	else if (board.size() == 1) return board.back();

	int ret = -987654321;
	int cand;
	if (board.size() >= 2) {
		int pick1, pick2;
		pick1 = board[0];
		pick2 = board[1];
		board.erase(board.begin(), board.begin() + 2);
		cand = -solve();
		board.insert(board.begin(), { pick1,pick2 });
		ret = max(ret, cand);

		pick1 = board[board.size() - 2];
		pick2 = board.back();
		board.erase(board.end() - 2, board.end());
		cand = -solve();
		board.insert(board.end(), { pick1,pick2 });
		ret = max(ret, cand);
	}

	int pick;
	pick = board[0];
	board.erase(board.begin());
	cand = pick - solve();
	board.insert(board.begin(), pick);
	ret = max(ret, cand);

	pick = board.back();
	board.erase(board.end()-1);
	cand = pick - solve();
	board.insert(board.end(), pick);
	ret = max(ret, cand);

	return ret;
}