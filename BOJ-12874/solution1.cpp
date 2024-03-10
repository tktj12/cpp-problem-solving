#include <iostream>
#include <cstring>
using namespace std;

const int MOD = 1'000'000'007;
int cache[100][100];
string S;

// DP(pos,open) = DP(next_open_pos, open+1) + DP(next_close_pos, open-1)
int DP(int pos, int open)
{
	if (pos >= S.size()) return 0;

	int& ret = cache[pos][open];
	if (ret != -1) return ret;

	int next_open_case=0, next_close_case=0;
	for (int i = pos + 1; i < S.size(); i++)
		if (S[i] == '(') {
			next_open_case = DP(i, open + 1);
			break;
		}

	if (open > 0)
		for (int i = pos + 1; i < S.size(); i++)
			if (S[i] == ')') {
				next_close_case = DP(i, open - 1);
				if (open == 1) next_close_case++;
				break;
			}

	return ret = (next_open_case + next_close_case) % MOD;
}

int main()
{
	memset(cache, -1, sizeof(cache));

	cin >> S;
	for (int i = 0; i < S.size(); i++)
		if (S[i] == '(') {
			cout << DP(i, 1);
			return 0;
		}

	cout << 0;
	return 0;
}
